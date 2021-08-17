cmake_minimum_required(VERSION 3.0)

# set(CMAKE_VERBOSE_MAKEFILE ON)

# SET wxWidgets_ROOT_DIR=d:\wxWidgets-3.1.2
# SET OPENSSL_ROOT_DIR=D:/vcpkg.1/installed/x64-windows
# export OPENSSL_ROOT_DIR=/home/nmam/vcpkg/installed/x64-linux

project(cpp-app)

if (UNIX)
  set(wxWidgets_CONFIG_OPTIONS --toolkit=gtk3 --prefix=/usr/local)
endif(UNIX)

find_package(OpenSSL REQUIRED)
find_package(wxWidgets COMPONENTS core base richtext adv html xml REQUIRED)

include(${wxWidgets_USE_FILE})

set(SRC_FILES App.cpp AppFrame.cpp)

if (WIN32)
  list(APPEND SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/sample.rc)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SRC_FILES})

SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../cpp-osl
  ${CMAKE_CURRENT_SOURCE_DIR}/../cpp-osl/INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}/../cpp-npl
  ${CMAKE_CURRENT_SOURCE_DIR}/../cpp-npl/INCLUDE 
)

target_link_libraries(
  ${PROJECT_NAME} 
  ${wxWidgets_LIBRARIES}
  OpenSSL::SSL
  OpenSSL::Crypto
)

if (WIN32)
  target_link_libraries(
    ${PROJECT_NAME}
    Ws2_32.lib 
  )
endif(WIN32)

if (WIN32)
  SET (CMAKE_CXX_FLAGS_RELEASE "/Zi /Od")
  SET_TARGET_PROPERTIES(
   ${PROJECT_NAME} PROPERTIES LINK_FLAGS 
   "/DEBUG /OPT:REF /OPT:ICF"
  )
endif (WIN32)

if (WIN32)
  add_custom_command(
    TARGET 
    ${PROJECT_NAME}
    POST_BUILD
    COMMAND "mt.exe" -manifest \"${CMAKE_CURRENT_SOURCE_DIR}\\manifest.xml\" -inputresource:\"$<TARGET_FILE:cpp-app>\"\;\#1 -outputresource:\"$<TARGET_FILE:cpp-app>\"\;\#1
  )
endif (WIN32)
