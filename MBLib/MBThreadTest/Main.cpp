#include <stdio.h>
#include <gtest/gtest.h>

#include "MBThread/MBThread.hpp"
#include "MBCore/MBCore.hpp"

class TimeThread : public MB::MBThread
{
private:
    MB::MBString tag;

public:
    TimeThread(MB::MBString _tag){
        tag = _tag;
    }

    virtual void Run()
    {
        SetRunning();

        while(!stopFlag){
            printf("this from: %s\n", tag.str);
            MB::MBTime::MBSleep(1000 * 1000);
        }

        SetStoping();
    }
};

TEST(MB, MBThread){
    TimeThread a("A");
    TimeThread b("B");

    a.Detach();
    b.Detach();

    MB::MBTime::MBSleep(1000 * 1000 * 10);

    a.Stop();
    b.Stop();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}