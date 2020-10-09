include_directories (../)
include_directories (./)

add_library(
        EyerAVC
        EyerAnnexB.cpp
        EyerAnnexB.hpp
        EyerNALU.cpp
        EyerNALU.hpp
        EyerSPS.cpp
        EyerSPS.hpp
        EyerAVCCommon.cpp
        EyerAVCCommon.hpp
        EyerAVC_VLC.cpp
        EyerAVC_VLC.hpp
        EyerBitStream.cpp
        EyerBitStream.hpp
        EyerSyntaxElement.cpp
        EyerSyntaxElement.hpp
        EyerVUI.cpp
        EyerVUI.hpp
        EyerField.cpp
        EyerField.hpp
        EyerPPS.cpp
        EyerPPS.hpp
        EyerNAL.cpp
        EyerNAL.hpp
        EyerSEI.cpp
        EyerSEI.hpp
        EyerIDR.cpp
        EyerIDR.hpp
        EyerSLICEBase.cpp
        EyerSLICEBase.hpp
        EyerSLICE.cpp
        EyerSLICE.hpp
        EyerENUMUtil.cpp
        EyerAVCDecoder.cpp
        EyerAVCDecoder.hpp
)

target_link_libraries (
        EyerAVC
        EyerCore
)

set(head_files
        EyerAVC.hpp
        EyerAnnexB.hpp
        EyerAVC_VLC.hpp
        EyerAVCCommon.hpp
        EyerBitStream.hpp
        EyerField.hpp
        EyerNALU.hpp
        EyerPPS.hpp
        EyerSPS.hpp
        EyerSyntaxElement.hpp
        EyerVUI.hpp
        EyerNAL.hpp
        EyerSEI.hpp
        EyerIDR.hpp
        EyerSLICE.hpp
        EyerSLICEBase.hpp
        EyerAVCDecoder.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerAVC)
INSTALL(
        TARGETS EyerAVC
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

