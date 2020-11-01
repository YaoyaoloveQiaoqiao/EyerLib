include_directories (../)
include_directories (./)

add_library(
        EyerAVC
        EyerAVC.hpp
        EyerAnnexB.cpp
        EyerAnnexB.hpp
        EyerAVCDecoder.cpp
        EyerAVCDecoder.hpp
        EyerNALU.cpp EyerNALU.hpp)

target_link_libraries (
        EyerAVC
        EyerCore
)

set(head_files
        EyerAVC.hpp
        EyerAnnexB.hpp
        EyerAVCDecoder.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerAVC)
INSTALL(
        TARGETS EyerAVC
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

