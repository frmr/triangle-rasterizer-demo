cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(triangle-rasterizer-demo)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(triangle-rasterizer-demo
	${LODEPNG_SOURCES}
	${TF_SOURCES}
	${TINYOBJLOADER_SOURCES}
	${TRIANGLE_RASTERIZER_SOURCES}
	${TRIANGLE_RASTERIZER_DEMO_SOURCES}
)

find_package(SDL2 REQUIRED)

target_link_directories(triangle-rasterizer-demo PRIVATE
	tf
	triangle-rasterizer
	${SDL2_LIBRARIES}
)

target_include_directories(triangle-rasterizer-demo PUBLIC
	../triangle-rasterizer/src/tr
	../triangle-rasterizer/src/matrix
	../tf/src
	${SDL2_INCLUDE_DIRS}
)