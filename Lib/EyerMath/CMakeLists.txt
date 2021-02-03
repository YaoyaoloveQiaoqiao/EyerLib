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
)

set(head_files
        EyerMath.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerMath)
INSTALL(
        TARGETS EyerMath
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
