#ifndef EYE_LIB_EYERBUFFER_HPP
#define EYE_LIB_EYERBUFFER_HPP

namespace Eyer{
    class EyerBuffer {
    public:
        EyerBuffer();
        ~EyerBuffer();

        EyerBuffer(const EyerBuffer & buffer);
        EyerBuffer & operator = (const EyerBuffer & buffer);

        int Append(unsigned char * _buf, int _bufLen);

        int GetBuffer(unsigned char * _buf);

        int Clear();
    private:
        unsigned char * buf = nullptr;
        int bufLen = 0;
    };
}

#endif //EYE_LIB_EYERBUFFER_HPP
