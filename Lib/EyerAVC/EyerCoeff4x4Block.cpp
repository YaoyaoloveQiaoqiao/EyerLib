#include "EyerCoeff4x4Block.hpp"

namespace Eyer
{
    EyerCoeff4x4Block::EyerCoeff4x4Block(int _qp)
    {
        qp = _qp;
    }

    EyerCoeff4x4Block::~EyerCoeff4x4Block()
    {

    }

    int EyerCoeff4x4Block::Restore()
    {
        int dequant_coef[6][4][4] = {
                {
                        { 10, 13, 10, 13},
                        { 13, 16, 13, 16},
                        { 10, 13, 10, 13},
                        { 13, 16, 13, 16}},
                {
                        { 11, 14, 11, 14},
                        { 14, 18, 14, 18},
                        { 11, 14, 11, 14},
                        { 14, 18, 14, 18}},
                {
                        { 13, 16, 13, 16},
                        { 16, 20, 16, 20},
                        { 13, 16, 13, 16},
                        { 16, 20, 16, 20}},
                {
                        { 14, 18, 14, 18},
                        { 18, 23, 18, 23},
                        { 14, 18, 14, 18},
                        { 18, 23, 18, 23}},
                {
                        { 16, 20, 16, 20},
                        { 20, 25, 20, 25},
                        { 16, 20, 16, 20},
                        { 20, 25, 20, 25}},
                {
                        { 18, 23, 18, 23},
                        { 23, 29, 23, 29},
                        { 18, 23, 18, 23},
                        { 23, 29, 23, 29}}
        };

        EyerLog("\t\t\t\tRestore: \n");

        int coeffNum[16] = {0};
        // trailingOnes
        for(int i=totleCoeff - 1, j = trailingOnes - 1; j >= 0; j--) {
            if(trailingSign[j] == 1){
                coeffNum[i--] = -1;
            }
            else{
                coeffNum[i--] = 1;
            }
        }
        // levels
        for(int i=totleCoeff - trailingOnes - 1; i >= 0; i--) {
            coeffNum[i] = levels[totleCoeff - trailingOnes - 1 - i];
        }
        // runbefore
        int tempTotleZeros = totleZeros;
        for(int i=totleCoeff - 1; i > 0; i--) {
            SWAP(coeffNum[i], coeffNum[i + tempTotleZeros]);
            tempTotleZeros -= runBefore[i];
        }
        SWAP(coeffNum[0], coeffNum[tempTotleZeros]);

        EyerString logStr = "";
        for(int i=0;i<16;i++){
            logStr = logStr + EyerString::Number(coeffNum[i]) + " ";
        }
        EyerLog("\t\t\t\t\t%s\n", logStr.str);


        EyerLog("\t\t\t\t还原 ZigZag\n", logStr.str);
        int SNAL_SCAN[16][2] = {
                {0, 0}, {1, 0}, {0, 1}, {0, 2},
                {1, 1}, {2, 0}, {3, 0}, {2, 1},
                {1, 2}, {0, 3}, {1, 3}, {2, 2},
                {3, 1}, {3, 2}, {2, 3}, {3, 3}
        };

        for(int i=0;i<16;i++){
            int * s = SNAL_SCAN[i];
            int x = s[0];
            int y = s[1];
            coeffBuf[y][x] = coeffNum[i];
        }

        for(int i=0;i<4;i++){
            EyerString line = "";
            for(int j=0;j<4;j++){
                line = line + EyerString::Number(coeffBuf[i][j], "%4d") + " ";
            }
            EyerLog("\t\t\t\t\t%s\n", line.str);
        }



        // 反量化
        EyerLog("\t\t\t\t反量化\n", logStr.str);
        // 获取 QP
        int qp_per = qp / 6;
        int qp_rem = qp % 6;

        EyerLog("\t\t\t\tqp_per: %d, qp_rem: %d\n", qp_per, qp_rem);
        for(int i=0;i<4;i++) {
            for (int j = 0; j < 4; j++) {
                dequantBuf[i][j] = coeffBuf[i][j] * dequant_coef[qp_rem][j][i] << qp_per;
            }
        }

        for(int i=0;i<4;i++){
            EyerString line = "";
            for(int j=0;j<4;j++){
                line = line + EyerString::Number(dequantBuf[i][j], "%4d") + " ";
            }
            EyerLog("\t\t\t\t\t%s\n", line.str);
        }

        //
        // 水平变换
        EyerLog("\t\t\t\t反DCT\n", logStr.str);
        int temp1[4] = {0};
        int temp2[4] = {0};
        for(int j=0;j<4;j++){
            for(int i=0;i<4;i++){
                temp1[i] = dequantBuf[i][j];
            }
            temp2[0] = temp1[0] + temp1[2];
            temp2[1] = temp1[0] - temp1[2];
            temp2[2] = (temp1[1] >> 1) - temp1[3];
            temp2[3] = temp1[1] + (temp1[3] >> 1);

            for(int i=0;i<2;i++){
                int i1 = 3 - i;
                residualBuf[i][j] = temp2[i] + temp2[i1];
                residualBuf[i1][j] = temp2[i] - temp2[i1];
            }
        }

        // 垂直变换
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                temp1[j] = residualBuf[i][j];
            }
            temp2[0] = temp1[0] + temp1[2];
            temp2[1] = temp1[0] - temp1[2];
            temp2[2] = (temp1[1] >> 1) - temp1[3];
            temp2[3] = temp1[1] + (temp1[3] >> 1);

