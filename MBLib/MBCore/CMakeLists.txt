include_directories (../)
include_directories (./)

add_library(
    MBCore
    # SHARED

    MBCore.hpp
    MBString.hpp
    MBLog.hpp
    MBLog.cpp
    MBMath.hpp
    MBString.cpp

    MBMat.cpp
    MBMat4x4.cpp
    MBMat4x1.cpp
    MBMat3x1.cpp
    MBMat2x1.cpp
    MBRand.cpp
    MBTime.cpp

)

target_link_libraries (MBCore pthread)
target_link_libraries (MBCore gtest)

set(head_files 
    MBString.hpp
    MBCore.hpp
    MBLog.hpp
    MBMath.hpp
    MBTime.hpp
    MBLinkedList.hpp
    MBLinkedEle.hpp
    MBQueue.hpp
    MBMap.hpp
    MBMapEle.hpp
)

INSTALL(FILES ${head_files} DESTINATION include/MBCore)
INSTALL(
    TARGETS MBCore
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )
