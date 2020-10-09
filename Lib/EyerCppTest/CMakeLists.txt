add_executable(
        EyerCppTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerCppTest gtest)

INSTALL(
        TARGETS EyerCppTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)