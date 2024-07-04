META-ST-X-LINUX-GNSS1-EKF:
==============================================================================================================
The META-ST-X-LINUX-GNSS1-EKF is a Yocto Recipe for GNSS+EKF Application.It builds the EKF command line application 

To use the patch follow the below Steps : 
(1) Apply the GNSS and IMU patches on the Linux Kernel from here : meta-st-x-linux-gnss1\Layers\meta-st-x-linux-gnss1\meta-gnss1\recipes-kernel\linux\linux-stm32mp\stm32mp1
(2) Clone the repo :https://github.com/balamuruganky/EKF_IMU_GPS/ , follow "git submodule update --init --recursive" from README.md file of github
(3) Apply the patches from this directory
(4) compile the code

For detailed instructions refer "Getting started with X-LINUX-GNSS1 package for developing GNSS Applications on Linux : https://www.st.com/resource/en/user_manual/um2909-getting-started-with-xlinuxgnss1-package-for-developing-gnss-applications-on-linux-os-stmicroelectronics.pdf"  

