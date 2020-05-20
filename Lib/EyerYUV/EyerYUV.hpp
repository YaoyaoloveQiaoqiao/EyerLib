#ifndef	EYER_LIB_YUV_H
#define	EYER_LIB_YUV_H

namespace Eyer
{
    class EyerYUV
    {
    public:
        EyerYUV();
        ~EyerYUV();

        int RGB2YUV420(int width, int height, unsigned char * rgbData, unsigned char * y, unsigned char * u, unsigned char * v);

        int I420_TO_RGBA(int width, int height, unsigned char * y, unsigned char * u, unsigned char * v, unsigned char * rgbData);
    };
}

#endif