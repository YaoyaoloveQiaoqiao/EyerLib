add_executable(
        EyerRTPTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerRTPTest EyerRTP)

INSTALL(
        TARGETS EyerRTPTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)