#ifndef	EYER_LIB_MATH_H
#define	EYER_LIB_MATH_H

namespace MB {

    class MBRand
    {
    public:
        int static Rand(int x);
    };

    class MBMat;
    class MBMat4x1;
    class MBMat3x1;
    class MBMat2x1;
    class MBMat4x4;

    typedef MBMat4x1 MBVec4;
    typedef MBMat3x1 MBVec3;
    typedef MBMat2x1 MBVec2;

    class MBMat
    {
    public:
        int row = 0;
        int col = 0;
        float * * mat = nullptr;

    private:
        void init(int row, int col);
        void output();

    public:
        MBMat(int row = 0, int col = 0);
        MBMat(const MBMat &m);

        ~MBMat();

        MBMat & operator = (const MBMat &m);
        MBMat operator * (const MBMat &m);
        MBMat operator * (const float a);
        MBMat operator + (const MBMat &m);
        MBMat operator - (const MBMat &m);

        /**
         * 矩阵转置
         * @return
         */
        MBMat operator ~ ();

        /**
         * 矩阵求逆
         * @return
         */
        // SvMat operator ! ();
        int Print();

        /**
         * 当你想要从 Mat 中拷贝出矩阵的 float 数组的时候，你应该先后调用 GetMatLen() 和 GetMat(),GetMatLen() 将告诉你你需要多大的空间来存放这个数组
         * @return 你需要的空间大小
         */
        int GetMatLen();

        /**
         * GetMat 将把数组拷贝到你分配的空间内，当 matBuffer == NULL 的时候，函数将内部 malloc 一个空间，但是这样外部其实无法知道数组的长度。
         * @param matBuffer 你想要拷贝的地方
         * @return 返回数组
         */ 
        float * GetMat(float * matBuffer = nullptr);
    };

    class MBMat4x4 : public MBMat
    {
    public:
        MBMat4x4();
        ~MBMat4x4();

        MBMat4x4(const MBMat & mat);

        MBMat4x4 & operator = (const MBMat &m);

        int SetScale(float x, float y, float z);
        int SetTrans(float x, float y, float z);
        int SetPerspective(float fov, float aspect, float near, float far);
        int SetOrtho(float l, float r, float t, float b, float near, float far);

        int SetRotate(float x, float y, float z, float a);

        int SetRotateX(float a);
        int SetRotateY(float a);
        int SetRotateZ(float a);
    };


    class MBMat4x1 : public MBMat
    {
    public:
        MBMat4x1();
        ~MBMat4x1();

        float x();
        float y();
        float z();
        float w();

        int SetX(float x);
        int SetY(float y);
        int SetZ(float z);
        int SetW(float w);
    };

    class MBMat3x1 : public MBMat
    {
    public:
        MBMat3x1();
        ~MBMat3x1();

        float x();
        float y();
        float z();

        int SetX(float x);
        int SetY(float y);
        int SetZ(float z);
    };

    class MBMat2x1 : public MBMat
    {
    public:
        MBMat2x1(float x, float y);
        MBMat2x1();

        MBMat2x1(const MBMat & m);

        ~MBMat2x1();

        float x();
        float y();

        int SetX(float x);
        int SetY(float y);
    };
}

#endif