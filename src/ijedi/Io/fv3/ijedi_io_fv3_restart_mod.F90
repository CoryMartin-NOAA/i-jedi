module ijedi_io_fv3_restart_mod

use iso_c_binding
use fms2_io_mod
use mpp_domains_mod
use mpp_mod
use fckit_configuration_module, only: fckit_configuration
use ijedi_kinds_mod
use ijedi_fv3_geom_mod

implicit none
private

public :: ijedi_io_fv3_restart
public :: ijedi_io_fv3_restart_create
public :: ijedi_io_fv3_restart_delete
public :: ijedi_io_fv3_restart_read

integer, parameter :: numfiles = 9
integer, parameter :: field_clen = 128

type ijedi_io_fv3_restart
   type(domain2D) :: domain
   character(len=128) :: datapath
   character(len=128) :: filenames(numfiles)
   logical :: ps_in_file
   logical :: skip_coupler
   logical :: prepend_date
   logical :: ignore_checksum
   integer :: npx, npy, npz, ntiles
   integer :: isc, iec, jsc, jec, isd, ied, jsd, jed
   integer :: index_core = 1
   integer :: index_trcr = 2
   integer :: index_sfcd = 3
   integer :: index_sfcw = 4
   integer :: index_cplr = 5
   integer :: index_spec = 6
   integer :: index_phys = 7
   integer :: index_orog = 8
   integer :: index_cold = 9
end type ijedi_io_fv3_restart

type structured_buffer_t
   real(kind_real), allocatable :: data(:,:,:)
   integer :: levels
end type structured_buffer_t

contains

! --------------------------------------------------------------------------------------------------

subroutine ijedi_io_fv3_restart_create(self_ptr, conf_ptr, geom_vars_ptr) bind(c, name='ijedi_io_fv3_restart_create_f90')
   type(c_ptr), intent(out) :: self_ptr
   type(c_ptr), value, intent(in) :: conf_ptr
   type(c_ptr), value, intent(in) :: geom_vars_ptr

   type(ijedi_io_fv3_restart), pointer :: self
   type(fckit_configuration) :: conf, geom_vars
   character(len=:), allocatable :: str
   integer :: layout(2), io_layout(2)
   integer :: n
   character(len=13) :: fileconf(numfiles)

   allocate(self)
   self_ptr = c_loc(self)

   conf = fckit_configuration(conf_ptr)
   geom_vars = fckit_configuration(geom_vars_ptr)

   ! Extract grid info from geom_vars
   call geom_vars%get_or_die("npx", self%npx)
   call geom_vars%get_or_die("npy", self%npy)
   call geom_vars%get_or_die("nLevels", self%npz)
   call geom_vars%get_or_die("ntiles", self%ntiles)
   call geom_vars%get_or_die("layout_x", layout(1))
   call geom_vars%get_or_die("layout_y", layout(2))

   ! io_layout - default to layout if not provided
   if (.not. geom_vars%get("io_layout_x", io_layout(1))) io_layout(1) = layout(1)
   if (.not. geom_vars%get("io_layout_y", io_layout(2))) io_layout(2) = layout(2)

   ! Set up domain
   call fv3_geom_setup_domain(self%domain, self%npx-1, self%npy-1, &
                               self%ntiles, layout, io_layout, 3)

   call mpp_get_compute_domain(self%domain, self%isc, self%iec, self%jsc, self%jec)
   call mpp_get_data_domain(self%domain, self%isd, self%ied, self%jsd, self%jed)

   ! Get path to files
   call conf%get_or_die("datapath", str)
   self%datapath = str
   deallocate(str)

   ! Default filenames
   self%filenames(self%index_core) = 'fv_core.res.nc'
   self%filenames(self%index_trcr) = 'fv_tracer.res.nc'
   self%filenames(self%index_sfcd) = 'sfc_data.nc'
   self%filenames(self%index_sfcw) = 'fv_srf_wnd.res.nc'
   self%filenames(self%index_cplr) = 'coupler.res'
   self%filenames(self%index_spec) = 'null'
   self%filenames(self%index_phys) = 'phy_data.nc'
   self%filenames(self%index_orog) = 'oro_data.nc'
   self%filenames(self%index_cold) = 'gfs_data.nc'

   fileconf(self%index_core) = "filename_core"
   fileconf(self%index_trcr) = "filename_trcr"
   fileconf(self%index_sfcd) = "filename_sfcd"
   fileconf(self%index_sfcw) = "filename_sfcw"
   fileconf(self%index_cplr) = "filename_cplr"
   fileconf(self%index_spec) = "filename_spec"
   fileconf(self%index_phys) = "filename_phys"
   fileconf(self%index_orog) = "filename_orog"
   fileconf(self%index_cold) = "filename_cold"

   do n = 1, numfiles
      if (conf%has(fileconf(n))) then
         call conf%get_or_die(fileconf(n), str)
         self%filenames(n) = str
         deallocate(str)
      endif
   enddo

   self%ps_in_file = .false.
   if (conf%has("psinfile")) call conf%get_or_die("psinfile", self%ps_in_file)

   self%skip_coupler = .false.
   if (conf%has("skip coupler file")) call conf%get_or_die("skip coupler file", self%skip_coupler)

   if (.not. conf%get("prepend files with date", self%prepend_date)) self%prepend_date = .true.

   if (conf%has("ignore checksum")) then
      call conf%get_or_die("ignore checksum", self%ignore_checksum)
   else
      self%ignore_checksum = .true.
   endif

