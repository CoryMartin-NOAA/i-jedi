module ijedi_netcdf_utils_mod

use netcdf

implicit none
private
public nccheck

! ------------------------------------------------------------------------------

contains

! ------------------------------------------------------------------------------

subroutine nccheck(status,iam)

 implicit none
 integer, intent ( in) :: status
 character(len=*), optional :: iam

 character(len=1024) :: error_descr

 if(status /= nf90_noerr) then

   error_descr = "NetCDF error, aborting ... "

   if (present(iam)) then
     error_descr = trim(error_descr)//", "//trim(iam)
   endif

   error_descr = trim(error_descr)//". Error code: "//trim(nf90_strerror(status))

   call abor1_ftn(trim(error_descr))

 end if

end subroutine nccheck

! ------------------------------------------------------------------------------

end module ijedi_netcdf_utils_mod
