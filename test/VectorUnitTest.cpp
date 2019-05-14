/* ==================================================
+				CS1C Final Project:
+				Group Members - 6
+				Date: 5/14/2019
+               Spring Semester
+               Professor: John Kath
+				Members (6):
+	Joshua Yang (jmyphotographybooking@gmail.com)
+	Qian tai Chen (qiantaichen0303@gmail.com)
+	x (Jdu9572@gmail.com)
+	x (jonasqiang8@gmail.com)
+	x
+	x
+	
+
+
===================================================== */

#include "gtest/gtest.h"
#include "VectorNode.h"
#include "LinkedList.h"
#include "vector.h"
#include <iostream>
#include <vector>

using namespace cs1c;

const char SAMPLE_DEFAULT_NAME[] = "nothing";
const int  SAMPLE_DEFAULT_VALUE = 123;

class Sample {
public:
    Sample()
      : name(SAMPLE_DEFAULT_NAME), value(SAMPLE_DEFAULT_VALUE) {
    }
    std::string name;
    int         value;
};
#if 1
TEST(Vector_Node_Unit_Test, Default_Constructor_Test) {
    VectorNode<int> vectorNode;
    ASSERT_EQ(vectorNode.next, &vectorNode);    
    ASSERT_EQ(vectorNode.previous, &vectorNode); 
    ASSERT_EQ(vectorNode.arrayOfObjects, nullptr); 
    ASSERT_EQ(vectorNode.size, 0); 
    ASSERT_EQ(vectorNode.runningCapacity, 0); 
}

TEST(Vector_Node_Unit_Test, Non_Default_Constructor_Test) {
    int arrayOfObjects[100];
    for (int capcityFactor = 1; capcityFactor <= 3; capcityFactor++) {
        for (int size = 1; size < 1000; size++) {
            int runningCapacity = size * capcityFactor;
            VectorNode<int> vectorNode(arrayOfObjects, size, runningCapacity); 
            ASSERT_EQ(vectorNode.next, &vectorNode);    
            ASSERT_EQ(vectorNode.previous, &vectorNode); 
            ASSERT_EQ(vectorNode.arrayOfObjects, arrayOfObjects); 
            ASSERT_EQ(vectorNode.size, size); 
            ASSERT_EQ(vectorNode.runningCapacity, runningCapacity); 
        }
    }
}

TEST(Linked_List_Unit_Test, Linked_List_Constructor_Test) {
    LinkedList<int> vectorNodeLinkedList;
    ASSERT_TRUE(vectorNodeLinkedList.empty());
}

TEST(Vector_Unit_Test, Vector_Default_Constructor_Test) {
    int defaultSize = 0;
    cs1c::vector<int> vector;
    ASSERT_EQ(vector.size(), defaultSize); 
    ASSERT_EQ(vector.capacity(), defaultSize); 
}

TEST(Vector_Unit_Test, Vector_Size_Arg_Constructor_Test) {
    for (int size = 0; size < 1000; size++) {
        cs1c::vector<int> vector(size);
        ASSERT_EQ(vector.size(), size); 
        ASSERT_EQ(vector.capacity(), size); 
    }
}

TEST(Vector_Unit_Test, Vector_Size_Constructor_Test) {
    const int SIZE = 10;
    cs1c::vector<Sample> sampleVector(SIZE);
    ASSERT_EQ(sampleVector.size(), SIZE); 
    ASSERT_EQ(sampleVector.capacity(), SIZE); 
    for (int index = 0; index < SIZE; index++) {
        Sample sample = sampleVector[index];
        ASSERT_EQ(sample.value, SAMPLE_DEFAULT_VALUE); 
        ASSERT_STREQ(sample.name.c_str(), SAMPLE_DEFAULT_NAME); 
    }
}

TEST(Vector_Unit_Test, Copy_Constructor_Test) {
    const int SIZE = 10;
    cs1c::vector<int> listA(SIZE);
    for (int index = 0; index < listA.size(); index++) {
        listA[index] = index;
    }
    listA.push_back(SIZE);
    listA.reserve(SIZE * 10);
    
    cs1c::vector<int> listB = listA;
    ASSERT_EQ(listA.size(), listB.size());
    ASSERT_EQ(listA.capacity(), listB.capacity());
    
    for (int index = 0; index < listA.size(); index++) {
        ASSERT_EQ(listA[index], listB[index]);
    }
}

cs1c::vector<int> returnMove(cs1c::vector<int>& listA) {
    cs1c::vector<int> listC(listA);
    return std::move(listC);
}

