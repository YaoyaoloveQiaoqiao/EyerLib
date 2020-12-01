add_executable(
        EyerPJSIPTest
        Main2.cpp)

include_directories (../)

target_link_libraries (EyerPJSIPTest gtest)
target_link_libraries (EyerPJSIPTest EyerPJSIP)
target_link_libraries (EyerPJSIPTest EyerCore)


target_link_libraries (
        EyerPJSIPTest
        pjsua-x86_64-apple-darwin19.6.0
        pjsip-ua-x86_64-apple-darwin19.6.0
        pjsip-x86_64-apple-darwin19.6.0
        pjsip-simple-x86_64-apple-darwin19.6.0
        pj-x86_64-apple-darwin19.6.0
        pjlib-util-x86_64-apple-darwin19.6.0
        pjmedia-x86_64-apple-darwin19.6.0
        )

INSTALL(
        TARGETS EyerPJSIPTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)