include_directories (../)
include_directories (./)

add_library(
        EyerAVC
        EyerAVC.hpp
        EyerAnnexB.cpp
        EyerAnnexB.hpp
        EyerAVCDecoder.cpp
        EyerAVCDecoder.hpp
        EyerNALUData.cpp
        EyerNALUData.hpp
        NALRefIdc.cpp
        NALRefIdc.hpp
        NALUType.cpp
        NALUType.hpp
        EyerEnum.cpp
        EyerEnum.hpp
        EyerNALU.cpp
        EyerNALU.hpp
        EyerSPS.cpp
        EyerSPS.hpp
        EyerBitStream.cpp
        EyerBitStream.hpp
        EyerField.hpp
        EyerField.cpp
)

target_link_libraries (
        EyerAVC
        EyerCore
)

set(head_files
        EyerAVC.hpp
        EyerAnnexB.hpp
        EyerAVCDecoder.hpp
        EyerNALUData.hpp
        NALRefIdc.hpp
        NALUType.hpp
        EyerEnum.hpp
        EyerNALU.hpp
        EyerSPS.hpp
        EyerBitStream.hpp
        EyerField.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerAVC)
INSTALL(
        TARGETS EyerAVC
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

