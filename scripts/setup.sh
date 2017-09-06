## https://github.com/robertalks/udev-examples
## https://github.com/zserge/jsmn/blob/master/example/simple.c
## https://www.gnu.org/software/libmicrohttpd/
min=0
if [ -x "$(command -v make)" ]; then
  echo -e '\e[41mYa tiene instalado make\e[0m'
else
  echo -e '\e[41mInstalando make\e[0m'
  apt-get install make -y
fi

if [ -x "$(command -v gcc)" ]; then
  echo -e '\e[41mYa tiene instalado gcc\e[0m'
else
  echo -e '\e[41mInstalando gcc\e[0m'
  apt-get install gcc -y
fi

if [ -x "$(command -v wget)" ]; then
  echo -e '\e[41mYa tiene instalado wget\e[0m'
else
  echo -e '\e[41mInstalando wget\e[0m'
  apt-get install wget -y
fi

if [ -x "$(command -v git)" ]; then
  echo -e '\e[41mYa tiene instalado git\e[0m'
else
  echo -e '\e[41mInstalando git\e[0m'
  apt-get install git -y
fi

## INSTALANDO libmicrohttpd
libhttp=$(ldconfig -p | grep libmicrohttpd | wc -l)

if [ "$libhttp" -eq  "$min" ]; then
  echo -e '\e[41mInstalando libmicrohttpd\e[0m'
  apt-get install libmicrohttpd* -y 
else
  echo -e '\e[41mYa tiene instalado libmicrohttpd\e[0m'
fi

## INSTALANDO libudev
libudev=$(ldconfig -p | grep libudev-dev | wc -l)

if [ "$libudev" -eq  "$min" ]; then
  echo -e '\e[41mInstalando libudev\e[0m'
  apt-get install libudev-dev -y
else
  echo -e '\e[41mYa tiene instalado libudev\e[0m'
fi

libjson=$(ldconfig -p | grep libjson0 | wc -l)

if [ "$libjson" -eq  "$min"  ]; then
  echo -e '\e[41mInstalando libjson\e[0m'
  apt-get install libjson0 libjson0-dev -y
else
  echo -e '\e[41mYa tiene instalado libjson\e[0m'
fi

## dependencias en python
echo -e "\e[41mInstalando dependencias de python pip 3\e[0m"

if [ -x "$(command -v pip3)" ]; then
  echo -e '\e[41mYa tiene instalado pip python3\e[0m'
else
  echo -e '\e[41mInstalando pip python3-pip\e[0m'
  apt-get install python3-pip -y
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
echo -e "\e[41mInstalando dependencias de python3\e[0m"
pip3 install -r requirements.txt

echo "
_   ,--()
 ( )-'-.------|>
  \"     \`--[]
"
echo ""
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
