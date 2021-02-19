#include "EyerColorSpace.hpp"

namespace Eyer {
    EyerColorSpaceMat *EyerColorSpaceMat::instance = nullptr;

    EyerColorSpaceMat::EyerColorSpaceMat() {
        float rgb2020_xyz[] = {
                0.6370, 0.1446, 0.1689,
                0.2627, 0.6780, 0.0593,
                0, 0.0281, 1.0610
        };
        rgb2020_xyz_mat = Eyer::Eatrix<float>(3, 3);
        rgb2020_xyz_mat.SetData(rgb2020_xyz, 9);

        float rgb709_xyz[] = {
                0.4124, 0.3576, 0.1805,
                0.2126, 0.7152, 0.0722,
                0.0193, 0.1192, 0.9505
        };
        rgb709_xyz_mat = Eyer::Eatrix<float>(3, 3);
        rgb709_xyz_mat.SetData(rgb709_xyz, 9);

        float yuv601_rgb601_255[] = {
                1, 0, 1.4017,
                1, -0.3437, -0.7142,
                1, 1.7722, 0
        };
        yuv601_rgb601_255_mat = Eyer::Eatrix<float>(3, 3);
        yuv601_rgb601_255_mat.SetData(yuv601_rgb601_255, 9);

        yuv709_rgb709_255_mat = yuv601_rgb601_255_mat;

        float yuv2020_rgb2020_255[] = {
                1.0000, -0.0000, 1.4746,
                1.0000, -0.1645, -0.5713,
                1.0000, 1.8814, -0.0001
        };
        yuv2020_rgb2020_255_mat = Eyer::Eatrix<float>(3, 3);
        yuv2020_rgb2020_255_mat.SetData(yuv2020_rgb2020_255, 9);
    }

    EyerColorSpaceMat *EyerColorSpaceMat::GetInstance() {
        if (EyerColorSpaceMat::instance == nullptr) {
            EyerColorSpaceMat::instance = new EyerColorSpaceMat();
        }
        
        return EyerColorSpaceMat::instance;
    }
}
