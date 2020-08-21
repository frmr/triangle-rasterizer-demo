cmake_minimum_required (VERSION 3.10)

project (triangle-rasterizer-demo)

set(CMAKE_CXX_STANDARD 17)

add_executable (triangle-rasterizer-demo
	src/main.cpp
	src/trdAmbientLight.cpp
	src/trdApp.cpp
	src/trdCamera.cpp
	src/trdConfig.cpp
	src/trdControlledCamera.cpp
	src/trdDirectionalLight.cpp
	src/trdFrameTimer.cpp
	src/trdHologramManager.cpp
	src/trdInputState.cpp
	src/trdInstructions.cpp
	src/trdLight.cpp
	src/trdLights.cpp
	src/trdMesh.cpp
	src/trdMeshMap.cpp
	src/trdModel.cpp
	src/trdPointLight.cpp
	src/trdRenderManager.cpp
	src/trdRenderThread.cpp
	src/trdScene.cpp
	src/trdSettings.cpp
	src/trdShader.cpp
	src/trdTextRenderer.cpp
	src/trdTextureMap.cpp
	src/trdWindow.cpp
)

target_link_directories(triangle-rasterizer-demo PRIVATE
	tf
	lodepng
	tinyobjloader
	triangle-rasterizer
	triangle-rasterizer-demo
)

find_package(SDL2 REQUIRED)

target_include_directories(triangle-rasterizer-demo PUBLIC
	../triangle-rasterizer/src/tr
	../triangle-rasterizer/src/matrix
	../tf/src
	${SDL2_INCLUDE_DIRS}
)

target_link_libraries(triangle-rasterizer-demo ${SDL2_LIBRARIES})