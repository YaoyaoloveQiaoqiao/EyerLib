include_directories (../)
include_directories (./)

add_library(
        EyerGB28181
        EyerGB28181.hpp
        SIPServer.cpp
        SIPServer.hpp
        SIPServerMainThread.cpp
        SIPServerMainThread.hpp
        eXosipHeader.hpp
        SIPProcess.cpp
        SIPProcess.hpp
        SIPProcessRegister.cpp
        SIPProcessRegister.hpp
        SIPProcessMessage.cpp SIPProcessMessage.hpp)

set(head_files
        EyerGB28181.hpp
        SIPServer.hpp
        SIPServerMainThread.hpp
        SIPProcess.hpp
        SIPProcessRegister.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerGB28181)
INSTALL(
        TARGETS EyerGB28181
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

