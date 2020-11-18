include_directories (../)
include_directories (./)

add_library(
        EyerSIP
        EyerSIP.hpp
        EyerSIP.hpp
        EyerSIPMessgae.cpp
        EyerSIPMessgae.hpp
        EyerSIPMessgaePrivate.hpp
        EyerSIPFrom.cpp
        EyerSIPFrom.hpp
        EyerSIPFromPrivate.hpp)

set(head_files
        EyerSIP.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerSIP)
INSTALL(
        TARGETS EyerSIP
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