            for(int j=0;j<2;j++){
                int j1 = 3 - j;
                residualBuf[i][j] = temp2[j] + temp2[j1];
                residualBuf[i][j1] = temp2[j] - temp2[j1];
            }
        }

        for(int i=0;i<4;i++){
            EyerString line = "";
            for(int j=0;j<4;j++){
                line = line + EyerString::Number(residualBuf[i][j], "%4d") + " ";
            }
            EyerLog("\t\t\t\t\t%s\n", line.str);
        }

        return 0;
    }

    int EyerCoeff4x4Block::Decode(EyerNeighbourSamples & neiSample, EyerTable<Sample> & res)
    {
        res.Resize(4, 4);
        // 预测：
        // DC 模式
        if(luma_pred_mode == 2){
            int predBuf[4][4] = {0};

            EyerLog("============================intra4x4_dc_pred============================\n");
            if(neiSample.AvailableUp() && neiSample.AvailableLeft()){
                EyerLog("============================A\n");
                int pred = (neiSample.A.sample + neiSample.B.sample + neiSample.C.sample + neiSample.D.sample +
                            neiSample.I.sample + neiSample.J.sample + neiSample.K.sample + neiSample.L.sample + 4) >> 3;
                for(int i=0;i<4;i++) {
                    for (int j = 0; j < 4; j++) {
                        predBuf[i][j] = pred;
                    }
                }
            }
            if(!neiSample.AvailableUp() && neiSample.AvailableLeft()){
                EyerLog("============================B\n");
                int pred = (neiSample.I.sample + neiSample.J.sample + neiSample.K.sample + neiSample.L.sample + 2) >> 2;
                for(int i=0;i<4;i++) {
                    for (int j = 0; j < 4; j++) {
                        predBuf[i][j] = pred;
                    }
                }
            }
            if(neiSample.AvailableUp() && !neiSample.AvailableLeft()){
                EyerLog("============================C\n");
                int pred = (neiSample.A.sample + neiSample.B.sample + neiSample.C.sample + neiSample.D.sample + 2) >> 2;
                for(int i=0;i<4;i++) {
                    for (int j = 0; j < 4; j++) {
                        predBuf[i][j] = pred;
                    }
                }
            }
            if(!neiSample.AvailableUp() && !neiSample.AvailableLeft()){
                EyerLog("============================D\n");
                int pred = 1 << (8 - 1);
                for(int i=0;i<4;i++) {
                    for (int j = 0; j < 4; j++) {
                        predBuf[i][j] = pred;
                    }
                }
            }

            for(int yy=0; yy<4; yy++){
                EyerString log;
                for(int xx=0; xx<4; xx++){
                    log = log + EyerString::Number(predBuf[yy][xx], " %3d ");
                }
                EyerLog("%s\n", log.str);
            }

            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    int temp = (predBuf[i][j] << 6) + residualBuf[i][j];
                    temp = (temp + 32) >> 6;
                    Sample sample;
                    sample.sample = temp;
                    sample.available = true;
                    res.Set(j, i, sample);
                }
            }
        }

        return 0;
    }

    int EyerCoeff4x4Block::SetQP(int _qp)
    {
        qp = _qp;
        return 0;
    }

    int EyerCoeff4x4Block::SWAP(int & x, int & y)
    {
        int c = x;
        x = y;
        y = c;
        return 0;
    }
}