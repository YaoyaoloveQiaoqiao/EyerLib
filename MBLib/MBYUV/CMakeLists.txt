include_directories (../)
include_directories (./)
include_directories (${CMAKE_SOURCE_DIR}/../../Lib/libyuv_install/include)

add_library(
        MBYUV
        MBYUV.cpp
)

target_link_libraries (MBYUV MBCore)
target_link_libraries (MBYUV ${CMAKE_SOURCE_DIR}/../../Lib/libyuv_install/lib/libyuv.a)

set(head_files
        MBYUV.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/MBYUV)
INSTALL(
        TARGETS MBYUV
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
