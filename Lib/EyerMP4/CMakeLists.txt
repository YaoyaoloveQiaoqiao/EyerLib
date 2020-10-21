include_directories (../)
include_directories (./)

add_library(
        EyerMP4
        EyerMP4.hpp
        MP4Box.cpp
        MP4Box.hpp
        BoxType.cpp
        BoxType.hpp
        BoxFTYP.cpp
        BoxFTYP.hpp)

target_link_libraries (
        EyerCore
)

set(head_files
        EyerMP4.hpp
        MP4Box.hpp
        BoxType.hpp
        BoxFTYP.hpp
)

INSTALL(FILES ${head_files} DESTINATION include/EyerMP4)
INSTALL(
        TARGETS EyerMP4
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

