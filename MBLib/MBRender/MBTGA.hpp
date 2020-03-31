#ifndef	EYER_LIB_REDNER_TGA_AV_H
#define	EYER_LIB_REDNER_TGA_AV_H

#include <fstream>
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <math.h>

namespace MB
{
    #pragma pack(push,1)
    struct TGA_Header {
        char idlength;
        char colormaptype;
        char datatypecode;
        short colormaporigin;
        short colormaplength;
        char colormapdepth;
        short x_origin;
        short y_origin;
        short width;
        short height;
        char  bitsperpixel;
        char  imagedescriptor;
    };
    #pragma pack(pop)

    typedef struct MBTGAColor {
        union {
            struct {
                unsigned char b, g, r, a;
            };
            unsigned char raw[4];
            unsigned int val;
        };
        int bytespp;

        MBTGAColor() : val(0), bytespp(1) {
        }

        MBTGAColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : b(B), g(G), r(R), a(A), bytespp(4) {
        }

        MBTGAColor(int v, int bpp) : val(v), bytespp(bpp) {
        }

        MBTGAColor(const MBTGAColor &c) : val(c.val), bytespp(c.bytespp) {
        }

        MBTGAColor(const unsigned char *p, int bpp) : val(0), bytespp(bpp) {
            for (int i=0; i<bpp; i++) {
                raw[i] = p[i];
            }
        }

        MBTGAColor & operator = (const MBTGAColor &c) {
            if (this != &c) {
                bytespp = c.bytespp;
                val = c.val;
            }
            return *this;
        }
    } MBTGAColor;

    class MBTgaImage
    {
    protected:
        unsigned char* data;
        int width;
        int height;
        int bytespp;

        bool   load_rle_data(std::ifstream &in);
        bool unload_rle_data(std::ofstream &out);
    public:
        enum Format {
            GRAYSCALE=1, RGB=3, RGBA=4
        };

        MBTgaImage();
        MBTgaImage(int w, int h, int bpp);
        MBTgaImage(const MBTgaImage &img);

        bool read_tga_file(const char *filename);
        bool write_tga_file(const char *filename, bool rle=true);
        bool flip_horizontally();
        bool flip_vertically();
        bool scale(int w, int h);
        
        MBTGAColor get(int x, int y);
        bool set(int x, int y, MBTGAColor c);

        ~MBTgaImage();
        MBTgaImage & operator =(const MBTgaImage &img);

        int get_width();
        int get_height();
        int get_bytespp();
        unsigned char *buffer();
        void clear();
    };
}

#endif