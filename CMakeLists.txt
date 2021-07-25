cmake_minimum_required(VERSION 3.0)

# set(CMAKE_VERBOSE_MAKEFILE ON)
# SET wxWidgets_ROOT_DIR=d:\wxWidgets-3.1.2
# SET RapidJSON_DIR=D:\vcpkg\installed\x64-windows\share\rapidjson

project(cpp-app)

find_package(RapidJSON CONFIG REQUIRED)
find_package(wxWidgets 3.1 COMPONENTS core base REQUIRED)

include(${wxWidgets_USE_FILE})

set(SRC_FILES App.cpp AppFrame.cpp)

if (WIN32)
  list(APPEND SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/sample.rc)
endif(WIN32)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SRC_FILES})

SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp-osl
  ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp-osl/INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp-npl
  ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp-npl/INCLUDE 
)

target_link_libraries(
  ${PROJECT_NAME} 
  ${wxWidgets_LIBRARIES}
  Ws2_32.lib
)

if (WIN32)
  SET (CMAKE_CXX_FLAGS_RELEASE "/Zi /Od")
  SET_TARGET_PROPERTIES(
   ${PROJECT_NAME} PROPERTIES LINK_FLAGS 
   "/DEBUG /OPT:REF /OPT:ICF"
  )
endif (WIN32)
