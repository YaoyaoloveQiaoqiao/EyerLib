include_directories (../)
include_directories (./)

add_library(
        EyerMP4
        EyerMP4Constant.hpp
        EyerMP4.hpp
        EyerMP4.cpp
        EyerMP4Box.cpp
        EyerMP4Box.hpp
        EyerMP4Box_ftyp.cpp
        EyerMP4Box_ftyp.hpp
        EyerMP4Box_moov.cpp
        EyerMP4Box_moov.hpp
        EyerMP4Box_mvhd.cpp EyerMP4Box_mvhd.hpp EyerMP4Box_trak.cpp EyerMP4Box_trak.hpp EyerMP4Box_tkhd.cpp EyerMP4Box_tkhd.hpp EyerMP4Box_edts.cpp EyerMP4Box_edts.hpp EyerMP4Box_mdia.cpp EyerMP4Box_mdia.hpp EyerMP4Box_mdhd.cpp EyerMP4Box_mdhd.hpp)

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

