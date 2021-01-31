add_executable(
        EyerSignalTest
        Main.cpp
        GenRGBWImage.h DCT.hpp)

include_directories (../)

target_link_libraries (EyerSignalTest EyerCore)
target_link_libraries (EyerSignalTest EyerThread)
target_link_libraries (EyerSignalTest gtest)
target_link_libraries (EyerSignalTest yuv)

INSTALL(
        TARGETS EyerSignalTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)