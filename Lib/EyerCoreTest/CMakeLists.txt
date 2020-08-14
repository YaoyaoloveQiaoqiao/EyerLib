add_executable(
    EyerCoreTest
    Main.cpp
    )

include_directories (../)

target_link_libraries (EyerCoreTest EyerGL)
target_link_libraries (EyerCoreTest EyerCore)
target_link_libraries (EyerCoreTest gtest)

INSTALL(
    TARGETS EyerCoreTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
    )