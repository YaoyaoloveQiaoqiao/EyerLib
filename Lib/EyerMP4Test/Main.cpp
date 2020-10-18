#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

int GetSubBox(Eyer::EyerMP4Box & box, int depth){
    for(int i=0;i<depth;i++){
        printf("\t");
    }
    box.PrintInfo();

    if(!box.HasSub()){
        return 0;
    }

    while(1) {
        Eyer::EyerMP4Box *subBox = nullptr;
        int ret = box.Get(&subBox);
        if (ret) {
            break;
        }
        if(subBox == nullptr){
            continue;
        }
        int d = depth + 1;

        GetSubBox(*subBox, d);

        if(subBox != nullptr){
            delete subBox;
            subBox = nullptr;
        }
    }

    return 0;
}

TEST(EyerMP4, EyerMP4Test)
{
    FILE * fp = fopen("/Users/yuqiaomiao/boy.mp4", "rb");
    // FILE * fp = fopen("C://Video/bbb_1080p.mp4", "rb");


    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);

    fseek(fp, 0, 0);

    unsigned char * data = (unsigned char *)malloc(len);
    int ret = fread(data, len, 1, fp);

    Eyer::EyerBuffer buffer;
    buffer.Append(data, len);

    Eyer::EyerMP4Box box(buffer);
    GetSubBox(box, 0);

    free(data);

    fclose(fp);
}



int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
