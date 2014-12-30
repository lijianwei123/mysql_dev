#!/bin/sh

#check mysql-devel
is_install=`rpm -qa mysql-devel`
if test -z "$is_install"; then
	yum -y install mysql-devel
fi



echo "install mongodb c driver start......"
yum install  gcc automake autoconf libtool
git clone https://github.com/mongodb/mongo-c-driver.git
cd mongo-c-driver
./autogen.sh
make
make install
cd ..
echo "PKG_CONFIG_PATH=/usr/local/lib/pkgconfig/:\$PKG_CONFIG_PATH" >> /etc/profile
echo "LD_LIBRARY_PATH=/usr/local/lib:\$LD_LIBRARY_PATH" >> /etc/profile
source /etc/profile
echo "install mongodb c driver end......"

