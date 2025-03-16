// https://blog.naver.com/cksdn788/220794432210 -> transform
// https://cplusplus.com/reference/set/set/ -> set

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

#define MAXHEAPSIZE 30

struct HeapNode
{
    string name;
    int score;
    string className;
};

class Heap
{
private:
    int maxCount = 0;
    int currentCount = 0;
    HeapNode *pData;

public:
    Heap(int maxCount)
        : maxCount{maxCount}
    {
        this->pData = new HeapNode[maxCount + 1];
    }

    int getCurrentCount()
    {
        return this->currentCount;
    }

    void insert(HeapNode newNode)
    {
        if (currentCount >= maxCount)
        {
            cout << "Error: The heap reached its maximum size. Can not insert new data!\n";
        }

        this->currentCount++;
        int index = this->currentCount;

        while ((index != 1) && (newNode.score > this->pData[index / 2].score))
        {
            this->pData[index] = this->pData[index / 2];
            index /= 2;
        }

        this->pData[index] = newNode;
    }

    HeapNode maximum()
    {
        return pData[1];
    }

    HeapNode extracktMax()
    {

        if (this->currentCount <= 0 || this->pData == nullptr)
        {
            throw runtime_error("Cannot delete from an empty queue.!");
        }

        HeapNode pReturnNode = this->pData[1];

        HeapNode pTempNode = this->pData[this->currentCount];
        this->currentCount--;

        int parent = 1, child = 2;

        while (child <= this->currentCount)
        {

            if (child < this->currentCount && this->pData[child].score < this->pData[child + 1].score)
            {
                child++;
            }

            if (pTempNode.score >= this->pData[child].score)
            {
                break;
            }

            this->pData[parent] = this->pData[child];
            parent = child;
            child *= 2;
        }
        this->pData[parent] = pTempNode;

        return pReturnNode;
    }

    void printQueue()
    {
        if (this->currentCount <= 0)
        {
            cout << "The queue is empty!\n";
            return;
        }
        cout << "Current queue elements:\n";
        for (int i = 1; i <= this->currentCount; i++)
        {
            cout << i << "." << "[" << this->pData[i].name << ", " << this->pData[i].score << ", " << this->pData[i].className << "]\n";
        }

        cout << endl;
    }
};

void showMenu();
string preprocessInput(string input);
string getUserMenuInput();
enum Menu
{
    i,
    d,
    r,
    n,
    p,
    q,
    w
};

Menu convertStringToMenu(string str);
void getNewData(Heap *pq);
void showMaxData(Heap *pq);
void deleteData(Heap *pq);

int main()
{
    Heap prioritQueue{MAXHEAPSIZE};
    Menu menu;
    string selectedMenu;
    bool isLooping = true;

    while (isLooping)
    {
        showMenu();
        selectedMenu = getUserMenuInput();
        menu = convertStringToMenu(selectedMenu);

        switch (menu)
        {
        case i:
            getNewData(&prioritQueue);
            break;
        case d:
            deleteData(&prioritQueue);
            break;
        case r:
            showMaxData(&prioritQueue);
            break;
        case n:
            cout << "n\n";
            break;
        case p:
            prioritQueue.printQueue();
            break;
        case q:
            cout << "Program terminated.\n";
            isLooping = false;
            break;
        case w:
            cout << "wrong input. Tyr again.\n";
            break;
        }
    }

    return 0;
}

void showMenu()
{
    cout << "\n";
    cout << "*********** MENU ****************\n";
    cout << "I : Insert a new element into the queue\n";
    cout << "D : Delete the element with the largest key from the queue.\n";
    cout << "R : Retrieve the element with the largest key\n";
    cout << "N : Increase the key of an element in the queue\n";
    cout << "P : Print all elements in the queue\n";
    cout << "Q: Quit\n";
    cout << endl;
}

string preprocessInput(string input)
{
    string processedInput = input;

    if (processedInput.length() > 1)
    {
        return NULL;
    }
    transform(processedInput.begin(), processedInput.end(), processedInput.begin(), ::tolower);

    return processedInput;
}

string getUserMenuInput()
{
    string input;
    cout << "Choose user menu: ";
    cin >> input;

    string processedInput = preprocessInput(input);

    return processedInput;
}

Menu convertStringToMenu(string str)
{
    if (str == "i")
    {
        return i;
    }
    else if (str == "d")
    {
        return d;
    }
    else if (str == "r")
    {
        return r;
    }
    else if (str == "n")
    {
        return n;
    }
    else if (str == "p")
    {
        return p;
    }
    else if (str == "q")
    {
        return q;
    }
    else
    {
        return w;
    }
}

void getNewData(Heap *pq)
{

    if (pq->getCurrentCount() == MAXHEAPSIZE)
    {
        cout << "The heap is full! You can not insert additional data.\n";
        return;
    }

    HeapNode newNode;
    int score;

    cin.ignore(); // 버퍼에 남아있을 수 있는 개행문자 제거
    cout << "Enter the name of the student: ";
    getline(cin, newNode.name);

    while (true)
    {
        cout << "Enter the score of the element: ";
        cin >> score;
        if (score < 0 || score > 100)
        {
            cout << "Number is out of the rannge 0 to 100\n";
            continue;
        }

        /// TODO: 인풋으로 스트링값 들어왔을때 처리 for case2

        newNode.score = score;
        break;
    }

    cin.ignore();
    cout << "Enter the class name: ";
    getline(cin, newNode.className);

    pq->insert(newNode);
    cout << "New Element: [" << newNode.name << ", " << newNode.score << ", " << newNode.className << "] has been inserted.\n";
}

void showMaxData(Heap *pq)
{
    if (pq->getCurrentCount() <= 0)
    {
        cout << "The queue is empty!\n";
        return;
    }
    HeapNode maxNode = pq->maximum();
    cout << "Element with the largest key: [" << maxNode.name << ", " << maxNode.score << ", " << maxNode.className << "]\n";
}

void deleteData(Heap *pq)
{
    if (pq->getCurrentCount() <= 0)
    {
        cout << "Cannot delete from an empty queue.\n";
        return;
    }
    HeapNode maxNode;
    maxNode = pq->extracktMax();

    cout << "Deleted element: [" << maxNode.name << ", " << maxNode.score << ", " << maxNode.className << "]\n";

    cout << endl;
}