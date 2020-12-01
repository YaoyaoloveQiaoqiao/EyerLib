include_directories (../)
include_directories (./)

add_library(
        EyerPJSIP
        EyerPJSIP.hpp
        PJ.hpp
        PJ.cpp
)

set(head_files
        EyerPJSIP.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerPJSIP)
INSTALL(
        TARGETS EyerPJSIP
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

