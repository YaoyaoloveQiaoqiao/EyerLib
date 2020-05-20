include_directories (../)
include_directories (./)

add_library(
        EyerGPUDomino

        EyerGomino.cpp
        EyerGominoPip.cpp
        EyerGominoGaussianBlur.cpp
        EyerGaussianBlurComponent.cpp
        EyerGominoCopy.cpp
        EyerCopyTextureComponent.cpp
        EyerGominoZoomBlur.cpp
        EyerCommonComponent.cpp
        EyerCommonParams.cpp
)

target_link_libraries (EyerGPUDomino EyerCore)
target_link_libraries (EyerGPUDomino pthread)
target_link_libraries (EyerGPUDomino gtest)
target_link_libraries (EyerGPUDomino EyerGL)

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
        EyerGPUDomino.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerGPUDomino)
INSTALL(
        TARGETS EyerGPUDomino
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
