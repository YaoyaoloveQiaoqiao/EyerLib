include_directories (../)
include_directories (./)

add_library(
        EyerCodecCommon
        EyerCodecCommon.hpp
        EyerSyntax.hpp
        EyerSyntax.cpp
)

target_link_libraries (
        EyerCodecCommon
        EyerCore
)

set(head_files
        EyerCodecCommon.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerCodecCommon)
INSTALL(
        TARGETS EyerCodecCommon
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

