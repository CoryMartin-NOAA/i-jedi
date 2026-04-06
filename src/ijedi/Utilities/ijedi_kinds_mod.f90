module ijedi_kinds_mod
  use, intrinsic :: iso_c_binding
  implicit none

  private
  public kind_int, kind_real

  integer, parameter :: kind_int=c_int
  integer, parameter :: kind_real=c_double
end module ijedi_kinds_mod
