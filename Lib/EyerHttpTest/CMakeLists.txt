add_executable(
        EyerHttpTest
        Main.cpp
)

include_directories (../)

link_directories(${CMAKE_SOURCE_DIR}/../../Lib/curl_install/lib)

target_link_libraries (EyerHttpTest EyerHttp)
target_link_libraries (EyerHttpTest EyerCore)
target_link_libraries (EyerHttpTest gtest)

target_link_libraries (
        EyerHttpTest
        curl
        )

INSTALL(
        TARGETS EyerHttpTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)