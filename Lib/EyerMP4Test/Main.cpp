#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"


TEST(EyerMP4, EyerMP4Test)
{
    // FILE * fp = fopen("/Users/yuqiaomiao/boy.mp4", "rb");
    FILE * fp = fopen("C://Video/bbb_1080p.mp4", "rb");


    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);

    fseek(fp, 0, 0);

    unsigned char * data = (unsigned char *)malloc(len);
    int ret = fread(data, len, 1, fp);

    Eyer::EyerBuffer buffer;
    buffer.Append(data, len);


    Eyer::EyerMP4Box box(buffer);
    if(box.GetType() == Eyer::BoxType::UNKNOW){
        while(1){
            Eyer::EyerMP4Box * subbox = nullptr;
            int ret = box.Get(&subbox);
            if(ret){
                break;
            }
            if(subbox == nullptr){
                continue;
            }

            if(subbox->GetType() == Eyer::BoxType::FTYP){
                Eyer::EyerMP4Box_ftyp * ftyp = (Eyer::EyerMP4Box_ftyp *)subbox;
                ftyp->PrintInfo();
            }
            else if(subbox->GetType() == Eyer::BoxType::MOOV){
                Eyer::EyerMP4Box_moov * moov = (Eyer::EyerMP4Box_moov *)subbox;
                moov->PrintInfo();
                while(1){
                    Eyer::EyerMP4Box * subbox = nullptr;
                    ret = moov->Get(&subbox);
                    if(ret){
                        break;
                    }
                    if(subbox == nullptr){
                        continue;
                    }
                    subbox->PrintInfo();

                    if(subbox->GetType() == Eyer::BoxType::TRAK){
                        Eyer::EyerMP4Box_trak * trak = (Eyer::EyerMP4Box_trak *)subbox;
                        while(1){
                            Eyer::EyerMP4Box * trakSub = nullptr;
                            ret = trak->Get(&trakSub);
                            if(ret){
                                break;
                            }
                            if(trakSub == nullptr){
                                continue;
                            }
                            trakSub->PrintInfo();
                        }
                    }

                    if(subbox != nullptr){
                        delete subbox;
                        subbox = nullptr;
                    }
                }
            }
            else{

            }


            if(subbox != nullptr){
                delete subbox;
                subbox = nullptr;
            }
        }
    }


    free(data);

    fclose(fp);
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
