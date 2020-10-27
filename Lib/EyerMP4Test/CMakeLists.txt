add_executable(
        EyerMP4Test
        Main.cpp
        STTSTest.hpp
        STSCTest.hpp
        STCOTest.hpp MEHDTest.hpp Endian.hpp FTYPTest.hpp Read_fMP4Test.hpp MVHDTest.hpp TKHDTest.hpp Read_MP4Test.hpp ELSTTest.hpp HDLRTest.hpp TREXTest.hpp)

include_directories (../)

target_link_libraries (EyerMP4Test EyerMP4)
target_link_libraries (EyerMP4Test EyerCore)
target_link_libraries (EyerMP4Test gtest)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo.mp4
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/xiaomai_dashinit.mp4
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )


INSTALL(
        TARGETS EyerMP4Test
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)