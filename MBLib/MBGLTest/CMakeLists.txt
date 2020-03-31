add_executable(
        MBGLTest
        Main.cpp
)

include_directories (../)

target_link_libraries (MBGLTest MBCore)
target_link_libraries (MBGLTest MBGL)
target_link_libraries (MBGLTest MBType)
target_link_libraries (MBGLTest MBGLWindow)
target_link_libraries (MBGLTest MBGLAD)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/Manjari-Bold.otf
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/xiao_xiao_yuan_pin_ying.ttf
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/han_yi_xing_kai_jian.ttf
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )



INSTALL(
        TARGETS MBGLTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
