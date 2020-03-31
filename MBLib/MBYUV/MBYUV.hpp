#ifndef	EYER_LIB_YUV_H
#define	EYER_LIB_YUV_H

namespace MB
{
    class MBYUV
    {
    public:
        MBYUV();
        ~MBYUV();

        int RGB2YUV420(int width, int height, unsigned char * rgbData, unsigned char * y, unsigned char * u, unsigned char * v);
    };
}

#endif