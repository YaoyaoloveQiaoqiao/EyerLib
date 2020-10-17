include_directories (../)
include_directories (./)

add_library(
        EyerMP4
        EyerMP4.hpp
        EyerMP4.cpp
        EyerMP4Deserialize.cpp
        EyerMP4Deserialize.hpp
        EyerMP4Box.cpp
        EyerMP4Box.hpp
        EyerMP4Box_ftyp.cpp
        EyerMP4Box_ftyp.hpp
        EyerMP4Constant.hpp
        EyerMP4Box_moov.cpp EyerMP4Box_moov.hpp)

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

