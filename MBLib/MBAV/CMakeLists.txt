include_directories (../)
include_directories (./)

add_library(
    MBAV
    MBAVPacket.cpp
    MBAVReader.cpp
    MBAVDecoder.cpp
    MBAVStream.cpp
    MBAVFrame.cpp
    MBAVEncoder.cpp
    MBAVWriter.cpp

    MBAV.hpp
    MBAVDecoderPrivate.hpp
    MBAVEncoderPrivate.hpp
    MBAVFramePrivate.hpp
    MBAVPacketPrivate.hpp
    MBAVReaderPrivate.hpp
    MBAVStreamPrivate.hpp
    MBAVWriterPrivate.hpp
    MBAVBitmap.cpp
    MBAVRational.cpp
    MBAVAudioFrameUtil.cpp
    MBAVFrameWeight.cpp
        MBAVPacketQueue.cpp
        MBAVPacketQueue.hpp
        MBAVFrameQueue.cpp
        MBAVFrameQueue.hpp
        MBAVQueue.cpp
        MBAVQueue.hpp)

target_link_libraries (MBAV pthread)
target_link_libraries (MBAV MBCore)

include_directories (${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/include)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")

    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)

    target_link_libraries (MBAV dl)
    target_link_libraries (MBAV z)
    target_link_libraries (MBAV bz2)
    target_link_libraries (MBAV lzma)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")

    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)

    target_link_libraries (MBAV z)
    target_link_libraries (MBAV bz2)
    target_link_libraries (MBAV ws2_32)
    target_link_libraries (MBAV Secur32)
    target_link_libraries (MBAV lzma)
    target_link_libraries (MBAV iconv)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
    MESSAGE(STATUS "current platform: Android")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin")

    target_link_libraries (MBAV bz2)
    target_link_libraries (MBAV z)
    target_link_libraries (MBAV lzma)
    target_link_libraries (MBAV iconv)

    link_directories(${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib)
    link_directories(/Users/lichi/MBWand/Lib/ffmpeg_install/lib/)

    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.a)
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.a)

    # target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavformat.dylib)
    # target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavdevice.dylib)
    # target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavcodec.dylib)
    # target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavutil.dylib)
    # target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libavfilter.dylib)
    # target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswresample.dylib)
    # target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/ffmpeg_install/lib/libswscale.dylib)
    
    target_link_libraries (MBAV ${CMAKE_SOURCE_DIR}/../../Lib/x264_install/lib/libx264.a)
    
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(head_files 
    MBAV.hpp
        MBAVPacketQueue.hpp
        MBAVFrameQueue.hpp
        MBAVQueue.hpp
)

INSTALL(FILES ${head_files} DESTINATION include/MBAV)
INSTALL(
    TARGETS MBAV
    RUNTIME DESTINATION bin        
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )

