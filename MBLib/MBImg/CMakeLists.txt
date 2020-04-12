include_directories (../)
include_directories (./)

add_library(
        MBImg
        stb_image.h
        stb_image.cpp
)

target_link_libraries (MBImg gtest)

set(head_files
        stb_image.h
        )

INSTALL(FILES ${head_files} DESTINATION include/MBImg)
INSTALL(
        TARGETS MBImg
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
