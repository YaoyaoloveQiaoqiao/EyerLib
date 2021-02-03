add_executable(
        EyerMathTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerMathTest EyerMath)
target_link_libraries (EyerMathTest EyerCore)
target_link_libraries (EyerMathTest EyerThread)
target_link_libraries (EyerMathTest gtest)

INSTALL(
        TARGETS EyerMathTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)