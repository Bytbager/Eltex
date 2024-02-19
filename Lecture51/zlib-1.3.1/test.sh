LINARO=/usr/gcc-linaro-11.3.1-2022.06-x86_64_arm-linux-gnueabihf/bin
CHOST=arm \
CC=$LINARO/arm-linux-gnueabihf-gcc \
AR=$LINARO/arm-linux-gnueabihf-ar \
RANLIB=$LINARO/arm-linux-gnueabihf-ranlib \
./configure \
--prefix=$PWD/_install