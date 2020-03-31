add_executable(
    MBRenderTest
    Main.cpp
    )

include_directories (../)

target_link_libraries (MBRenderTest MBRender)

INSTALL(
    TARGETS MBRenderTest
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib        
    ARCHIVE DESTINATION lib
    )