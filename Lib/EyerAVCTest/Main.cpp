#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

#include "Baseline.hpp"
#include "NALUReader.hpp"

#include "EyerCore/EyerCore.hpp"

int main(int argc,char **argv){
    eyer_log_path("./log.txt");

    eyer_log_param(1, 1, 0, 0, 0);
    eyer_log_set_level(5);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
