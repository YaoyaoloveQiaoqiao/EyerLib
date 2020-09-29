add_executable(
        EyerAVCTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerAVCTest EyerCore)
target_link_libraries (EyerAVCTest EyerAVC)
target_link_libraries (EyerAVCTest gtest)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/demo_video.h264
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

INSTALL(
        TARGETS EyerAVCTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)