include_directories (../)
include_directories (./)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/libosip2_install/include)

add_library(
        EyerNetwork
        EyerNetwork.hpp
        EyerUDP.hpp
        EyerUDP.cpp
        EyerUDPThread.cpp EyerUDPThread.hpp EyerUDPCallback.cpp EyerUDPCallback.hpp)

target_link_libraries (
        EyerCore
)

set(head_files
        EyerNetwork.hpp
        EyerUDP.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerNetwork)
INSTALL(
        TARGETS EyerNetwork
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

