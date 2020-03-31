include_directories (../)
include_directories (./)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/include)
include_directories (../MBGLAD/glad/include/)

add_library(
        MBGLCustomComponent
        MBGLCustomComponent.hpp
        MBGLTextDraw.cpp
        MBGLMVPTextureDraw.cpp
        MBGLFrameDraw.cpp
        MBGLSingleTextureDraw.cpp
        MBGLYUV2TextureComponent.cpp
        )

target_link_libraries (MBGLCustomComponent MBCore)
target_link_libraries (MBGLCustomComponent pthread)
target_link_libraries (MBGLCustomComponent gtest)
target_link_libraries (MBGLCustomComponent MBType)
target_link_libraries (MBGLCustomComponent MBGL)
target_link_libraries (MBGLCustomComponent MBGLAD)
target_link_libraries (MBGLCustomComponent ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        MESSAGE(STATUS "current platform: Linux")
        target_link_libraries (MBGLCustomComponent dl)
        target_link_libraries (MBGLCustomComponent X11)
        target_link_libraries (MBGLCustomComponent bz2)
        target_link_libraries (MBGLCustomComponent z)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
        MESSAGE(STATUS "current platform: Windows")
        target_link_libraries (MBGLCustomComponent bz2)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
        MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        MESSAGE(STATUS "current platform: Darwin")
ELSE ()
        MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(head_files
        MBGLCustomComponent.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/MBGLCustomComponent)
INSTALL(
        TARGETS MBGLCustomComponent
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
