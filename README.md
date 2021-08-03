### cpp-app

ui app for cpp-npl  

### Build

#### Windows  
SET wxWidgets_ROOT_DIR=d:\wxWidgets-3.1.2  
SET RapidJSON_DIR=D:\vcpkg.1\installed\x64-windows\share\rapidjson  

md build  
cd build  
cmake ..  
cmake --build . --config Release  

#### Linux (debian)
download wxwidgets 3.1* and build it the usual way;
./configure
make
make install

export OPENSSL_ROOT_DIR=~/vcpkg/installed/x64-linux/  
export RapidJSON_DIR=/home/nmam/vcpkg/installed/x64-linux/share/rapidjson  

cmake -DCMAKE_BUILD_TYPE=Debug ..  
cmake --build . 
