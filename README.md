### cpp-app

ui app for cpp-npl  

### Build

#### Windows  

##### Build wxwidgets  
download wxwidgets 3.1* and build it : 

namke -f makefile.vc BUILD=Release TARGET_CPU=AMD64  

##### Build cpp-app  
SET wxWidgets_ROOT_DIR=d:\wxWidgets-3.1.2  
SET OPENSSL_ROOT_DIR=d:\vcpkg.1\installed\x64-windows   

md build  
cd build  
cmake ..  
cmake --build . --config Release  

#### Linux (debian)

point the compiler to gcc 11  

export CC=/opt/gcc-11/bin/gcc  
export CXX=/opt/gcc-11/bin/g++  

##### Build wxwidgets  
download wxwidgets 3.1* and build it :  

./configure --prefix=/path/to/install/folder  
make  
make install  
sudo ldconfig  

##### Build cpp-app  
export OPENSSL_ROOT_DIR=~/vcpkg/installed/x64-linux/  
export OPENSSL_ROOT_DIR=/Users/neelabh.mam/code/vcpkg/installed/x64-osx

mkdir build  
cd build  
cmake -DCMAKE_BUILD_TYPE=Debug ..  
cmake --build .  

### DPI aware manifest

mt.exe -manifest ..\..\manifest.xml -inputresource:cpp-app.exe;#1 -outputresource:cpp-app.exe;#1