add_executable(
    EyerCoreTest
    Main.cpp
        MD5Test.hpp)

include_directories (../)

target_link_libraries (EyerCoreTest EyerCore)
target_link_libraries (EyerCoreTest EyerThread)
target_link_libraries (EyerCoreTest gtest)

INSTALL(
    TARGETS EyerCoreTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
    )