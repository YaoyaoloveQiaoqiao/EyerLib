include_directories (../)
include_directories (./)

add_library(
        EyerMP4
        EyerMP4.hpp
        MP4Box.cpp
        MP4Box.hpp
        BoxType.cpp
        BoxType.hpp
        MP4BoxFTYP.cpp
        MP4BoxFTYP.hpp
        MP4File.cpp
        MP4File.hpp
        MP4BoxMVHD.cpp MP4BoxMVHD.hpp MP4FullBox.cpp MP4FullBox.hpp MP4BoxTKHD.cpp MP4BoxTKHD.hpp EyerISOTypeReader.cpp EyerISOTypeReader.hpp)

target_link_libraries (
        EyerCore
)

set(head_files
        EyerMP4.hpp
        MP4Box.hpp
        BoxType.hpp
        MP4BoxFTYP.hpp
)

INSTALL(FILES ${head_files} DESTINATION include/EyerMP4)
INSTALL(
        TARGETS EyerMP4
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

