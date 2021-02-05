include_directories (../)
include_directories (./)

add_library(
        EyerSignal
        # SHARED
        EyerSignal.cpp
        EyerSignal.hpp
        DCT.cpp
        DCT.hpp
        EyerPalette.cpp
        EyerPalette.hpp
        EyerPixel.cpp
        EyerPixel.hpp
)

set(head_files
        EyerSignal.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerSignal)
INSTALL(
        TARGETS EyerSignal
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
