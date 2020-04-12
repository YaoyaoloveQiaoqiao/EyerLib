add_executable(
        MBImgTest
        Main.cpp
    )

include_directories (../)

target_link_libraries (MBImgTest MBCore)
target_link_libraries (MBImgTest MBImg)

INSTALL(
    TARGETS MBImgTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
)