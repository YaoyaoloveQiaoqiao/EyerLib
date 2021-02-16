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
    }

    EyerColorSpaceMat *EyerColorSpaceMat::GetInstance() {
        if (EyerColorSpaceMat::instance == nullptr) {
            EyerColorSpaceMat::instance = new EyerColorSpaceMat();

        }
        return EyerColorSpaceMat::instance;
    }
}
//A::GetInstance()->rgb2020_xyz_mat
