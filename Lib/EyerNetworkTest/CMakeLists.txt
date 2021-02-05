add_executable(
        EyerNetworkTest
        Main.cpp
        UDPThreadTest.hpp SIPTest.h)

include_directories (../)

target_link_libraries (EyerNetworkTest EyerNetwork)
target_link_libraries (EyerNetworkTest EyerThread)
target_link_libraries (EyerNetworkTest EyerCore)
target_link_libraries (EyerNetworkTest EyerSIP)

# target_link_libraries (EyerNetworkTest ws2_32)
target_link_libraries (EyerNetworkTest osipparser2)
target_link_libraries (EyerNetworkTest gtest)

INSTALL(
        TARGETS EyerNetworkTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)