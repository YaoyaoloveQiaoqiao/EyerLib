add_executable(
        EyerTypeTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerTypeTest gtest gtest_main)
target_link_libraries (EyerTypeTest EyerCore)
target_link_libraries (EyerTypeTest EyerType)
target_link_libraries (EyerTypeTest EyerGL)
target_link_libraries (EyerTypeTest EyerGLWindow)

target_link_libraries (EyerTypeTest X11)

target_link_libraries (EyerTypeTest dl)
target_link_libraries (EyerTypeTest X11)
target_link_libraries (EyerTypeTest bz2)
target_link_libraries (EyerTypeTest z)
target_link_libraries (EyerTypeTest EyerGLAD)
target_link_libraries (EyerTypeTest ${CMAKE_SOURCE_DIR}/../../Lib/glfw_install/lib/libglfw3.a)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/xiao_xiao_yuan_pin_ying.ttf
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

INSTALL(
        TARGETS EyerTypeTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
