cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(triangle-rasterizer-demo)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pthread -lm")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(TF_SOURCES
	src/tf/src/tfBinaryFile.cpp
	src/tf/src/tfCsvFile.cpp
	src/tf/src/tfIniFile.cpp
	src/tf/src/tfIniFile.hpp
	src/tf/src/tfIniSection.cpp
	src/tf/src/tfLogger.cpp
	src/tf/src/tfString.cpp
	src/tf/src/tfStringW.cpp
	src/tf/src/tfTextFile.cpp
	src/tf/src/tfTime.cpp
	src/tf/src/tfTimer.cpp
)

set(TINYOBJLOADER_SOURCES
	src/tinyobjloader/src/tiny_obj_loader.cc
)

set(TRIANGLE_RASTERIZER_SOURCES
	src/triangle-rasterizer/src/matrix/Matrices.cpp
	src/triangle-rasterizer/src/tr/trDefaultShader.cpp
	src/triangle-rasterizer/src/tr/trDepthShader.cpp
	src/triangle-rasterizer/src/tr/trTexture.cpp
	src/triangle-rasterizer/src/tr/trTransformedVertex.cpp
)

set(TRIANGLE_RASTERIZER_DEMO_SOURCES
	src/triangle-rasterizer-demo/src/main.cpp
	src/triangle-rasterizer-demo/src/trdAmbientLight.cpp
	src/triangle-rasterizer-demo/src/trdApp.cpp
	src/triangle-rasterizer-demo/src/trdCamera.cpp
	src/triangle-rasterizer-demo/src/trdConfig.cpp
	src/triangle-rasterizer-demo/src/trdControlledCamera.cpp
	src/triangle-rasterizer-demo/src/trdDirectionalLight.cpp
	src/triangle-rasterizer-demo/src/trdFrameTimer.cpp
	src/triangle-rasterizer-demo/src/trdHologramManager.cpp
	src/triangle-rasterizer-demo/src/trdInputState.cpp
	src/triangle-rasterizer-demo/src/trdInstructions.cpp
	src/triangle-rasterizer-demo/src/trdLight.cpp
	src/triangle-rasterizer-demo/src/trdLights.cpp
	src/triangle-rasterizer-demo/src/trdMesh.cpp
	src/triangle-rasterizer-demo/src/trdMeshMap.cpp
	src/triangle-rasterizer-demo/src/trdModel.cpp
	src/triangle-rasterizer-demo/src/trdPointLight.cpp
	src/triangle-rasterizer-demo/src/trdRenderManager.cpp
	src/triangle-rasterizer-demo/src/trdRenderThread.cpp
	src/triangle-rasterizer-demo/src/trdScene.cpp
	src/triangle-rasterizer-demo/src/trdSettings.cpp
	src/triangle-rasterizer-demo/src/trdShader.cpp
	src/triangle-rasterizer-demo/src/trdTextRenderer.cpp
	src/triangle-rasterizer-demo/src/trdTextureMap.cpp
	src/triangle-rasterizer-demo/src/trdWindow.cpp
)

set(LODEPNG_SOURCES
	src/lodepng/src/lodepng.cpp
)

add_executable(triangle-rasterizer-demo
	${LODEPNG_SOURCES}
	${TF_SOURCES}
	${TINYOBJLOADER_SOURCES}
	${TRIANGLE_RASTERIZER_SOURCES}
	${TRIANGLE_RASTERIZER_DEMO_SOURCES}
)

add_subdirectory(src/sdl)

target_include_directories(triangle-rasterizer-demo PUBLIC
	src/triangle-rasterizer/src/tr
	src/triangle-rasterizer/src/matrix
	src/tf/src
	src/lodepng/src
	src/tinyobjloader/src
	src/sdl/include
)

target_link_libraries(triangle-rasterizer-demo SDL2 SDL2main)
