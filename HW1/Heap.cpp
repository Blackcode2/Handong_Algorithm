#include <iostream>
#include <string>
using namespace std;

struct HeapNode
{
    string name;
    int score;
    string className;
};

class Heap
{
private:
    int maxCount;
    int currentCount;

public:
    Heap(int maxCount)
        : maxCount{maxCount} {}

    void INSERT(HeapNode node, HeapNode &heap)
    {
    }
};