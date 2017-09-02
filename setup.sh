## https://github.com/robertalks/udev-examples
## https://github.com/zserge/jsmn/blob/master/example/simple.c
## https://www.gnu.org/software/libmicrohttpd/

if [ -x "$(command -v make)" ]; then
  echo 'Ya tiene instalado make'
else
  echo 'Instalando make'
  apt-get install make
fi

if [ -x "$(command -v gcc)" ]; then
  echo 'Ya tiene instalado gcc'
else
  echo 'Instalando gcc'
  apt-get install gcc
fi

if [ -x "$(command -v wget)" ]; then
  echo 'Ya tiene instalado wget'
else
  echo 'Instalando wget'
  apt-get install wget
fi

if [ -x "$(command -v git)" ]; then
  echo 'Ya tiene instalado git'
else
  echo 'Instalando git'
  apt-get install git -y
fi

## INSTALANDO libmicrohttpd
if [ -x "$(command -v libmicrohttpd10)" ]; then
  echo 'Ya tiene instalado libmicrohttpd'
else
  echo 'Instalando libmicrohttpd'
  apt-get -y install libmicrohttpd*
fi

## INSTALANDO libudev
if [ -x "$(command -v libudev1)" ]; then
  echo 'Ya tiene instalado libudev'
else
  echo 'Instalando libudev'
  apt-get install libudev-dev
fi

## dependencias en python
echo "Instalando dependencias de python pip 3"
if [ -x "$(command -v pip3)" ]; then
  echo 'Ya tiene instalado pip python3'
else
  echo 'Instalando pip python3-pip'
  apt-get install python3-pip
fi

## sin virtualenv

# if [ -x "$(command -v virtualenv)" ]; then
#   echo 'Ya tiene instalado virtualenv python3' >&2
# else
#   echo 'Instalando virtualenv python3'
#   pip install virtualenv
#   /usr/bin/easy_install virtualenv
# fi
# return 1
# echo "Instalando virtualenv en el proyecto"
# virtualenv -p python3 .virtualenv
#
# echo "Accediendo al virtualenv"
# source .virtualenv/bin/activate
#
echo "Instalando dependencias de python3"
pip3 install -r requirements.txt

echo "Terminado de instalar"
echo "
_   ,--()
 ( )-'-.------|>
  \"     \`--[]
"
## ejecutar servidor en background
## ejecutar ingresar al virtualenv python

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
