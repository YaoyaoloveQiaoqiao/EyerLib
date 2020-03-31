#ifndef	EYER_CORE_STRING_H
#define	EYER_CORE_STRING_H

namespace MB {
    class MBString
    {
    public:
        char * str = nullptr;
        int ClearStr();

    public:
        MBString();
        MBString(const char str[]);
        MBString(const MBString & str);
        ~MBString();

        bool IsEmpty() const;

        MBString & operator = (const MBString & s);
        bool operator == (const MBString & s);

        bool operator > (const MBString & s);
        bool operator < (const MBString & s);

        MBString operator + (const MBString & s);

        static MBString Number(int num, MBString format = "%d");

        static MBString Number(long num);
        static MBString Number(long long num);
    };
}

#endif
