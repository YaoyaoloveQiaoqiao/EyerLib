include_directories (../)
include_directories (./)

add_library(
        MBGPUDomino

        MBGomino.cpp
        MBGominoPip.cpp
        MBGominoGaussianBlur.cpp
        MBGaussianBlurComponent.cpp
        MBGominoCopy.cpp
        MBCopyTextureComponent.cpp
        MBGominoZoomBlur.cpp
        MBCommonComponent.cpp
        MBCommonParams.cpp
)

target_link_libraries (MBGPUDomino MBCore)
target_link_libraries (MBGPUDomino pthread)
target_link_libraries (MBGPUDomino gtest)
target_link_libraries (MBGPUDomino MBGL)
target_link_libraries (MBGPUDomino MBType)

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
        MBGPUDomino.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/MBGPUDomino)
INSTALL(
        TARGETS MBGPUDomino
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