TEST(Vector_Unit_Test, Move_Constructor_Test) {
    const int SIZE = 10;
    cs1c::vector<int> listA(SIZE);
    for (int index = 0; index < listA.size(); index++) {
        listA[index] = index;
    }
    listA.push_back(SIZE);
    listA.reserve(SIZE * 10);
    
    cs1c::vector<int> listC(listA);
    cs1c::vector<int> listB = std::move(listC);
    ASSERT_EQ(listA.size(), listB.size());
    ASSERT_EQ(listA.capacity(), listB.capacity());
    
    for (int index = 0; index < listA.size(); index++) {
        ASSERT_EQ(listA[index], listB[index]);
    }
}

TEST(Vector_Unit_Test, Move_Assignment_Test) {
    const int SIZE = 10;
    cs1c::vector<int> listA(SIZE);
    for (int index = 0; index < listA.size(); index++) {
        listA[index] = index;
    }
    listA.push_back(SIZE);
    listA.reserve(SIZE * 10);
    
    cs1c::vector<int> listC(listA);
    cs1c::vector<int> listB;
    listB = std::move(listC);
    ASSERT_EQ(listA.size(), listB.size());
    ASSERT_EQ(listA.capacity(), listB.capacity());
    
    for (int index = 0; index < listA.size(); index++) {
        ASSERT_EQ(listA[index], listB[index]);
    }
}

TEST(Vector_Unit_Test, Assignment_Constructor_Test) {
    const int SIZE = 10;
    cs1c::vector<int> listA(SIZE);
    for (int index = 0; index < listA.size(); index++) {
        listA[index] = index;
    }
    listA.push_back(SIZE);
    listA.reserve(SIZE * 10);
    
    cs1c::vector<int> listB;
    listB = listA;
    ASSERT_EQ(listA.size(), listB.size());
    ASSERT_EQ(listA.capacity(), listB.capacity());
    
    for (int index = 0; index < listA.size(); index++) {
        ASSERT_EQ(listA[index], listB[index]);
    }
}

TEST(Vector_Unit_Test, Single_Node_Constructor_Test) {
    int seed = 123;
    for (int size = 1; size < 1000; size++) {
        cs1c::vector<int> list(size);
        ASSERT_EQ(list.size(), size);
        ASSERT_EQ(list.capacity(), size);
        for (int index = 0; index < size; index++) {
            list[index] = seed + index;
        }
        for (int index = 0; index < size; index++) {
            ASSERT_EQ(list[index], seed + index);
        }
    }
}

TEST(Vector_Unit_Test, Multiple_Node_Test) {
    int seed = 62;
    int nodeSize = 10;
    int totalSize = nodeSize;
    int oldSize = 0;
    cs1c::vector<int> list;
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.capacity(), 0);
    for (int nodeCount = 1; nodeCount < 10; nodeCount++) {
        list.resize(totalSize);
        ASSERT_EQ(list.size(), totalSize);
        ASSERT_EQ(list.capacity(), totalSize);
        for (int index = oldSize; index < list.size(); index++) {
            list[index] = seed + index;
        }
        for (int index = 0; index < list.size(); index++) {
            ASSERT_EQ(list[index], seed + index);
        }
        nodeSize *= 2;
        oldSize = totalSize;
        totalSize += nodeSize;
    }
}

TEST(Vector_Unit_Test, Multiple_Node_Capacity_Test) {
    int nodeCapacity = 10;
    int totalCapacity = nodeCapacity;
    cs1c::vector<int> list;
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.capacity(), 0);
    for (int nodeCount = 1; nodeCount < 10; nodeCount++) {
        list.reserve(totalCapacity);
        ASSERT_EQ(list.size(), 0);
        ASSERT_EQ(list.capacity(), totalCapacity);
        nodeCapacity *= 2;
        totalCapacity += nodeCapacity;
    }
}

TEST(Vector_Unit_Test, Single_Node_Push_Back_Test) {
    int seed = 98;
    cs1c::vector<int> list;
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.capacity(), 0);
    for (int entryCount = 1; entryCount <= 8; entryCount++) {
        list.push_back((entryCount - 1) + seed);
        ASSERT_EQ(list.size(), entryCount);
        ASSERT_EQ(list.capacity(), 8);
        for (int index = 0; index < list.size(); index++) {
             ASSERT_EQ(list[index], seed + index);
        }
    }
}

TEST(Vector_Unit_Test, Multi_Node_Push_Back_Test) {
    int seed = 98;
    cs1c::vector<int> list;
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.capacity(), 0);
    int capacity = 8;
    for (int entryCount = 1; entryCount <= 1024; entryCount++) {
        list.push_back((entryCount - 1) + seed);
        ASSERT_EQ(list.size(), entryCount);
        if (entryCount > capacity)
            capacity *= 2;
        ASSERT_EQ(list.capacity(), capacity);
        for (int index = 0; index < list.size(); index++) {
             ASSERT_EQ(list[index], seed + index);
        }
    }
}

