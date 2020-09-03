#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerGL/EyerGL.hpp"

#include "MathTest.hpp"

TEST(EyerString, string){
    for(int i=0;i<100;i++){
        Eyer::EyerString str = (Eyer::EyerString)"/Users/lichi/Downloads/size.flv";

        Eyer::EyerString strA = str;

        Eyer::EyerString strB;
        strB = str;

        Eyer::EyerString strEmptyA;
        EXPECT_TRUE(strEmptyA.IsEmpty());

        Eyer::EyerString strEmptyB;
        EXPECT_TRUE(strEmptyB.IsEmpty());

        EXPECT_TRUE(strEmptyA == strEmptyB);

        strEmptyA = str;
        EXPECT_FALSE(strEmptyA == strEmptyB);

        strEmptyB = str;
        EXPECT_TRUE(strEmptyA == strEmptyB);
    }

    for(int i=0;i<100;i++){
        Eyer::EyerString strA = "strA";
        Eyer::EyerString strB = "strB";

        Eyer::EyerString strAB = strA + strB;

        EXPECT_TRUE(strAB == "strAstrB");
    }
}

TEST(RedString_Test,string){
    
}

TEST(RedArgs_Test, args){
}

TEST(RedBtte_Test, byte){
}

TEST(EyerTime, time){
    long long time = Eyer::EyerTime::GetTime();
    EyerLog("Time:%lld\n", time);
    EyerLog("Time:%s\n", Eyer::EyerTime::TimeFormat().str);
}

TEST(EyerLinkedList_Test, insert_delete){
    Eyer::EyerLinkedList<int> list;
    for (int i = 0; i < 100; i++) {
		if (list.insertEle(i, i)) {
			EyerLog("EyerLinkedList insert fail \n");
		}	
	}
    EyerLog("circleElement \n");
    list.circleElement();
    EyerLog("list Length :%d\n", list.getLength());	
    EXPECT_TRUE(list.getLength() == 100);

    int data1 = 0.0;
    list.find(0, data1);
    EXPECT_EQ(data1, 0);
   
    list.find(5, data1);
    EXPECT_EQ(data1, 5);
    EyerLog("data5:%d\n", data1);

	list.deleteEle(0);
    EXPECT_TRUE(list.getLength() == 99);
    
    EyerLog("list Length:%d\n", list.getLength());	

    list.clear();
    EXPECT_TRUE(list.getLength() == 0);

    for (int i = 0; i < 100; i++) {
		if (list.insertEle(i, i)) {
			EyerLog("EyerLinkedList insert fail \n");
		}	
	}
    EyerLog("2. list Length :%d\n", list.getLength());	
    EXPECT_TRUE(list.getLength() == 100);

    list.find(0, data1);
    EXPECT_EQ(data1, 0);
    EyerLog("2. data1:%d\n", data1);	
}

/*
TEST(EyerLinkedList_Test, mem){
    Eyer::EyerGLWindow windows("aaa", 100, 100);
    windows.Open();

    while(!windows.ShouldClose()){

        Eyer::EyerLinkedList<Eyer::EyerGLComponent *> aList;
        aList.clear();

        windows.Loop();
    }


    windows.Clear();
}
*/

