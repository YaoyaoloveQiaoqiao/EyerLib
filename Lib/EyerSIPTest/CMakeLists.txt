add_executable(
        EyerSIPTest
        Main.cpp
        SIPMessgae.hpp)

include_directories (../)

target_link_libraries (EyerSIPTest EyerSIP)
target_link_libraries (EyerSIPTest EyerCore)
target_link_libraries (EyerSIPTest EyerSIP)
target_link_libraries (EyerSIPTest osipparser2)
target_link_libraries (EyerSIPTest gtest)

INSTALL(
        TARGETS EyerSIPTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)