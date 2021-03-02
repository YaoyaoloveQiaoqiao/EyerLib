add_executable(
        ColorSpaceAnimation
        Main.cpp

        Scene.cpp
        Scene.hpp
        MagicNumber.hpp
        MagicNumber.cpp
        CIE_XYZ_COOR_EyerSpirit.cpp
        CIE_XYZ_COOR_EyerSpirit.hpp
        CIE_RGB_COOR_EyerSpirit.cpp
        CIE_RGB_COOR_EyerSpirit.hpp
        Label_EyerSpirit.cpp
        Label_EyerSpirit.hpp
        SphereSpirit.cpp
        SphereSpirit.hpp
        MVPCoorLineSpirit.cpp
        MVPCoorLineSpirit.hpp
        MVPNormalizePlaneSpirit.cpp
        MVPNormalizePlaneSpirit.hpp
        MVPLineSpirit.cpp
        MVPLineSpirit.hpp
        MVPCustomSpirit.cpp 
	MVPCustomSpirit.hpp
)

include_directories (../)

target_link_libraries (ColorSpaceAnimation EyerGLWindow)
target_link_libraries (ColorSpaceAnimation EyerVideoEditor)
target_link_libraries (ColorSpaceAnimation EyerGLCustomComponent)
target_link_libraries (ColorSpaceAnimation EyerGL)
target_link_libraries (ColorSpaceAnimation EyerImage)
target_link_libraries (ColorSpaceAnimation EyerMath)
target_link_libraries (ColorSpaceAnimation EyerAV)
target_link_libraries (ColorSpaceAnimation EyerCore)
target_link_libraries (ColorSpaceAnimation EyerThread)
target_link_libraries (ColorSpaceAnimation EyerGLShader)
target_link_libraries (ColorSpaceAnimation EyerYUV)

target_link_libraries (ColorSpaceAnimation xml2)

INSTALL(
        TARGETS ColorSpaceAnimation
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)