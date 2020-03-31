add_executable(
        MBTypeTest
        Main.cpp
)

include_directories (../)

target_link_libraries (MBTypeTest MBCore)
target_link_libraries (MBTypeTest MBType)

INSTALL(
        TARGETS MBTypeTest
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
