add_executable(
        EyerDashTest
        Main.cpp
)

include_directories (../)

link_directories(${CMAKE_SOURCE_DIR}/../../Lib/curl_install/lib)
link_directories(${CMAKE_SOURCE_DIR}/../../Lib/libxml2_install/lib)

target_link_libraries (EyerDashTest EyerDASH)
target_link_libraries (EyerDashTest EyerNet)
target_link_libraries (EyerDashTest EyerCore)
target_link_libraries (EyerDashTest gtest)

target_link_libraries (
        EyerDashTest
        curl
        xml2
)

INSTALL(
        TARGETS EyerDashTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)