include_directories (../)
include_directories (./)

add_library(
        EyerMP4
        EyerMP4.hpp
        EyerMP4.cpp

        mp4.h
        mp4.c
        stream.c
        stream.h
)

target_link_libraries (
        EyerCore
)

set(head_files
        EyerMP4.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerMP4)
INSTALL(
        TARGETS EyerMP4
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

