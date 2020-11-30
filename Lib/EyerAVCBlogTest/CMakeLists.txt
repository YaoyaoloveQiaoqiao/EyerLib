add_executable(
        EyerAVCBlogTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerAVCBlogTest gtest)
target_link_libraries (EyerAVCBlogTest EyerAVCBlog)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo_video.h264
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo_video_176x144.h264
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo_video_176x144_baseline.h264
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

INSTALL(
        TARGETS EyerAVCBlogTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)