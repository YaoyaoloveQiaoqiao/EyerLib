#include "EyerImageReader.hpp"

#include "EyerCore/EyerCore.hpp"
#include <png.h>

namespace Eyer
{
    EyerImageReader::EyerImageReader()
    {

    }

    EyerImageReader::~EyerImageReader()
    {

    }

    static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        EyerBuffer * buffer = (EyerBuffer *)png_get_io_ptr(png_ptr);
        buffer->CutOff(data, length);

        // png_error(png_ptr, "pngReaderCallback failed");
    }

    int EyerImageReader::Reader(unsigned char * data, int size, EyerImageBuffer & outBuffer)
    {
        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
        if(png_ptr == 0){
            return -1;
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if(info_ptr == 0) {
            png_destroy_read_struct(&png_ptr, 0, 0);
            return -1;
        }

        if(setjmp(png_jmpbuf(png_ptr))) {
            png_destroy_read_struct(&png_ptr, &info_ptr,0);
        }

        EyerBuffer buffer;
        buffer.Append(data, size);

        png_set_read_fn(png_ptr, &buffer, pngReadCallback);

        png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

        int width = png_get_image_width(png_ptr, info_ptr);
        int height = png_get_image_height(png_ptr, info_ptr);
        int color_type = png_get_color_type(png_ptr, info_ptr);
        int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        int channels = png_get_channels(png_ptr, info_ptr);

        outBuffer.width = width;
        outBuffer.height = height;

        EyerLog("width: %d\n", width);
        EyerLog("height: %d\n", height);
        EyerLog("color_type: %d\n", color_type);
        EyerLog("bit_depth: %d\n", bit_depth);
        EyerLog("channels: %d\n", channels);

        unsigned char * rgba = (unsigned char *)malloc(width * height * 4);

        png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                rgba[i * width * 4 + j * 4 + 0] = row_pointers[i][j * 4 + 0];
                rgba[i * width * 4 + j * 4 + 1] = row_pointers[i][j * 4 + 1];
                rgba[i * width * 4 + j * 4 + 2] = row_pointers[i][j * 4 + 2];
                rgba[i * width * 4 + j * 4 + 3] = row_pointers[i][j * 4 + 3];
            }
        }

        outBuffer.Append(rgba, width * height * 4);
        free(rgba);

        png_destroy_read_struct(&png_ptr, &info_ptr, 0);

        return 0;
    }
}