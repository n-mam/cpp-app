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
SET RapidJSON_DIR=D:\vcpkg.1\installed\x64-windows\share\rapidjson  

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

./configure  
make  
sudo make install  
sudo ldconfig  

##### Build cpp-app  
export OPENSSL_ROOT_DIR=~/vcpkg/installed/x64-linux/  
export RapidJSON_DIR=/home/nmam/vcpkg/installed/x64-linux/share/rapidjson  

mkdir build  
cd build  
cmake -DCMAKE_BUILD_TYPE=Debug ..  
cmake --build .  
