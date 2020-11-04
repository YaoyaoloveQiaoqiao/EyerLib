add_executable(
        EyerLuaTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerLuaTest gtest)

INSTALL(
        TARGETS EyerLuaTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)