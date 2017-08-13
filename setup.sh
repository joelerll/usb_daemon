## https://github.com/robertalks/udev-examples
## https://github.com/zserge/jsmn/blob/master/example/simple.c
## https://www.gnu.org/software/libmicrohttpd/

## COMPROBAR SI TIENE INSTALADO GIT
if [ -x "$(command -v make)" ]; then
  echo 'Ya tiene instalado make' >&2
else
  echo 'Instalando make'
  apt-get install make
fi

if [ -x "$(command -v git)" ]; then
  echo 'Ya tiene instalado git' >&2
else
  echo 'Instalando git'
  apt-get install git -y
fi

## INSTALANDO libmicrohttpd
if [ -x "$(command -v libmicrohttpd10)" ]; then
  echo 'Ya tiene instalado libmicrohttpd' >&2
else
  echo 'Instalando libmicrohttpd'
  apt-get -y install libmicrohttpd* > /dev/null
fi

## INSTALANDO libudev
if [ -x "$(command -v libudev1)" ]; then
  echo 'Ya tiene instalado libudev1' >&2
else
  echo 'Instalando libudev'
  apt-get install libudev1 > /dev/null
fi

## INSTALANDO jsmn
# function installjsmn {
#   echo 'Instalando libreria jsmn'
#   git clone --quiet https://github.com/zserge/jsmn.git  tmp > /dev/null
#   cd tmp
#   make
#   cp jsmn.a ../lib
#   cd ..
#   rm -rf tmp
#
# }
# installjsmn


## INSTALANDO wget
# if [ -x "$(command -v wget)" ]; then
#   echo 'Ya tiene instalado wget' >&2
#
# else
#   echo 'Instalando wget'
#   apt-get install wget > /dev/null
# fi
#
# function libmicrohttpd {
#   echo 'Instalando libmicrohttpd'
#   wget ftp://ftp.gnu.org/gnu/libmicrohttpd/libmicrohttpd-0.9.20.tar.gz > /dev/null
#   tar xvf libmicrohttpd-0.9.20.tar.gz > /dev/null
#   cd libmicrohttpd-0.9.20
#   ./configure
#   make
#   make install
#   cd ..
#   rm -f libmicrohttpd-0.9.20.tar.gz
#   rm -rf libmicrohttpd-0.9.20
# }
# libmicrohttpd
