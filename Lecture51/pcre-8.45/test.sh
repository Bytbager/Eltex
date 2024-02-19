LINARO=/usr/gcc-linaro-11.3.1-2022.06-x86_64_arm-linux-gnueabihf/bin
PATH=$LINARO:$PATH
./configure \
--prefix=$PWD/_install \
--host=arm-linux-gnueabihf
# --with-z=/home/bytbager/My_projects/Eltex/Lecture51/zlib-1.3.1/_install \