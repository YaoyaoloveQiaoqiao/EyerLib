add_executable(
        EyerNetTest
        Main.cpp
)

include_directories (../)

link_directories(${CMAKE_SOURCE_DIR}/../../Lib/curl_install/lib)

target_link_libraries (EyerNetTest EyerNet)
target_link_libraries (EyerNetTest EyerCore)
target_link_libraries (EyerNetTest gtest)

target_link_libraries (
        EyerNetTest
        curl
        )

INSTALL(
        TARGETS EyerNetTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)