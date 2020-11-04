add_executable(
        EyerGLTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerGLTest EyerCore)
target_link_libraries (EyerGLTest EyerGLCustomComponent)
target_link_libraries (EyerGLTest EyerGL)
target_link_libraries (EyerGLTest EyerGLShader)
target_link_libraries (EyerGLTest EyerType)
target_link_libraries (EyerGLTest EyerGLWindow)
target_link_libraries (EyerGLTest EyerGLContext)
target_link_libraries (EyerGLTest EyerGLAD)
target_link_libraries (EyerGLTest EyerThread)

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
        TARGETS EyerGLTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
