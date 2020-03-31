add_executable(
        MBAVTest

        Test.cpp

        MBAVDecoderTest.hpp
        MBAVEncoderTest.hpp
        Path.hpp
        MBAVFrameTest.hpp
        MBAVEncoderSinTest.hpp
        MBAVDecoderAudioTest.h MBAVBitmapTest.h)

include_directories (../)

target_link_libraries (MBAVTest MBCore)
target_link_libraries (MBAVTest MBAV)
target_link_libraries (MBAVTest MBGL)
target_link_libraries (MBAVTest MBYUV)

INSTALL(
        TARGETS MBAVTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