end subroutine ijedi_io_fv3_restart_create

! --------------------------------------------------------------------------------------------------

subroutine ijedi_io_fv3_restart_delete(self_ptr) bind(c, name='ijedi_io_fv3_restart_delete_f90')
   type(c_ptr), intent(inout) :: self_ptr
   type(ijedi_io_fv3_restart), pointer :: self

   if (c_associated(self_ptr)) then
      call c_f_pointer(self_ptr, self)
      call mpp_deallocate_domain(self%domain)
      deallocate(self)
      self_ptr = c_null_ptr
   endif
end subroutine ijedi_io_fv3_restart_delete

! --------------------------------------------------------------------------------------------------

subroutine ijedi_io_fv3_restart_read(self_ptr, num_fields, levels, field_io_names, atlas_ptrs) &
                                     bind(c, name='ijedi_io_fv3_restart_read_f90')
   type(c_ptr), value, intent(in) :: self_ptr
   integer(c_int), value, intent(in) :: num_fields
   integer(c_int), intent(in) :: levels(num_fields)
   type(c_ptr), intent(in) :: field_io_names(num_fields) ! Array of c_ptr to strings
   type(c_ptr), intent(in) :: atlas_ptrs(num_fields) ! Array of pointers to atlas field data

   type(ijedi_io_fv3_restart), pointer :: self
   type(FmsNetcdfDomainFile_t) :: fileobj(numfiles)
   logical :: rstflag(numfiles)
   integer :: n, var, indexrst, k, i, j, jl
   character(len=field_clen) :: io_name
   real(kind_real), pointer :: atlas_view(:,:)
   integer :: ngrid
   type(structured_buffer_t), allocatable :: buffers(:)

   call c_f_pointer(self_ptr, self)

   ngrid = (self%iec-self%isc+1)*(self%jec-self%jsc+1)
   rstflag(:) = .false.

   allocate(buffers(num_fields))

   do var = 1, num_fields
      call convert_c_string(field_io_names(var), io_name)
      buffers(var)%levels = levels(var)
      allocate(buffers(var)%data(self%isd:self%ied, self%jsd:self%jed, levels(var)))

      call get_io_file(self, io_name, levels(var), indexrst)

      if (.not. rstflag(indexrst)) then
         if (open_file(fileobj(indexrst), &
              trim(self%datapath)//'/'//trim(self%filenames(indexrst)), &
              "read", self%domain, is_restart=.true., &
              dont_add_res_to_filename=.true.)) then
            rstflag(indexrst) = .true.
         else
            call mpp_error(FATAL, 'ijedi_io_fv3_restart_mod.read_restart_read: could not open '//trim(self%filenames(indexrst)))
         endif
      endif

      call register_restart_field(fileobj(indexrst), trim(io_name), buffers(var)%data)
   enddo

   ! Read all registered fields for each file
   do n = 1, numfiles
      if (rstflag(n)) then
         call read_restart(fileobj(n), ignore_checksum=self%ignore_checksum)
         call close_file(fileobj(n))
      endif
   enddo

   ! Copy from structured buffers to Atlas
   do var = 1, num_fields
      call c_f_pointer(atlas_ptrs(var), atlas_view, [buffers(var)%levels, ngrid])
      do jl = 1, buffers(var)%levels
         do j = self%jsc, self%jec
            do i = self%isc, self%iec
               k = (j - self%jsc) * (self%iec - self%isc + 1) + (i - self%isc) + 1
               atlas_view(jl, k) = buffers(var)%data(i, j, jl)
            enddo
         enddo
      enddo
      deallocate(buffers(var)%data)
   enddo

   deallocate(buffers)

end subroutine ijedi_io_fv3_restart_read

subroutine get_io_file(self, io_name, npz, indexrst)
   type(ijedi_io_fv3_restart), intent(in) :: self
   character(len=*), intent(in) :: io_name
   integer, intent(in) :: npz
   integer, intent(out) :: indexrst

   character(len=field_clen) :: io_file

   io_file = 'core'
   ! Basic logic ported from fv3-jedi
   if (npz == 1) io_file = 'surface'
   if (index(io_name, 'sphum') > 0 .or. index(io_name, 'liq_wat') > 0 .or. &
       index(io_name, 'ice_wat') > 0 .or. index(io_name, 'rainwat') > 0 .or. &
       index(io_name, 'snowwat') > 0 .or. index(io_name, 'graupel') > 0) io_file = 'tracer'

   select case (io_file)
   case("core")
      indexrst = self%index_core
   case("tracer")
      indexrst = self%index_trcr
   case("surface")
      indexrst = self%index_sfcd
   case default
      indexrst = self%index_core
   end select
end subroutine get_io_file

subroutine convert_c_string(c_str_ptr, f_string)
   type(c_ptr), intent(in) :: c_str_ptr
   character(len=*), intent(out) :: f_string
   character(kind=c_char), pointer :: c_array(:)
   integer :: i

   call c_f_pointer(c_str_ptr, c_array, [field_clen])
   f_string = ""
   do i = 1, field_clen
      if (c_array(i) == c_null_char) exit
      f_string(i:i) = c_array(i)
   enddo
end subroutine convert_c_string

end module ijedi_io_fv3_restart_mod
