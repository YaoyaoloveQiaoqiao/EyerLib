#include <gtest/gtest.h>

#include "MBCore/MBCore.hpp"
#include "MBGL/MBGL.hpp"

#include "MathTest.hpp"

TEST(MBString, string){
    for(int i=0;i<100;i++){
        MB::MBString str = (MB::MBString)"/Users/lichi/Downloads/size.flv";

        MB::MBString strA = str;

        MB::MBString strB;
        strB = str;

        MB::MBString strEmptyA;
        EXPECT_TRUE(strEmptyA.IsEmpty());

        MB::MBString strEmptyB;
        EXPECT_TRUE(strEmptyB.IsEmpty());

        EXPECT_TRUE(strEmptyA == strEmptyB);

        strEmptyA = str;
        EXPECT_FALSE(strEmptyA == strEmptyB);

        strEmptyB = str;
        EXPECT_TRUE(strEmptyA == strEmptyB);
    }

    for(int i=0;i<100;i++){
        MB::MBString strA = "strA";
        MB::MBString strB = "strB";

        MB::MBString strAB = strA + strB;

        EXPECT_TRUE(strAB == "strAstrB");
    }
}

TEST(RedString_Test,string){
    
}

TEST(RedArgs_Test, args){
}

TEST(RedBtte_Test, byte){
}

TEST(MBTime, time){
    long long time = MB::MBTime::GetTime();
    MBLog("Time:%lld\n", time);
    MBLog("Time:%s\n", MB::MBTime::TimeFormat().str);
}

TEST(MBLinkedList_Test, insert_delete){
    MB::MBLinkedList<int> list;
    for (int i = 0; i < 100; i++) {
		if (list.insertEle(i, i)) {
			MBLog("MBLinkedList insert fail \n");
		}	
	}
    MBLog("circleElement \n");
    list.circleElement();
    MBLog("list Length :%d\n", list.getLength());	
    EXPECT_TRUE(list.getLength() == 100);

    int data1 = 0.0;
    list.find(0, data1);
    EXPECT_EQ(data1, 0);
   
    list.find(5, data1);
    EXPECT_EQ(data1, 5);
    MBLog("data5:%d\n", data1);

	list.deleteEle(0);
    EXPECT_TRUE(list.getLength() == 99);
    
    MBLog("list Length:%d\n", list.getLength());	

    list.clear();
    EXPECT_TRUE(list.getLength() == 0);

    for (int i = 0; i < 100; i++) {
		if (list.insertEle(i, i)) {
			MBLog("MBLinkedList insert fail \n");
		}	
	}
    MBLog("2. list Length :%d\n", list.getLength());	
    EXPECT_TRUE(list.getLength() == 100);

    list.find(0, data1);
    EXPECT_EQ(data1, 0);
    MBLog("2. data1:%d\n", data1);	
}

/*
TEST(MBLinkedList_Test, mem){
    MB::MBGLWindow windows("aaa", 100, 100);
    windows.Open();

    while(!windows.ShouldClose()){

        MB::MBLinkedList<MB::MBGLComponent *> aList;
        aList.clear();

        windows.Loop();
    }


    windows.Clear();
}
*/

TEST(MBLinkedList_Test, insertBack){
    MB::MBLinkedList<int> list;
    for (int i = 0; i < 100; i++) {
		if (list.insertBack(i)) {
			MBLog("MBLinkedList insert fail \n");
		}	
	}
    MBLog("circleElement \n");
    list.circleElement();
    MBLog("list Length :%d\n", list.getLength());	
    EXPECT_TRUE(list.getLength() == 100);

    int data1 = 0.0;
    list.find(0, data1);
    EXPECT_EQ(data1, 0);
    MBLog("data1:%d\n", data1);	
   
    list.find(5, data1);
    EXPECT_EQ(data1, 5);
    MBLog("data5:%d\n", data1);		

	list.deleteEle(0);
    EXPECT_TRUE(list.getLength() == 99);

    list.deleteEle(50);
    EXPECT_TRUE(list.getLength() == 98);
    
    MBLog("list Length:%d\n", list.getLength());	

    list.clear();
    EXPECT_TRUE(list.getLength() == 0);

    for (int i = 0; i < 100; i++) {
		if (list.insertBack(i)) {
			MBLog("MBLinkedList insert fail \n");
		}	
	}
    MBLog("2. list Length :%d\n", list.getLength());	
    EXPECT_TRUE(list.getLength() == 100);

    list.find(0, data1);
    EXPECT_EQ(data1, 0);
    MBLog("2. data1:%d\n", data1);

    list.clear();
    list.clear();	

}

TEST(MBQueue_Test, enQueue_deQueue){
    MB::MBQueue<int> queue;
	int num = 0;
	for (int i = 0; i < 10; i++) {
		queue.enQueue(i);
		queue.deQueue(num);
	}
    EXPECT_EQ(queue.getSize(),0);

	queue.clear();
	EXPECT_EQ(queue.getSize(),0);

	int res = queue.deQueue(num);
    EXPECT_EQ(res, -1);

	for (int i = 0; i < 100; i++) {
		queue.enQueue(i);
	}
    EXPECT_EQ(queue.getSize(), 100);

	for (int i = 0; i < 10; i++) {
		queue.deQueue(num);
	}
    EXPECT_EQ(queue.getSize(), 90);

    queue.clear();
    EXPECT_EQ(queue.getSize(), 0);

}

TEST(MBMap_Test, insert_clear){
    MB::MBMap<int, int> map;
    for(int i=0; i<10; i++){
        map.insert(i, i);
    }
    EXPECT_EQ(map.getSize(), 10);
    int value = 0;
    int ret = map.find(2, value);
    if(ret < 0){
        EXPECT_FALSE(value == 2);
    }else{
        EXPECT_TRUE(value == 2);
    }

    map.clear();
    map.clear();

    for(int i=0; i<100; i++){
        map.insert(i, i);
    }
    EXPECT_EQ(map.getSize(), 100);
    ret = map.find(5, value);
    if(ret < 0){
        EXPECT_FALSE(value == 5);
    }else{
        EXPECT_TRUE(value == 5);
    }

}

TEST(MBLinkedList_Test, sort){
    MB::MBLinkedList<int> list;
    for (int i = 100; i >=0; i--) {
        if (list.insertEle(i, 100-i)) {
			MBLog("MBLinkedList insert fail \n");
		}	
	}
    list.sort();
    int data1 = 20;
    list.find(0, data1);
    EXPECT_EQ(data1, 0);
    
}



TEST(MBMath, mat){
    MB::MBVec2 a;
}


int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
