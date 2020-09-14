#ifndef EYERLIB_EYERSPS_HPP
#define EYERLIB_EYERSPS_HPP

namespace Eyer{
    typedef enum {
        FALSE,
        TRUE
    } Boolean;

    class EyerSPS {
    public:
        EyerSPS();
        ~EyerSPS();

        int PrintInfo();

    private:
        unsigned int profile_idc;                                       // u(8)
        Boolean   constrained_set0_flag;                                // u(1)
        Boolean   constrained_set1_flag;                                // u(1)
        Boolean   constrained_set2_flag;                                // u(1)
        Boolean   constrained_set3_flag;                                // u(1)
        Boolean   constrained_set4_flag;                                // u(1)
        Boolean   constrained_set5_flag;                                // u(2)

        unsigned  int level_idc;                                        // u(8)
        unsigned  int seq_parameter_set_id;                             // ue(v)

        unsigned  int chroma_format_idc;                                // ue(v)


    };
}

#endif //EYERLIB_EYERSPS_HPP
