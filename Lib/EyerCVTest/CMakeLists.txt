add_executable(
        EyerCVTest
        Main.cpp
)

include_directories (../)

target_link_libraries (EyerCVTest gtest)
target_link_libraries (EyerCVTest opencv_core)
target_link_libraries (EyerCVTest opencv_calib3d)
target_link_libraries (EyerCVTest opencv_dnn)
target_link_libraries (EyerCVTest opencv_features2d)
target_link_libraries (EyerCVTest opencv_flann)
target_link_libraries (EyerCVTest opencv_highgui)
target_link_libraries (EyerCVTest opencv_imgcodecs)
target_link_libraries (EyerCVTest opencv_imgproc)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/bug_a.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/image_a.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/image_b.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/image_c.png
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )
file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/image_d.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/a.png
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/star.jpg
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )
INSTALL(
        TARGETS EyerCVTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)