TEST(EyerLinkedList_Test, insertBack){
    Eyer::EyerLinkedList<int> list;
    for (int i = 0; i < 100; i++) {
		if (list.insertBack(i)) {
			EyerLog("EyerLinkedList insert fail \n");
		}	
	}
    EyerLog("circleElement \n");
    list.circleElement();
    EyerLog("list Length :%d\n", list.getLength());	
    EXPECT_TRUE(list.getLength() == 100);

    int data1 = 0.0;
    list.find(0, data1);
    EXPECT_EQ(data1, 0);
    EyerLog("data1:%d\n", data1);	
   
    list.find(5, data1);
    EXPECT_EQ(data1, 5);
    EyerLog("data5:%d\n", data1);		

	list.deleteEle(0);
    EXPECT_TRUE(list.getLength() == 99);

    list.deleteEle(50);
    EXPECT_TRUE(list.getLength() == 98);
    
    EyerLog("list Length:%d\n", list.getLength());	

    list.clear();
    EXPECT_TRUE(list.getLength() == 0);

    for (int i = 0; i < 100; i++) {
		if (list.insertBack(i)) {
			EyerLog("EyerLinkedList insert fail \n");
		}	
	}
    EyerLog("2. list Length :%d\n", list.getLength());	
    EXPECT_TRUE(list.getLength() == 100);

    list.find(0, data1);
    EXPECT_EQ(data1, 0);
    EyerLog("2. data1:%d\n", data1);

    list.clear();
    list.clear();	

}

TEST(EyerQueue_Test, enQueue_deQueue){
    Eyer::EyerQueue<int> queue;
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
/*
TEST(EyerMap_Test, insert_clear){
    Eyer::EyerMap<int, int> map;
    for(int i=0; i<10; i++){
        map.Insert(i, i);
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
 */

TEST(EyerLinkedList_Test, sort){
    Eyer::EyerLinkedList<int> list;
    for (int i = 100; i >=0; i--) {
        if (list.insertEle(i, 100-i)) {
			EyerLog("EyerLinkedList insert fail \n");
		}	
	}
    list.sort();
    int data1 = 20;
    list.find(0, data1);
    EXPECT_EQ(data1, 0);   
}



TEST(EyerMath, mat){
    Eyer::EyerVec2 a;
}


TEST(LRUCache, LRUCache){
    // Eyer::EyerVec4;
    Eyer::EyerLRUMap<int, Eyer::EyerVec4> lruMap(10);

    for(int i=0;i<100;i++){
        Eyer::EyerVec4 * vec4 = new Eyer::EyerVec4();
        lruMap.Put(i, vec4);

        int size = lruMap.Size();
        // printf("Size:%d \n", size);

        EXPECT_LE(size, 10);
    }
}


TEST(Map, MapTest){
    std::map<Eyer::EyerString, Eyer::EyerString> m;

    m.insert(std::pair<Eyer::EyerString, Eyer::EyerString>("a", "miaowu_a"));
    m.insert(std::pair<Eyer::EyerString, Eyer::EyerString>("b", "miaowu_b"));
    m.insert(std::pair<Eyer::EyerString, Eyer::EyerString>("c", "miaowu_c"));
    m.insert(std::pair<Eyer::EyerString, Eyer::EyerString>("d", "miaowu_d"));
    m.insert(std::pair<Eyer::EyerString, Eyer::EyerString>("e", "miaowu_e"));
    m.insert(std::pair<Eyer::EyerString, Eyer::EyerString>("f", "miaowu_f"));

    int size = m.size();

    EyerLog("Map Size: %d\n", size);

    std::map<Eyer::EyerString, Eyer::EyerString>::iterator iter;
    for(iter = m.begin(); iter != m.end(); iter++){
        EyerLog("key: %s   value: %s\n", iter->first.str, iter->second.str);
    }

    {
        std::map<Eyer::EyerString, Eyer::EyerString>::iterator it;
        it = m.find(Eyer::EyerString("a"));
        if (it != m.end()){
            EyerLog("key: %s   value: %s\n", it->first.str, it->second.str);
        }
    }

    {
        std::map<Eyer::EyerString, Eyer::EyerString>::iterator it;
        it = m.find(Eyer::EyerString("b"));
        if (it != m.end()){
            EyerLog("key: %s   value: %s\n", it->first.str, it->second.str);
        }
    }
    {
        std::map<Eyer::EyerString, Eyer::EyerString>::iterator it;
        it = m.find(Eyer::EyerString("c"));
        if (it != m.end()){
            EyerLog("key: %s   value: %s\n", it->first.str, it->second.str);
        }
    }

}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
