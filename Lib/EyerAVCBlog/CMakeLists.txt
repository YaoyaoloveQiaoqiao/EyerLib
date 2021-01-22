include_directories (../)
include_directories (./)

add_library(
        EyerAVCBlog
        AnnexBReader.hpp
        AnnexBReader.cpp
        BitStream.cpp BitStream.hpp)

set(head_files
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerAVCBlog)
INSTALL(
        TARGETS EyerAVCBlog
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

