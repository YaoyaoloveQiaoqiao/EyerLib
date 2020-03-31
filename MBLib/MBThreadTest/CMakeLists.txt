add_executable(
    MBThreadTest
    Main.cpp
    )

include_directories (../)

target_link_libraries (MBThreadTest MBCore)
target_link_libraries (MBThreadTest MBThread)

INSTALL(
    TARGETS MBThreadTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
)