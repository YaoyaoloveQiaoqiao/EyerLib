include_directories (../)
include_directories (./)

add_library(
        MBThread
        MBThread.cpp
)

target_link_libraries (MBThread pthread)
target_link_libraries (MBThread gtest)

set(head_files
        MBThread.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/MBThread)
INSTALL(
        TARGETS MBThread
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
