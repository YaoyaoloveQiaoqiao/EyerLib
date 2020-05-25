add_executable(
        EyerVideoTweenAnimationTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerVideoTweenAnimationTest EyerCore)
target_link_libraries (EyerVideoTweenAnimationTest gtest)
target_link_libraries (EyerVideoTweenAnimationTest EyerVideoTweenAnimation)

INSTALL(
        TARGETS EyerVideoTweenAnimationTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
