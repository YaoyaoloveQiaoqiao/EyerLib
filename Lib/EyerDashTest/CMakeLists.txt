add_executable(
        EyerDASHTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerDASHTest EyerDASH)
target_link_libraries (EyerDASHTest EyerHttp)
target_link_libraries (EyerDASHTest EyerCore)
target_link_libraries (EyerDASHTest gtest)

target_link_libraries (
        EyerDASHTest
        curl
        xml2
)

INSTALL(
        TARGETS EyerDASHTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)