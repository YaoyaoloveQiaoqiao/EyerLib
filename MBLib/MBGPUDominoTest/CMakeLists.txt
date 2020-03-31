add_executable(
        MBGPUDominoTest
        Main.cpp
)

include_directories (../)

target_link_libraries (MBGPUDominoTest MBCore)
target_link_libraries (MBGPUDominoTest MBGL)
target_link_libraries (MBGPUDominoTest MBType)
target_link_libraries (MBGPUDominoTest MBGPUDomino)

INSTALL(
        TARGETS MBGPUDominoTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
