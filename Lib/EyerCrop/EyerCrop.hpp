#ifndef	EYER_LIB_AV_CROP_H
#define	EYER_LIB_AV_CROP_H

namespace Eyer
{
    enum EyerAVCropType
    {
        FIT_CENTER = 0,
        FIT_XY = 1,
        FIT_END = 2,
        FIT_START = 3,
        CENTER = 4,
        CENTER_CROP = 5,
        CENTER_INSIDE = 6,
        MATRIX = 7
    };

    class EyerAVCropUtil
    {
    public:
        EyerAVCropUtil();
        ~EyerAVCropUtil();

        int GetCrop(int viewW, int viewH, int imageW, int imageH, int & targetW, int & targetH, EyerAVCropType cropType = EyerAVCropType::FIT_CENTER);
        int GetCrop(int viewW, int viewH, int imageW, int imageH, int& targetW, int& targetH, int& transX, int& transY, EyerAVCropType cropType = EyerAVCropType::FIT_CENTER);
    };


    class EyerAVCrop
    {
    public:
        EyerAVCrop(int viewW, int viewH, int imageW, int imageH);
        ~EyerAVCrop();

        int GetCropW();
        int GetCropH(); 

        int Crop(EyerAVCropType cropType = EyerAVCropType::FIT_CENTER);
    private:
        int viewW = 0;
        int viewH = 0;
        int imageW = 0;
        int imageH = 0;

        int cropW = 0;
        int cropH = 0;
    };
}

#endif