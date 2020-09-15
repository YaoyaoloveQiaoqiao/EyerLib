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

    Eyer::EyerString m4vUrl;

    int representationIndex = 2;

    ret = mpd.GetInitURL(m4vUrl, representationIndex);

    Eyer::EyerURLUtil urlUtil(url);
    m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);
    printf("%s\n", m4vUrl.str);

    for(int i=1;i<=100;i++){
        ret = mpd.GetVideoURL(m4vUrl, i, representationIndex);
        if(ret){
            break;
        }
        m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);
        printf("%s\n", m4vUrl.str);
    }
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}