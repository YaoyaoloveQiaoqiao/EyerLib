add_executable(
    MBCoreTest
    Main.cpp
    )

include_directories (../)

target_link_libraries (MBCoreTest MBGL)
target_link_libraries (MBCoreTest MBCore)

INSTALL(
    TARGETS MBCoreTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
    )