PROJECT(EYE_Lib)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/)

include_directories (googletest/googletest/include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    ADD_DEFINITIONS(-D EYER_PLATFORM_WINDOWS)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
    set(CMAKE_EXE_LINKER_FLAGS
        "-framework IOKit -framework AudioToolbox -framework CoreGraphics -framework CoreMedia -framework Cocoa -framework VideoToolbox -framework AVFoundation -framework Security -framework CoreFoundation -framework CoreVideo -framework OpenGL -framework AppKit -framework CoreImage -framework VideoDecodeAcceleration"
    )
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

ADD_SUBDIRECTORY(MBCore)
ADD_SUBDIRECTORY(MBCoreTest)
ADD_SUBDIRECTORY(MBAV)
ADD_SUBDIRECTORY(MBAVTest)
ADD_SUBDIRECTORY(MBGL)
ADD_SUBDIRECTORY(MBGLWindow)
ADD_SUBDIRECTORY(MBGLTest)
ADD_SUBDIRECTORY(MBGLAD)
ADD_SUBDIRECTORY(MBGLCustomComponent)
ADD_SUBDIRECTORY(MBRender)
ADD_SUBDIRECTORY(MBRenderTest)
ADD_SUBDIRECTORY(MBType)
ADD_SUBDIRECTORY(MBTypeTest)
ADD_SUBDIRECTORY(MBYUV)
ADD_SUBDIRECTORY(MBGPUDomino)
ADD_SUBDIRECTORY(MBGPUDominoTest)
ADD_SUBDIRECTORY(MBGLShader)
ADD_SUBDIRECTORY(MBThreadTest)
ADD_SUBDIRECTORY(MBThread)
ADD_SUBDIRECTORY(MBEventQueue)
ADD_SUBDIRECTORY(MBImg)
ADD_SUBDIRECTORY(MBImgTest)

ADD_SUBDIRECTORY(googletest)