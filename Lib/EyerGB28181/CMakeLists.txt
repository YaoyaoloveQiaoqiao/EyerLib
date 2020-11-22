include_directories (../)
include_directories (./)

add_library(
        EyerGB28181
        EyerGB28181.hpp
        SIPServer.cpp
        SIPServer.hpp
)

set(head_files
        EyerGB28181.hpp
        SIPServer.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerGB28181)
INSTALL(
        TARGETS EyerGB28181
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

