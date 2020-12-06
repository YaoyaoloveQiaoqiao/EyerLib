add_executable(
        EyerYUVTest
        Main.cpp
)

include_directories (../)



target_link_libraries (EyerYUVTest EyerYUV)
target_link_libraries (EyerYUVTest EyerMP4)
target_link_libraries (EyerYUVTest EyerHttp)
target_link_libraries (EyerYUVTest EyerDASH)
target_link_libraries (EyerYUVTest EyerAV)
target_link_libraries (EyerYUVTest EyerCore)
target_link_libraries (EyerYUVTest EyerThread)
target_link_libraries (EyerYUVTest gtest)

target_link_libraries (
        EyerYUVTest
        curl
        xml2
)

INSTALL(
        TARGETS EyerYUVTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo_video.mp4
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )
