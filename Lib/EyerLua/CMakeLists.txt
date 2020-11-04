include_directories (../)
include_directories (./)

add_library(
        EyerLua
        EyerLua.hpp
        A.cpp
        A.hpp
)

set(head_files
        EyerLua.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerLua)
INSTALL(
        TARGETS EyerLua
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

