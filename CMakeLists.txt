    cmake_minimum_required(VERSION 2.8)

option(BUILD_VIDEOPLAYER_DEMO "Build the videoplayer demo" ON)

set(OGRE_FFMPEG_VIDEOPLAYER_LIBRARY "ogre-ffmpeg-videoplayer")
set(OGRE_FFMPEG_VIDEOPLAYER_LIBRARY ${OGRE_FFMPEG_VIDEOPLAYER_LIBRARY} PARENT_SCOPE)

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

# Sources

set(OGRE_FFMPEG_VIDEOPLAYER_SOURCE_FILES
    src/videoplayer.cpp
    src/videostate.cpp
    src/videodefs.hpp
    src/libavwrapper.cpp
    src/audiodecoder.cpp
    src/audiofactory.hpp
)

# Find FFMPEG
set(FFmpeg_FIND_COMPONENTS AVCODEC AVFORMAT AVUTIL SWSCALE SWRESAMPLE AVRESAMPLE)
unset(FFMPEG_LIBRARIES CACHE)
find_package(FFmpeg)
if ( NOT AVCODEC_FOUND OR NOT AVFORMAT_FOUND OR NOT AVUTIL_FOUND OR NOT SWSCALE_FOUND )
    message(FATAL_ERROR "FFmpeg component required, but not found!")
endif()
set(VIDEO_FFMPEG_LIBRARIES ${FFMPEG_LIBRARIES} ${SWSCALE_LIBRARIES})
if( SWRESAMPLE_FOUND )
    add_definitions(-DHAVE_LIBSWRESAMPLE)
    set(VIDEO_FFMPEG_LIBRARIES ${FFMPEG_LIBRARIES} ${SWRESAMPLE_LIBRARIES})
else()
    if( AVRESAMPLE_FOUND )
        set(VIDEO_FFMPEG_LIBRARIES ${FFMPEG_LIBRARIES} ${AVRESAMPLE_LIBRARIES})
    else()
        message(FATAL_ERROR "Install either libswresample (FFmpeg) or libavresample (Libav).")
    endif()
endif()
include_directories(${FFMPEG_INCLUDE_DIRS})

# Find Boost
set(BOOST_COMPONENTS thread)
find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})
include_directories(${Boost_INCLUDE_DIRS})

# Find Ogre
find_package(OGRE REQUIRED)
include_directories(${OGRE_INCLUDE_DIRS})


add_library(${OGRE_FFMPEG_VIDEOPLAYER_LIBRARY} STATIC ${OGRE_FFMPEG_VIDEOPLAYER_SOURCE_FILES})

target_include_directories(${OGRE_FFMPEG_VIDEOPLAYER_LIBRARY} PUBLIC src/)

target_link_libraries(${OGRE_FFMPEG_VIDEOPLAYER_LIBRARY} ${VIDEO_FFMPEG_LIBRARIES} ${Boost_LIBRARIES} ${OGRE_LIBRARIES})

if(BUILD_VIDEOPLAYER_DEMO)
    add_subdirectory(demo)
endif()
