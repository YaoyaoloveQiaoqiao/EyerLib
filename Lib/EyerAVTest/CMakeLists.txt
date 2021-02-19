add_executable(
        EyerAVTest

        Test.cpp

        EyerAVDecoderTest.hpp
        EyerAVEncoderTest.hpp
        Path.hpp
        EyerAVFrameTest.hpp
        EyerAVEncoderSinTest.hpp
        EyerAVDecoderAudioTest.h
        EyerAVBitmapTest.h
        EyerAVPureColorCheck.hpp
        AVGif.hpp
        EyerAVReadImage.h)

include_directories (../)

target_link_libraries (EyerAVTest EyerMP4)
target_link_libraries (EyerAVTest EyerCore)
target_link_libraries (EyerAVTest EyerAV)
target_link_libraries (EyerAVTest EyerGL)
target_link_libraries (EyerAVTest EyerYUV)
target_link_libraries (EyerAVTest EyerDASH)
target_link_libraries (EyerAVTest EyerHttp)
target_link_libraries (EyerAVTest EyerThread)
target_link_libraries (EyerAVTest EyerMP4)
target_link_libraries (EyerAVTest EyerImg)
target_link_libraries (EyerAVTest gtest)

target_link_libraries (
        EyerAVTest
        curl
        xml2
)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo.mp4
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/1.png
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/2.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/3.png
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

INSTALL(
        TARGETS EyerAVTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
