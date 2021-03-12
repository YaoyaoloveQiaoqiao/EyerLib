include_directories (../)
include_directories (./)

add_library(
        EyerVideoEditor

        EyerVideoEditor.hpp
        EyerScene.hpp
        EyerScene.cpp
        EyerLayer.cpp
        EyerLayer.hpp
        EyerSpirit.cpp
        EyerSpirit.hpp
        EyerKey.cpp
        EyerKey.hpp
        EyerCamera.cpp EyerCamera.hpp)

set(head_files
        EyerVideoEditor.hpp
        EyerScene.hpp
        EyerLayer.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerVideoEditor)
INSTALL(
        TARGETS EyerVideoEditor
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
