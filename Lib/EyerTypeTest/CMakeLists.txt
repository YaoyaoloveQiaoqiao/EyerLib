add_executable(
        EyerTypeTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerTypeTest gtest)
target_link_libraries (EyerTypeTest EyerCore)
target_link_libraries (EyerTypeTest EyerType)
target_link_libraries (EyerTypeTest EyerGL)
target_link_libraries (EyerTypeTest EyerGLWindow)

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

    target_link_libraries (EyerTypeTest dl)
    target_link_libraries (EyerTypeTest bz2)
    target_link_libraries (EyerTypeTest z)
    target_link_libraries (EyerTypeTest EyerGLAD)
    # target_link_libraries (EyerTypeTest harfbuzz)

    target_link_libraries (EyerTypeTest ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")



file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/xiao_xiao_yuan_pin_ying.ttf
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

INSTALL(
        TARGETS EyerTypeTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
