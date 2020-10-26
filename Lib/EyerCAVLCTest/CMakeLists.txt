add_executable(
        EyerCAVLCTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerCAVLCTest EyerCore)
target_link_libraries (EyerCAVLCTest EyerCAVLC)
target_link_libraries (EyerCAVLCTest gtest)

INSTALL(
        TARGETS EyerCAVLCTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)