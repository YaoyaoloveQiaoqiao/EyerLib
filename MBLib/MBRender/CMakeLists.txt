include_directories (../)
include_directories (./)

add_library(
        MBRender
        MBRender.hpp
        MBTgaImage.cpp

        MBLine.hpp
        MBLine.cpp

        MBCanvas.hpp
        MBCanvas.cpp

        MBObjModel.cpp

        MBVertex.hpp
        MBVertex.cpp
        )

target_link_libraries (MBRender gtest)
target_link_libraries (MBRender MBCore)

set(head_files
        MBRender.hpp
        MBTGA.hpp
        MBLine.hpp
        MBVertex.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/MBRender)
INSTALL(
        TARGETS MBRender
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