TEST(Vector_Unit_Test, Single_Node_Iterator_Test) {
    int seed = 0;
    for (int size = 1; size < 1000; size++) {
        cs1c::vector<int> list(size);
        ASSERT_EQ(list.size(), size);
        ASSERT_EQ(list.capacity(), size);
        for (int index = 0; index < size; index++) {
            list[index] = seed + index;
        }
        for (int pre = 0; pre < 2; pre++) {
            int index = 0;
            cs1c::vector<int>::iterator iter = list.begin();
            while (iter != list.end()) {
                int expectedValue = seed + index;
                int value = *iter;
                ASSERT_EQ(value, expectedValue);
                index++;
                if (pre == 0) {
                    ++iter;
                }
                else {
                    iter++;
                }
            }
        }
    }
}

TEST(Vector_Unit_Test, Single_Node_Greater_Capacity_Iterator_Test) {
    int seed = 123;
    int CAPCITY_FACTOR = 2;
    int MAX_VECTOR_SIZE = 1000;
    for (int vectorSize = 1; vectorSize < MAX_VECTOR_SIZE; vectorSize++) {
        cs1c::vector<int> list;
        list.reserve(vectorSize * CAPCITY_FACTOR);
        list.resize(vectorSize);
        ASSERT_EQ(list.size(), vectorSize);
        ASSERT_EQ(list.capacity(), vectorSize * CAPCITY_FACTOR);
        for (int index = 0; index < list.size(); index++) {
            list[index] = seed + index;
        }
        for (int pre = 0; pre < 2; pre++) {
            int index = 0;
            cs1c::vector<int>::iterator iter = list.begin();
            while (iter != list.end()) {
                int expectedValue = seed + index;
                int value = *iter;
                ASSERT_EQ(value, expectedValue);
                index++;
                if (pre == 0) {
                    ++iter;
                }
                else {
                    iter++;
                }
            }
        }
    }
}

TEST(Vector_Unit_Test, Single_Node_Erase_Test) {
    const int SIZE = 100;
    const int SEED = 0;
    cs1c::vector<int> list(SIZE);
    ASSERT_EQ(list.size(), SIZE);
    ASSERT_EQ(list.capacity(), SIZE);
    for (int index = 0; index < list.size(); index++) {
        list[index] = SEED + index;
    }
#if 0    
    for (int index = 0; index < list.size(); index++) {
        std::cout << index << ", " << list[index] << std::endl;
    }
#endif    
    int removeCount = 0;
    for (int index = 0; index < SIZE; index += 2) {
        cs1c::vector<int>::iterator iter = list.begin();
        int removeValue = SEED + index;
        while (iter != list.end()) {
            if (*iter == removeValue) {
//                std::cout << "remove " << removeValue << std::endl;
                list.erase(iter);
                removeCount++;
                break;
            }
            ++iter;
        }
        ASSERT_EQ(list.size(), SIZE - removeCount);
        ASSERT_EQ(list.capacity(), SIZE - removeCount);
    }
#if 0    
    for (int index = 0; index < list.size(); index++) {
        std::cout << index << ", " << list[index] << std::endl;
    }
#endif    
    cs1c::vector<int>::iterator iter = list.begin();
    int number = 1;
    while (iter != list.end()) {
        int expectedValue = SEED + number;
        //std::cout << "found " << *iter << ", expectedValue " << expectedValue << std::endl;
        ASSERT_EQ(*iter, expectedValue);
        ++iter;
        number += 2;
    }
}
#endif

bool inList(std::vector<int> values, int checkValue) {
    for (int index = 0; index < static_cast<int>(values.size()); index++) {
        if (values[index] == checkValue) {
            return true;
        }
    }
    return false;
}

