#ifndef EYERLIB_BITSTREAM_HPP
#define EYERLIB_BITSTREAM_HPP

class BitStream {
public:
    BitStream(unsigned char * buf, int size);
    ~BitStream();

    int ReadU1();
    int ReadU(int n);

    int ReadUE();
    int ReadSE();

private:
    unsigned char * start = nullptr;
    int size = 0;
    unsigned char * p = nullptr;
    int bits_left;
};


#endif //EYERLIB_BITSTREAM_HPP
