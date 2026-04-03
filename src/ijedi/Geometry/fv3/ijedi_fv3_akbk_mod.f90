module ijedi_fv3_akbk_mod

! ijedi uses
use ijedi_kinds_mod, only: kind_real

implicit none
private
public akbk_gfs_127

! --------------------------------------------------------------------------------------------------

contains

! --------------------------------------------------------------------------------------------------

subroutine akbk_gfs_127(npz, ak, bk)

! Arguments
integer,              intent(in)    :: npz
real(kind=kind_real), intent(inout) :: ak(npz+1)
real(kind=kind_real), intent(inout) :: bk(npz+1)

! Locals
integer :: j

! Fill ak
! -------
j = 0
j = j+1; ak(j) = 0.999_kind_real
j = j+1; ak(j) = 1.605_kind_real
j = j+1; ak(j) = 2.532_kind_real
j = j+1; ak(j) = 3.924_kind_real
j = j+1; ak(j) = 5.976_kind_real
j = j+1; ak(j) = 8.947_kind_real
j = j+1; ak(j) = 13.177_kind_real
j = j+1; ak(j) = 19.096_kind_real
j = j+1; ak(j) = 27.243_kind_real
j = j+1; ak(j) = 38.276_kind_real
j = j+1; ak(j) = 52.984_kind_real
j = j+1; ak(j) = 72.293_kind_real
j = j+1; ak(j) = 97.269_kind_real
j = j+1; ak(j) = 129.11_kind_real
j = j+1; ak(j) = 169.135_kind_real
j = j+1; ak(j) = 218.767_kind_real
j = j+1; ak(j) = 279.506_kind_real
j = j+1; ak(j) = 352.894_kind_real
j = j+1; ak(j) = 440.481_kind_real
j = j+1; ak(j) = 543.782_kind_real
j = j+1; ak(j) = 664.236_kind_real
j = j+1; ak(j) = 803.164_kind_real
j = j+1; ak(j) = 961.734_kind_real
j = j+1; ak(j) = 1140.931_kind_real
j = j+1; ak(j) = 1341.538_kind_real
j = j+1; ak(j) = 1564.119_kind_real
j = j+1; ak(j) = 1809.028_kind_real
j = j+1; ak(j) = 2076.415_kind_real
j = j+1; ak(j) = 2366.252_kind_real
j = j+1; ak(j) = 2678.372_kind_real
j = j+1; ak(j) = 3012.51_kind_real
j = j+1; ak(j) = 3368.363_kind_real
j = j+1; ak(j) = 3745.646_kind_real
j = j+1; ak(j) = 4144.164_kind_real
j = j+1; ak(j) = 4563.881_kind_real
j = j+1; ak(j) = 5004.995_kind_real
j = j+1; ak(j) = 5468.017_kind_real
j = j+1; ak(j) = 5953.848_kind_real
j = j+1; ak(j) = 6463.864_kind_real
j = j+1; ak(j) = 7000.0_kind_real
j = j+1; ak(j) = 7563.494_kind_real
j = j+1; ak(j) = 8150.661_kind_real
j = j+1; ak(j) = 8756.529_kind_real
j = j+1; ak(j) = 9376.141_kind_real
j = j+1; ak(j) = 10004.553_kind_real
j = j+1; ak(j) = 10636.851_kind_real
j = j+1; ak(j) = 11268.157_kind_real
j = j+1; ak(j) = 11893.639_kind_real
j = j+1; ak(j) = 12508.519_kind_real
j = j+1; ak(j) = 13108.091_kind_real
j = j+1; ak(j) = 13687.727_kind_real
j = j+1; ak(j) = 14242.89_kind_real
j = j+1; ak(j) = 14769.153_kind_real
j = j+1; ak(j) = 15262.202_kind_real
j = j+1; ak(j) = 15717.859_kind_real
j = j+1; ak(j) = 16132.09_kind_real
j = j+1; ak(j) = 16501.018_kind_real
j = j+1; ak(j) = 16820.938_kind_real
j = j+1; ak(j) = 17088.324_kind_real
j = j+1; ak(j) = 17299.852_kind_real
j = j+1; ak(j) = 17453.084_kind_real
j = j+1; ak(j) = 17548.35_kind_real
j = j+1; ak(j) = 17586.771_kind_real
j = j+1; ak(j) = 17569.697_kind_real
j = j+1; ak(j) = 17498.697_kind_real
j = j+1; ak(j) = 17375.561_kind_real
j = j+1; ak(j) = 17202.299_kind_real
j = j+1; ak(j) = 16981.137_kind_real
j = j+1; ak(j) = 16714.504_kind_real
j = j+1; ak(j) = 16405.02_kind_real
j = j+1; ak(j) = 16055.485_kind_real
j = j+1; ak(j) = 15668.86_kind_real
j = j+1; ak(j) = 15248.247_kind_real
j = j+1; ak(j) = 14796.868_kind_real
j = j+1; ak(j) = 14318.04_kind_real
j = j+1; ak(j) = 13815.15_kind_real
j = j+1; ak(j) = 13291.629_kind_real
j = j+1; ak(j) = 12750.924_kind_real
j = j+1; ak(j) = 12196.468_kind_real
j = j+1; ak(j) = 11631.659_kind_real
j = j+1; ak(j) = 11059.827_kind_real
j = j+1; ak(j) = 10484.208_kind_real
j = j+1; ak(j) = 9907.927_kind_real
j = j+1; ak(j) = 9333.967_kind_real
j = j+1; ak(j) = 8765.155_kind_real
j = j+1; ak(j) = 8204.142_kind_real
j = j+1; ak(j) = 7653.387_kind_real
j = j+1; ak(j) = 7115.147_kind_real
j = j+1; ak(j) = 6591.468_kind_real
j = j+1; ak(j) = 6084.176_kind_real
j = j+1; ak(j) = 5594.876_kind_real
j = j+1; ak(j) = 5124.949_kind_real
j = j+1; ak(j) = 4675.554_kind_real
j = j+1; ak(j) = 4247.633_kind_real
j = j+1; ak(j) = 3841.918_kind_real
j = j+1; ak(j) = 3458.933_kind_real
j = j+1; ak(j) = 3099.01_kind_real
j = j+1; ak(j) = 2762.297_kind_real
j = j+1; ak(j) = 2448.768_kind_real
j = j+1; ak(j) = 2158.238_kind_real
j = j+1; ak(j) = 1890.375_kind_real
j = j+1; ak(j) = 1644.712_kind_real
j = j+1; ak(j) = 1420.661_kind_real
j = j+1; ak(j) = 1217.528_kind_real
j = j+1; ak(j) = 1034.524_kind_real
j = j+1; ak(j) = 870.778_kind_real
j = j+1; ak(j) = 725.348_kind_real
j = j+1; ak(j) = 597.235_kind_real
j = j+1; ak(j) = 485.392_kind_real
j = j+1; ak(j) = 388.734_kind_real
j = j+1; ak(j) = 306.149_kind_real
j = j+1; ak(j) = 236.502_kind_real
j = j+1; ak(j) = 178.651_kind_real
j = j+1; ak(j) = 131.447_kind_real
j = j+1; ak(j) = 93.74_kind_real
j = j+1; ak(j) = 64.392_kind_real
j = j+1; ak(j) = 42.274_kind_real
j = j+1; ak(j) = 26.274_kind_real
j = j+1; ak(j) = 15.302_kind_real
j = j+1; ak(j) = 8.287_kind_real
j = j+1; ak(j) = 4.19_kind_real
j = j+1; ak(j) = 1.994_kind_real
j = j+1; ak(j) = 0.81_kind_real
j = j+1; ak(j) = 0.232_kind_real
j = j+1; ak(j) = 0.029_kind_real
j = j+1; ak(j) = 0.0_kind_real
j = j+1; ak(j) = 0.0_kind_real
j = j+1; ak(j) = 0.0_kind_real

