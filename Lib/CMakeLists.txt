PROJECT(EYE_Lib)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/)

include_directories (googletest/googletest/include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")


FUNCTION(ModuleOption moduleName)
IF (${moduleName})
ADD_SUBDIRECTORY(${moduleName})
ENDIF(${moduleName})
ENDFUNCTION(myfunction)

OPTION(EyerCore         "option for EyerCore"           ON)
ModuleOption(EyerCore)

OPTION(EyerAV           "option for EyerAV"             ON)
ModuleOption(EyerAV)

OPTION(EyerCrop         "option for EyerCrop"           ON)
ModuleOption(EyerCrop)

OPTION(EyerGLAD         "option for EyerGLAD"           ON)
ModuleOption(EyerGLAD)

OPTION(EyerGL           "option for EyerGL"             ON)
ModuleOption(EyerGL)

OPTION(EyerYUV           "option for EyerYUV"           ON)
ModuleOption(EyerYUV)

OPTION(EyerGLWindow      "option for EyerGLWindow"      ON)
ModuleOption(EyerGLWindow)

OPTION(EyerType          "option for EyerType"          ON)
ModuleOption(EyerType)

OPTION(EyerGPUDomino     "option for EyerGPUDomino"     ON)
ModuleOption(EyerGPUDomino)

OPTION(EyerGLShader      "option for EyerGLShader"      ON)
ModuleOption(EyerGLShader)

OPTION(EyerThread        "option for EyerThread"        ON)
ModuleOption(EyerThread)

OPTION(EyerImg           "option for EyerImg"           ON)
ModuleOption(EyerImg)

OPTION(EyerVideoTweenAnimation           "option for EyerVideoTweenAnimation"           ON)
ModuleOption(EyerVideoTweenAnimation)

OPTION(AL_TEST           "option for AL_TEST"           OFF)
IF (AL_TEST)
ADD_SUBDIRECTORY(EyerVideoTweenAnimationTest)
ADD_SUBDIRECTORY(EyerCoreTest)
ADD_SUBDIRECTORY(EyerAVTest)
ADD_SUBDIRECTORY(EyerGLTest)
ADD_SUBDIRECTORY(EyerRender)
ADD_SUBDIRECTORY(EyerRenderTest)
ADD_SUBDIRECTORY(EyerTypeTest)
ADD_SUBDIRECTORY(EyerGPUDominoTest)
ADD_SUBDIRECTORY(EyerThreadTest)
ADD_SUBDIRECTORY(EyerEventQueue)
ADD_SUBDIRECTORY(EyerImgTest)
ADD_SUBDIRECTORY(googletest)
ENDIF(AL_TEST)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    ADD_DEFINITIONS(-D EYER_PLATFORM_WINDOWS)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
    ADD_DEFINITIONS(-D EYER_PLATFORM_ANDROID)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
    set(CMAKE_EXE_LINKER_FLAGS
        "-framework IOKit -framework AudioToolbox -framework CoreGraphics -framework CoreMedia -framework Cocoa -framework VideoToolbox -framework AVFoundation -framework Security -framework CoreFoundation -framework CoreVideo -framework OpenGL -framework AppKit -framework CoreImage -framework VideoDecodeAcceleration"
    )
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")