LINARO=/usr/gcc-linaro-11.3.1-2022.06-x86_64_arm-linux-gnueabihf/bin
PATH=$LINARO:$PATH
./Configure \
--cross-compile-prefix=arm-linux-gnueabihf- \
--prefix=/usr/arm/openssl \
--with-zlib-include=/home/bytbager/My_projects/Eltex/Lecture51/zlib-1.3.1/_install/include \
--with-zlib-lib=/home/bytbager/My_projects/Eltex/Lecture51/zlib-1.3.1/_install/lib \
# CC=arm-linux-gnueabihf-gcc
# CFLAGS=-I/usr/arm/libressl/include/ \
# LDFLAGS=-L/usr/arm/libressl/lib/ \
# --with-cfalgs-after \
# --with-ldflags-after