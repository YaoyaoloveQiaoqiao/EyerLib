add_executable(
        EyerGPUDominoTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerGPUDominoTest EyerCore)
target_link_libraries (EyerGPUDominoTest EyerGL)
target_link_libraries (EyerGPUDominoTest EyerType)
target_link_libraries (EyerGPUDominoTest EyerGPUDomino)

INSTALL(
        TARGETS EyerGPUDominoTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
