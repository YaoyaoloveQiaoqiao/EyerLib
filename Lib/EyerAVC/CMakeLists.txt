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
        EyerPPS.cpp
        EyerPPS.hpp
        EyerSLICE.cpp
        EyerSLICE.hpp
        SLICEType.cpp
        SLICEType.hpp
        EyerSLICEHeader.cpp
        EyerSLICEHeader.hpp
        EyerSLICEBody.cpp
        EyerSLICEBody.hpp
        I_MB_TYPE.cpp
        I_MB_TYPE.hpp
        MB_PART_PRED_MODE.cpp
        MB_PART_PRED_MODE.hpp
        MB_TYPE.cpp
        MB_TYPE.hpp
        EyerMacroblock.cpp EyerMacroblock.hpp)

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
        EyerBitStream.hpp
        EyerField.hpp
        EyerSPS.hpp
        EyerPPS.hpp
        EyerSLICE.hpp
        SLICEType.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerAVC)
INSTALL(
        TARGETS EyerAVC
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

