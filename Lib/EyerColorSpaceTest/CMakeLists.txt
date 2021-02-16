add_executable(
        EyerColorSpaceTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerColorSpaceTest EyerColorSpace)
target_link_libraries (EyerColorSpaceTest EyerMath)
target_link_libraries (EyerColorSpaceTest EyerCore)
target_link_libraries (EyerColorSpaceTest EyerThread)
target_link_libraries (EyerColorSpaceTest gtest)

INSTALL(
        TARGETS EyerColorSpaceTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)