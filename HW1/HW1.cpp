// https://blog.naver.com/cksdn788/220794432210 -> transform
// https://cplusplus.com/reference/set/set/ -> set

#include <iostream>
#include <algorithm>
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

    void INSERT(HeapNode newNode, HeapNode *heap)
    {
        if (currentCount > maxCount)
        {
            cout << "Error: The heap reached its maximum size. Can not insert new data!\n";
        }

        this->currentCount++;
        int index = this->currentCount;

        while ((index != 1) && (newNode.score > heap[index / 2].score))
        {
            heap[index] = heap[index / 2];
            index / 2;
        }

        heap[index] = newNode;
    }

    HeapNode MAXIMUM(HeapNode *heap)
    {
        return heap[0];
    }

    HeapNode EXTRACTMAX(HeapNode *heap)
    {
        HeapNode *pReturnNode;
        HeapNode *pTempNode;
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
void getNewElement()
{
    HeapNode newNode;
    int score;
    cout << "Enter the name of the student: ";
    cin >> newNode.name;

    while (true)
    {
        cout << "Enter the score of the element: ";
        cin >> score;
        if (score < 0 || score > 100)
        {
            cout << "Number is out of the rannge 0 to 100\n";
            continue;
        }

        /// TODO: 인풋으로 스트링값 들어왔을때 처리리
        if (cin.fail())
        {
            cout << "Wrong Input! Please, put integer\n";
            continue;
        }

        newNode.score = score;
        break;
    }
    cout << "Enter the class name: ";
}

/// TODO: heap index 0 말고 1부터 시작이란다

int main()
{
    Menu menu;
    string selectedMenu;
    bool isLooping = true;

    HeapNode priorityQue[30];

    while (isLooping)
    {
        showMenu();
        selectedMenu = getUserMenuInput();
        menu = convertStringToMenu(selectedMenu);

        switch (menu)
        {
        case i:
            cout << "i\n";
            getNewElement();
            break;
        case d:
            cout << "d\n";
            break;
        case r:
            cout << "r\n";
            break;
        case n:
            cout << "n\n";
            break;
        case p:
            cout << "p\n";
            break;
        case q:
            cout << "q\n";
            isLooping = false;
            break;
        case w:
            cout << "wrong input\n";
            break;
        }
    }
    return 0;
}

void showMenu()
{
    cout << "*********** MENU ****************\n";
    cout << "I : Insert a new element into the queue\n";
    cout << "D : Delete the element with the largest key from the queue.\n";
    cout << "R : Retrieve the element with the largest key\n";
    cout << "N : Increase the key of an element in the queue\n";
    cout << "P : Print all elements in the queue\n";
    cout << "Q: Quit\n";
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
