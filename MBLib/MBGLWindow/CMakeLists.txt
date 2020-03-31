include_directories (../)
include_directories (./)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/include)
include_directories (../MBGLAD/glad/include/)

add_library(
        MBGLWindow
        MBGLWindow.hpp
        MBGLWindow.cpp
        )

target_link_libraries (MBGLWindow MBCore)
target_link_libraries (MBGLWindow pthread)
target_link_libraries (MBGLWindow gtest)
target_link_libraries (MBGLWindow MBType)
target_link_libraries (MBGLWindow MBGLAD)
target_link_libraries (MBGLWindow ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        MESSAGE(STATUS "current platform: Linux")
        target_link_libraries (MBGLWindow dl)
        target_link_libraries (MBGLWindow X11)
        target_link_libraries (MBGLWindow bz2)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
        MESSAGE(STATUS "current platform: Windows")
        target_link_libraries (MBGLWindow bz2)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
        MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        MESSAGE(STATUS "current platform: Darwin")
ELSE ()
        MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(head_files
        MBGLWindow.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/MBGLWindow)
INSTALL(
        TARGETS MBGLWindow
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
