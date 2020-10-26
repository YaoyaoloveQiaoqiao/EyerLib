include_directories (../)
include_directories (./)

add_library(
        EyerCAVLC
        EyerCAVLC.hpp
        CAVLC.cpp
        CAVLC.hpp
)

target_link_libraries (
        EyerCore
)

set(head_files
        EyerCAVLC.hpp
        CAVLC.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerCAVLC)
INSTALL(
        TARGETS EyerCAVLC
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