! Fill bk
! -------
j = 0
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 0.0_kind_real
j = j+1; bk(j) = 1.018e-05_kind_real
j = j+1; bk(j) = 8.141e-05_kind_real
j = j+1; bk(j) = 0.00027469_kind_real
j = j+1; bk(j) = 0.00065078_kind_real
j = j+1; bk(j) = 0.00127009_kind_real
j = j+1; bk(j) = 0.00219248_kind_real
j = j+1; bk(j) = 0.00347713_kind_real
j = j+1; bk(j) = 0.00518228_kind_real
j = j+1; bk(j) = 0.00736504_kind_real
j = j+1; bk(j) = 0.0100812_kind_real
j = j+1; bk(j) = 0.01338492_kind_real
j = j+1; bk(j) = 0.01732857_kind_real
j = j+1; bk(j) = 0.02196239_kind_real
j = j+1; bk(j) = 0.02733428_kind_real
j = j+1; bk(j) = 0.03348954_kind_real
j = j+1; bk(j) = 0.04047056_kind_real
j = j+1; bk(j) = 0.04831661_kind_real
j = j+1; bk(j) = 0.05706358_kind_real
j = j+1; bk(j) = 0.06674372_kind_real
j = j+1; bk(j) = 0.07738548_kind_real
j = j+1; bk(j) = 0.08900629_kind_real
j = j+1; bk(j) = 0.10159397_kind_real
j = j+1; bk(j) = 0.11512618_kind_real
j = j+1; bk(j) = 0.12957622_kind_real
j = j+1; bk(j) = 0.14491294_kind_real
j = j+1; bk(j) = 0.1611008_kind_real
j = j+1; bk(j) = 0.17809989_kind_real
j = j+1; bk(j) = 0.19586605_kind_real
j = j+1; bk(j) = 0.21435112_kind_real
j = j+1; bk(j) = 0.23350307_kind_real
j = j+1; bk(j) = 0.25326633_kind_real
j = j+1; bk(j) = 0.27358216_kind_real
j = j+1; bk(j) = 0.29438898_kind_real
j = j+1; bk(j) = 0.3156229_kind_real
j = j+1; bk(j) = 0.33721805_kind_real
j = j+1; bk(j) = 0.35910723_kind_real
j = j+1; bk(j) = 0.38122237_kind_real
j = j+1; bk(j) = 0.40349507_kind_real
j = j+1; bk(j) = 0.42585716_kind_real
j = j+1; bk(j) = 0.44824126_kind_real
j = j+1; bk(j) = 0.47058126_kind_real
j = j+1; bk(j) = 0.49281296_kind_real
j = j+1; bk(j) = 0.51487434_kind_real
j = j+1; bk(j) = 0.53670621_kind_real
j = j+1; bk(j) = 0.55825245_kind_real
j = j+1; bk(j) = 0.5794605_kind_real
j = j+1; bk(j) = 0.60028154_kind_real
j = j+1; bk(j) = 0.62067074_kind_real
j = j+1; bk(j) = 0.64058751_kind_real
j = j+1; bk(j) = 0.65999568_kind_real
j = j+1; bk(j) = 0.67886335_kind_real
j = j+1; bk(j) = 0.69716311_kind_real
j = j+1; bk(j) = 0.714872_kind_real
j = j+1; bk(j) = 0.73197126_kind_real
j = j+1; bk(j) = 0.74844646_kind_real
j = j+1; bk(j) = 0.76428711_kind_real
j = j+1; bk(j) = 0.77948666_kind_real
j = j+1; bk(j) = 0.79404217_kind_real
j = j+1; bk(j) = 0.80795413_kind_real
j = j+1; bk(j) = 0.8212263_kind_real
j = j+1; bk(j) = 0.83386517_kind_real
j = j+1; bk(j) = 0.84588009_kind_real
j = j+1; bk(j) = 0.85728264_kind_real
j = j+1; bk(j) = 0.86808664_kind_real
j = j+1; bk(j) = 0.8783077_kind_real
j = j+1; bk(j) = 0.88796324_kind_real
j = j+1; bk(j) = 0.89707178_kind_real
j = j+1; bk(j) = 0.90565324_kind_real
j = j+1; bk(j) = 0.91372836_kind_real
j = j+1; bk(j) = 0.92131871_kind_real
j = j+1; bk(j) = 0.92844635_kind_real
j = j+1; bk(j) = 0.93513376_kind_real
j = j+1; bk(j) = 0.94140369_kind_real
j = j+1; bk(j) = 0.94727886_kind_real
j = j+1; bk(j) = 0.95278209_kind_real
j = j+1; bk(j) = 0.95793599_kind_real
j = j+1; bk(j) = 0.96276295_kind_real
j = j+1; bk(j) = 0.9672851_kind_real
j = j+1; bk(j) = 0.971524_kind_real
j = j+1; bk(j) = 0.97550088_kind_real
j = j+1; bk(j) = 0.97923642_kind_real
j = j+1; bk(j) = 0.98275077_kind_real
j = j+1; bk(j) = 0.98606253_kind_real
j = j+1; bk(j) = 0.98918509_kind_real
j = j+1; bk(j) = 0.99212992_kind_real
j = j+1; bk(j) = 0.99490768_kind_real
j = j+1; bk(j) = 0.9975282_kind_real
j = j+1; bk(j) = 1.0_kind_real


end subroutine akbk_gfs_127

! --------------------------------------------------------------------------------------------------

end module ijedi_fv3_akbk_mod
