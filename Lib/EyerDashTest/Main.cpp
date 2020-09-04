#include <gtest/gtest.h>
#include <curl/curl.h>
#include "EyerNet/EyerNet.hpp"
#include "EyerCore/EyerCore.hpp"
#include <stdlib.h>
#include <libxml2/libxml/parser.h>
#include "EyerDASH/EyerDASH.hpp"

TEST(EyerDashTest, EyerAdaptationSet){
    Eyer::EyerAdaptationSet adaptationSet;

    Eyer::EyerSegmentTemplate segmentTemplateA;
    segmentTemplateA.SetInitialization("$RepresentationID$/$RepresentationID$_0.m4v");


}

TEST(EyerDashTest, SegmentTemplate){
    Eyer::EyerSegmentTemplate segmentTemplateA;
    segmentTemplateA.SetInitialization("$RepresentationID$/$RepresentationID$_0.m4v");
    EyerLog("Initialization A: %s\n", segmentTemplateA.GetInitialization().str);

    Eyer::EyerSegmentTemplate segmentTemplateB;
    segmentTemplateB = segmentTemplateA;
    Eyer::EyerSegmentTemplate segmentTemplateC = segmentTemplateA;

    ASSERT_EQ(segmentTemplateB.GetInitialization() == segmentTemplateA.GetInitialization(), true) << "Initialization Error";
    ASSERT_EQ(segmentTemplateC.GetInitialization() == segmentTemplateA.GetInitialization(), true) << "Initialization Error";
}

TEST(EyerDashTest, MPD){
    // Read mpd file
    Eyer::EyerSimplestHttp http;

    Eyer::EyerString url = "https://dash.akamaized.net/akamai/bbb_30fps/bbb_30fps.mpd";
    Eyer::EyerBuffer buffer;
    int ret = http.Get(buffer, url);
    if(ret){
        EyerLog("Read mpd file error");
        return;
    }

    Eyer::EyerMPD mpd;
    mpd.LoadMPD(buffer);
    mpd.PrintInfo();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}