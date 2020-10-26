include_directories (../)
include_directories (./)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/include)
include_directories (../EyerGLAD/glad/include/)

add_library(
    EyerGLCustomComponent
    
    EyerGLCustomComponent.hpp

    EyerGLTextMeshDraw.cpp
    EyerGLFrameDraw.cpp
    EyerGLJulia.cpp
    EyerGLMVPTextureDraw.cpp
    EyerGLSingleTextureDraw.cpp
    EyerGLTest.cpp
    EyerGLTextDraw.cpp
    EyerGLYUV2TextureComponent.cpp
    EyerGLChessboard.cpp
    )

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(head_files
    EyerGLCustomComponent.hpp
    )

INSTALL(FILES ${head_files} DESTINATION include/EyerGLCustomComponent)
INSTALL(
    TARGETS EyerGLCustomComponent
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
