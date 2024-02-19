LINARO=/usr/gcc-linaro-11.3.1-2022.06-x86_64_arm-linux-gnueabihf/bin
PATH=$LINARO:$PATH
./configure \
CFLAGS=-I/usr/arm/libressl/include/ \
LDFLAGS=-L/usr/arm/libressl/lib/ \
--prefix=/usr/arm/openssh \
--host=arm-linux-gnueabihf \
--with-zlib=/home/bytbager/My_projects/Eltex/Lecture51/zlib-1.3.1/_install \
--with-cfalgs-after \
--with-ldflags-after
# --with-z=/home/bytbager/My_projects/Eltex/Lecture51/zlib-1.3.1/_install \