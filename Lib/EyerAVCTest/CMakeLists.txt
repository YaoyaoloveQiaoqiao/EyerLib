add_executable(
        EyerAVCTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerAVCTest EyerCore)
target_link_libraries (EyerAVCTest EyerAVC)
target_link_libraries (EyerAVCTest gtest)

INSTALL(
        TARGETS EyerAVCTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)