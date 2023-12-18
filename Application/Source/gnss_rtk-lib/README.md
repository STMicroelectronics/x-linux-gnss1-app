META-ST-X-LINUX-GNSS1-RTKLIB:
==============================================================================================================
The META-ST-X-LINUX-GNSS1-RTKLIB is a Yocto Recipe for RTK Lib Application.It builds the RTK application and the corresponding QT GUI Application

To use the patch follow the below Steps : 
(1) Apply the GNSS and IMU patches on the Linux Kernel from here : meta-st-x-linux-gnss1\Layers\meta-st-x-linux-gnss1\meta-gnss1\recipes-kernel\linux\linux-stm32mp\stm32mp1
(2) Clone the repo : RTK lib : https://github.com/tomojitakasu/RTKLIB and https://github.com/Francklin2/RTKLIB_Touchscreen_GUI/
(3) Apply the patches from this directory

For detailed instructions refer "Getting started with X-LINUX-GNSS1 package for developing GNSS Applications on Linux : https://www.st.com/resource/en/user_manual/um2909-getting-started-with-xlinuxgnss1-package-for-developing-gnss-applications-on-linux-os-stmicroelectronics.pdf"  

