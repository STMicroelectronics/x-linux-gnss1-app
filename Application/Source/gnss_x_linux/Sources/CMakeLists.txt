# CMakeLists text file of the project
# RFAL code release version 1.0

cmake_minimum_required(VERSION 3.1.0)

project(gnss_app)

include_directories(
    ../Sources/cloud
    ../Sources/Drivers/BSP/Components/Common
    ../Sources/Drivers/BSP/Components/teseo_liv3f
    ../Sources/Drivers/BSP/GNSS1A1
    ../Sources/Inc
    ../Sources/Middlewares/ST/lib_gnss/LibGNSS/Inc
    ../Sources/Middlewares/ST/lib_gnss/LibNMEA/Inc)
    
file(GLOB SOURCE1 "../Sources/Src/*.c")
file(GLOB SOURCE2 "../Sources/Middlewares/ST/lib_gnss/LibGNSS/Src/*.c")
file(GLOB SOURCE3 "../Sources/Middlewares/ST/lib_gnss/LibNMEA/Src/*.c")
file(GLOB SOURCE4 "../Sources/Drivers/BSP/Components/teseo_liv3f/*.c")
file(GLOB SOURCE5 "../Sources/Drivers/BSP/GNSS1A1/*.c")
file(GLOB SOURCE6 "../Sources/cloud/*.c")
set(SOURCES ${SOURCE1} ${SOURCE2} ${SOURCE3} ${SOURCE4} ${SOURCE5} ${SOURCE6})


# RFAL library variant to link the executable with
#set(RFAL_VARIANT "st25r3911" CACHE STRING "Select the RFAL library")

# Compile the RFAL library variant to link the executable with
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g -Wall")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set( CURL_LIBRARY ${CMAKE_SOURCE_DIR}/lib )
set( CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include )
#find_package( CURL )

#include_directories( ${CURL_INCLUDE_DIRS} )
#link_directories( ${CURL_LIBRARIES} )


set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR})

add_executable(gnss_app ${SOURCES})
#target_link_libraries(gnss_app edit readline)
target_link_libraries(gnss_app m)
#target_link_libraries(gnss_app curl)
#target_link_libraries(gnss_app pthread)
target_link_libraries(gnss_app pthread)
target_link_libraries(gnss_app ${CURL_LIBRARIES})

