set(PROJECT_NAME "ogre-ffmpeg-videoplayer-demo")

project(${PROJECT_NAME} CXX C)
cmake_minimum_required(VERSION 2.8)

# We want the binaries to be easily accessible
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_definitions(-DOGRE_PLUGIN_DIR_REL="${OGRE_PLUGIN_DIR_REL}")
add_definitions(-DOGRE_PLUGIN_DIR_DBG="${OGRE_PLUGIN_DIR_DBG}")

find_package(SDL2 REQUIRED)
find_package(OIS REQUIRED)

# The project's sources
file(GLOB PROJECT_SOURCES
	Application.cpp
    BaseApplication.cpp
    main.cpp
    SDLMovieAudioFactory.cpp
)

include_directories(${SDL2_INCLUDE_DIR} ${OIS_INCLUDE_DIRS} ${OGRE_INCLUDE_DIR} ${OGRE_Overlay_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS} ${OGRE_LIB_DIR} ${Boost_LIBRARY_DIRS})

# Now compile the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} ${OGRE_LIBRARIES} ${OGRE_Overlay_LIBRARIES} ${SDL2_LIBRARY} ${OIS_LIBRARY} "ogre-ffmpeg-videoplayer")
