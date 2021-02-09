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
        EyerLog("\t\t\t\tRestore: \n");

        int SNAL_SCAN[16][2] = {
                {0, 0}, {1, 0}, {0, 1}, {0, 2},
                {1, 1}, {2, 0}, {3, 0}, {2, 1},
                {1, 2}, {0, 3}, {1, 3}, {2, 2},
                {3, 1}, {3, 2}, {2, 3}, {3, 3}
        };

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

        int coeffBuf[4][4] = {0};
        int residualBuf[4][4] = {0};

        for(int i=0;i<16;i++){
            int * s = SNAL_SCAN[i];
            coeffBuf[s[0]][s[1]] = coeffNum[i];
        }

        EyerLog("\n\n");
        for(int i=0;i<4;i++){
            EyerString line = "";
            for(int j=0;j<4;j++){
                line = line + EyerString::Number(coeffBuf[i][j], "%4d") + " ";
            }
            EyerLog("\t\t\t\t\t%s\n", line.str);
        }

        // 获取 QP

        // 反量化
        int qp_per = qp / 6;
        int qp_rem = qp % 6;

        EyerLog("\t\t\t\tqp_per: %d, qp_rem: %d\n", qp_per, qp_rem);

        // 水平变换
        int temp1[4] = {0};
        int temp2[4] = {0};
        for(int j=0;j<4;j++){
            for(int i=0;i<4;i++){
                temp1[i] = coeffBuf[i][j];
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

        for(int i=0;i<4;i++) {
            for (int j = 0; j < 4; j++) {
                // residualBuf[i][j] = residualBuf[i][j] >> 6;
            }
        }

        EyerLog("\n\n");
        for(int i=0;i<4;i++){
            EyerString line = "";
            for(int j=0;j<4;j++){
                line = line + EyerString::Number(residualBuf[i][j], "%4d") + " ";
            }
            EyerLog("\t\t\t\t\t%s\n", line.str);
        }

        return 0;
    }

    int EyerCoeff4x4Block::Decode(EyerNeighbourSamples & neighbourSamples, EyerTable<Sample> & res)
    {
        // 预测：
        // DC 模式
        if(luma_pred_mode == 2){
            if(neighbourSamples.AvailableUp() && neighbourSamples.AvailableLeft()){
                printf("============================A\n");
            }
            if(!neighbourSamples.AvailableUp() && neighbourSamples.AvailableLeft()){
                printf("============================B\n");
            }
            if(neighbourSamples.AvailableUp() && !neighbourSamples.AvailableLeft()){
                printf("============================C\n");
            }
            if(!neighbourSamples.AvailableUp() && !neighbourSamples.AvailableLeft()){
                printf("============================D\n");

                // 预测结果
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        int pred = 1 << (8 - 1);
                        printf(" %d ", 1 << (8 - 1));
                    }
                    printf("\n");
                }
                // 与残差叠加

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