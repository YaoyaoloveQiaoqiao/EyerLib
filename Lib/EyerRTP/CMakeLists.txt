include_directories (../)
include_directories (./)

add_library(
        EyerRTP
        EyerRTP.hpp
        EyerRTPServer.cpp
        EyerRTPServer.hpp
        EyerRTPServerThread.cpp EyerRTPServerThread.hpp)

set(head_files
        EyerRTP.hpp
        EyerRTPServer.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerRTP)
INSTALL(
        TARGETS EyerRTP
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

