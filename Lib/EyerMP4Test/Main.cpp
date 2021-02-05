#include <gtest/gtest.h>

#include "Endian.hpp"
#include "Read_MP4Test.hpp"
#include "Read_fMP4Test.hpp"

#include "FTYPTest.hpp"
#include "MEHDTest.hpp"
#include "STTSTest.hpp"
#include "STSCTest.hpp"
#include "STCOTest.hpp"
#include "MVHDTest.hpp"
#include "TKHDTest.hpp"
#include "ELSTTest.hpp"
#include "HDLRTest.hpp"
#include "TREXTest.hpp"
#include "MFHDTest.hpp"
#include "TFHDTest.hpp"

int main(int argc,char **argv){
    eyer_log_param(1, 1, 0, 0, 0);
    eye_log_set_level(5);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
