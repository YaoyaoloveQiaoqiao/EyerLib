add_executable(
        EyerAVTest

        Test.cpp

        EyerAVDecoderTest.hpp
        EyerAVEncoderTest.hpp
        Path.hpp
        EyerAVFrameTest.hpp
        EyerAVEncoderSinTest.hpp
        EyerAVDecoderAudioTest.h EyerAVBitmapTest.h)

include_directories (../)

target_link_libraries (EyerAVTest EyerCore)
target_link_libraries (EyerAVTest EyerAV)
target_link_libraries (EyerAVTest EyerGL)
target_link_libraries (EyerAVTest EyerYUV)
target_link_libraries (EyerAVTest gtest)

INSTALL(
        TARGETS EyerAVTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
