add_executable(
        EyerMP4Test
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerMP4Test EyerCore)
target_link_libraries (EyerMP4Test EyerMP4)
target_link_libraries (EyerMP4Test gtest)

INSTALL(
        TARGETS EyerMP4Test
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)