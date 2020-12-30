#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"
#include "EyerDASH/EyerDASH.hpp"

#include "EyerAVPureColorCheck.hpp"
#include "AVGif.hpp"

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
