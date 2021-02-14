include_directories (../)
include_directories (./)

add_library(
        EyerMath
        EyerMath.hpp
        Eatrix.hpp
        Eatrix.cpp
        Eatrix4x4.hpp
        Eath.cpp
        Eath.hpp
        Eatrix3x1.hpp
        Eatrix3x3.hpp
        EnterPolation.cpp
        EnterPolation.hpp
        Eatrix4x1.hpp)

set(head_files
        EyerMath.hpp
        Eath.hpp
        Eatrix.hpp
        Eatrix3x1.hpp
        Eatrix3x3.hpp
        Eatrix4x1.hpp
        Eatrix4x4.hpp
        EnterPolation.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerMath)
INSTALL(
        TARGETS EyerMath
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
