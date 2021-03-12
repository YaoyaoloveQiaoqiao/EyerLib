include_directories (../)
include_directories (./)

add_library(
        EyerImage
        EyerImage.hpp
        EyerImageReader.hpp
        EyerImageReader.cpp
        EyerImageBuffer.hpp
        EyerImageBuffer.cpp
)

set(head_files
        EyerImage.hpp
        EyerImageReader.hpp
        EyerImageBuffer.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerImage)
INSTALL(
        TARGETS EyerImage
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