TEST(Vector_Unit_Test, Multi_Node_Erase_Test) {
    const int STARTING_SIZE = 2;
    const int MAX_NODE_COUNT = 10;
    int size = STARTING_SIZE;
    cs1c::vector<int> list(size);
    ASSERT_EQ(list.size(), size);
    ASSERT_EQ(list.capacity(), size);
    // Add nodes, increasing the size and capacity
    for (int nodeCount = 1; nodeCount < MAX_NODE_COUNT; nodeCount++) {
        size *= 2;
        list.resize(size);
        ASSERT_EQ(list.size(), size);
        ASSERT_EQ(list.capacity(), size);
    }
    int fixedSize = list.size();
    // Add nodes, increasing the capacity only
    for (int nodeCount = 1; nodeCount < MAX_NODE_COUNT; nodeCount++) {
        size += (10 * nodeCount);
        list.reserve(size);
        ASSERT_EQ(list.size(), fixedSize);
        ASSERT_EQ(list.capacity(), size);
    }
    int fixedCapacity = list.capacity();
    
    // set the value of all entries
    for (int index = 0; index < list.size(); index++) {
        list[index] = index;
        //std::cout << index << ", " << list[index] << std::endl;
    }

    int removeCount = 0;
    int oldSize = 0;
    int newSize = STARTING_SIZE;
    int removeValue = STARTING_SIZE/2;
    int maxIndex = list.size()/2;
    std::vector<int> removedValues;
    for (int index = 0; index < maxIndex; index++) {
        {
            cs1c::vector<int>::iterator iter = list.begin();
            while (iter != list.end()) {
                if (*iter == removeValue) {
                    //std::cout << "remove " << removeValue << std::endl;
                    removedValues.push_back(removeValue);
                    //std::cout << "add to skip list " << removeValue << std::endl;
                    list.erase(iter);
                    removeCount++;
                    oldSize = newSize;
                    if (newSize > 20) {
                        newSize *= 1.1;
                        removeValue = oldSize + (newSize - oldSize)/5;
                    }
                    else {
                        newSize *= 2;
                        removeValue = oldSize + (newSize - oldSize)/2;
                    }
                    break;
                }
                ++iter;
            }
            ASSERT_EQ(list.size(), fixedSize - removeCount);
            ASSERT_EQ(list.capacity(), fixedCapacity - removeCount);
        }
#if 0
        std::cout << "values to skip: [";
        for (int count = 0; count < static_cast<int>(removedValues.size()); count++) {
            std::cout << removedValues[count] << " ";
        }
        std::cout << "]" << std::endl;
#endif
        int count = 0;
        cs1c::vector<int>::iterator iter = list.begin();
        while (iter != list.end()) {
            int expectedValue;
            // Get the next expected value, skipped removed values.
            for (;;) {
                expectedValue = count++;
                if (inList(removedValues, expectedValue)) {
                    //std::cout << "skipped " << expectedValue << std::endl;
                }
                else {
                    break;
                }
            }
            
            ASSERT_EQ(*iter, expectedValue);
            ++iter;
        }
    }

    for (int index = 0; index < list.size(); index++) {
       // std::cout << index << ", " << list[index] << std::endl;
    }
}

TEST(Vector_Unit_Test, Single_Node_Insert_Test) {
    const int SIZE = 100;
    cs1c::vector<int> list(SIZE);
    ASSERT_EQ(list.size(), SIZE);
    ASSERT_EQ(list.capacity(), SIZE);
    for (int index = 0; index < list.size(); index++) {
        list[index] = index * 2;
    }
    int insertCount = 0;
    for (int index = 0; index < (SIZE * 2); index += 2) {
        cs1c::vector<int>::iterator iter = list.begin();
        int insertValue = index;
        while (iter != list.end()) {
            if (*iter == insertValue) {
                list.insert(iter, ++insertValue);
                insertCount++;
                break;
            }
            ++iter;
        }
        ASSERT_EQ(list.size(), SIZE + insertCount);
        ASSERT_EQ(list.capacity(), SIZE + insertCount);
    }
    cs1c::vector<int>::iterator iter = list.begin();
    int expectedValue = 0;
    while (iter != list.end()) {
        ASSERT_EQ(*iter, expectedValue++);
        ++iter;
    }
}

TEST(Vector_Unit_Test, Basic_Usage_Test) {
    const int SIZE = 10;
    cs1c::vector<int> list;
    
    for (int i = 0; i < SIZE; ++i) {
        list.push_back(i);
    }
    
    int size = 0;
    for (auto i : list) {
        ASSERT_EQ(size, i);
        ++size;
    }
    
    ASSERT_EQ(SIZE, size);
    ASSERT_EQ(SIZE, list.size());
}

TEST(Vector_Unit_Test, Reserve_Test) {
    const int CAPACITY = 10;
    cs1c::vector<int> list;
    
    list.reserve(CAPACITY);
    
    int size = 0;
    for (auto i : list) {
        ASSERT_EQ(size, i);
        ++size;
    }
    
    ASSERT_EQ(0, size);
    ASSERT_EQ(0, list.size());
}

TEST(Vector_Unit_Test, Erase_Test) {
    cs1c::vector<int> list;
    
    list.push_back(0);
    list.erase(list.begin());
    
    int size = 0;
    for (auto i : list) {
        ASSERT_EQ(size, i);
        ++size;
    }
    
    ASSERT_EQ(0, size);
    ASSERT_EQ(0, list.size());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
