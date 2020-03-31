include_directories (../)
include_directories (./)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/include)
include_directories (../MBGLAD/glad/include/)

add_library(
        MBGL
        MBGL.hpp
        MBGLShader.cpp
        MBGLProgram.cpp
        MBGLVAO.cpp
        MBGLDraw.cpp
        MBGLTexture.cpp
        MBGLFrameBuffer.cpp
        MBGLComponent.cpp
        )

target_link_libraries (MBGL MBCore)
target_link_libraries (MBGL pthread)
target_link_libraries (MBGL gtest)
target_link_libraries (MBGL MBGLAD)
target_link_libraries (MBGL ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        MESSAGE(STATUS "current platform: Linux")
        target_link_libraries (MBGL dl)
        target_link_libraries (MBGL X11)
        target_link_libraries (MBGL bz2)
        target_link_libraries (MBGL z)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
        MESSAGE(STATUS "current platform: Windows")
        target_link_libraries (MBGL bz2)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
        MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        MESSAGE(STATUS "current platform: Darwin")
ELSE ()
        MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(head_files
        MBGL.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/MBGL)
INSTALL(
        TARGETS MBGL
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
