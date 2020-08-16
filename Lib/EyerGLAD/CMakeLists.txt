include_directories (../)
include_directories (./)
include_directories (../EyerGLAD/glad/include/)

add_library(
        EyerGLAD
        glad/src/glad.c
        )

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        MESSAGE(STATUS "current platform: Linux")
        target_link_libraries (EyerGLAD dl)
        target_link_libraries (EyerGLAD X11)
        target_link_libraries (EyerGLAD bz2)
        target_link_libraries (EyerGLAD z)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
        MESSAGE(STATUS "current platform: Windows")
        target_link_libraries (EyerGLAD bz2)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
        MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        MESSAGE(STATUS "current platform: Darwin")
ELSE ()
        MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(head_files
        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerGLAD)

INSTALL(FILES glad/include/glad/glad.h DESTINATION include/glad)
INSTALL(FILES glad/include/KHR/khrplatform.h DESTINATION include/KHR)

INSTALL(
        TARGETS EyerGLAD
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
