// Blog: https://blog.naver.com/cksdn788/220794432210
// Blog: https://cplusplus.com/reference/set/set/
// Stackoverflow: https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
// Blog: https://dntworry-behappy.tistory.com/2

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// heap의 최대 수 설정
#define MAXHEAPSIZE 30

struct HeapNode
{
    string name;
    int score;
    string className;
};

// Heap을 다루는 클래스 
class Heap
{
private:
    int maxCount = 0;
    int currentCount = 0;
    HeapNode *pData;

public:
    // 생성자: 클래스 인스턴스 생성할때 힙 쵀대 수 받아서 멤버변수에 저장, 이때 +1 해서 index 1부터 시작하도록 변경
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

        // 현재 Heap의 데이터 개수 증가시켜준다
        this->currentCount++;
        int index = this->currentCount; // Heap의 마지막에 새로운 데이터 추가하는 것과 마찬가지

        // Heapyfiy UP
        // 새롭게 추가되는 데이터가 부모보다 큰지 확인
        while ((index != 1) && (newNode.score > this->pData[index / 2].score))
        {
            // 부모 데이터가 더 작으면 자식과 위치 교환
            this->pData[index] = this->pData[index / 2];
            index /= 2;
        }
        // 최종 위치 확정
        this->pData[index] = newNode;
    }

    // Heap의 가장 큰 값 리턴
    HeapNode maximum()
    {
        return pData[1];
    }

    // Heap의 가장 큰 값인 루트 삭제
    HeapNode extractMax()
    {

        if (this->currentCount <= 0 || this->pData == nullptr)
        {
            throw runtime_error("Cannot delete from an empty queue.!");
        }

        // 루트노드 반환용 변수에 담아줌
        HeapNode pReturnNode = this->pData[1];

        // HeapifyDown을 위해서는 가장 마자막 노드를 루트 노드에 올려주어야 함 
        // 그 과정을 위해 가장 마자막 노드를 임시 변수에 담음
        HeapNode pTempNode = this->pData[this->currentCount];
        this->currentCount--;

        int parent = 1, child = 2;

        while (child <= this->currentCount)
        {
            // 자식노드 중 왼쪽 자식이 더 큰지 오른쪽 자식이 더 큰지 비교
            if (child < this->currentCount && this->pData[child].score < this->pData[child + 1].score)
            {
                child++;
            }

            // 루트로 올린 마지막 노드가 자식 노드보다 크면 중단
            if (pTempNode.score >= this->pData[child].score)
            {
                break;
            }

            // 더 큰 자식 노드를 부모 노드와 위치 교체
            this->pData[parent] = this->pData[child];
            parent = child;
            child *= 2;
        }
        // 최종 위치 확정
        this->pData[parent] = pTempNode;

        return pReturnNode;
    }

    // Heap을 순회하면서 루트부트 차례로 Heapoder로 출력
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

    // 기존 데이터의 값을 수정
    void increaseKey()
    {

        if (this->currentCount <= 0)
        {
            cout << "The queue is empty.\n";
            return;
        }

        int selectedIndex;
        int newScore;

        while (true)
        {

            cin.ignore(); // 버퍼에 남아있는 개행문자 제거
            cout << "Enter the index of the Eelment: ";
            cin >> selectedIndex;
            if (selectedIndex <= 0 || selectedIndex > this->currentCount)
            {
                cout << "Wrong Index, Try again.\n";
                continue;
            }

            break;
        }

        while (true)
        {
            cin.ignore(); // 버퍼에 남아있는 개행문자 제거
            cout << "Enter the new score: ";
            cin >> newScore;

            if (this->pData[selectedIndex].score > newScore)
            {
                cout << "New score should be larger than current score. Please enter again.\n";
                continue;
            }

            break;
        }

        // 변경된 값으로 바꿔줌
        this->pData[selectedIndex].score = newScore;
        HeapNode modifiedNode = this->pData[selectedIndex]; // 새로운 위치를 찾기 위해 임시 노드에 값 복사

        int index = selectedIndex;

        // 부모 노드 보다 값이 큰지 확인
        while ((index != 1) && (newScore > this->pData[index / 2].score))
        {
            this->pData[index] = this->pData[index / 2];
            index /= 2;
        }

        this->pData[index] = modifiedNode;

        cout << "Key updated. [" << modifiedNode.name << ", " << modifiedNode.score << ", " << modifiedNode.className << "] has been repositioned in the queue.\n";
    }
};

void showMenu();
string preprocessInput(string input);
string getUserMenuInput();

// 유저의 선택 메뉴는 enum으로 관리 -> 코드 읽기가 더 편함
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
            // 새로운 데이터 추가
            getNewData(&prioritQueue);
            break;
        case d:
            // 가장 큰 값 삭제
            deleteData(&prioritQueue);
            break;
        case r:
            // 가장 큰 값 리턴
            showMaxData(&prioritQueue);
            break;
        case n:
            // 기존 데이터 수정
            prioritQueue.increaseKey();
            break;
        case p:
            // Heqp 전체 출력
            prioritQueue.printQueue();
            break;
        case q:
            // 프로그램 종료
            cout << "Program terminated.\n";
            isLooping = false;
            break;
        case w:
            // 잘못된 입력값은 다 여기로 들어옴
            cout << "Wrong input. Tyr again.\n";
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

// 유저가 선택한 메뉴가 valid한지 체크하고 대문자 소문자 상관없이 인식하도록 전처리
string preprocessInput(string input)
{
    string processedInput = input;

    if (processedInput.length() > 1)
    {
        return "w";
    }
    //대문자 소문자로 변경 경
    transform(processedInput.begin(), processedInput.end(), processedInput.begin(), ::tolower);

    return processedInput;
}

// 유저가 선택하는 메뉴를 받는 함수
string getUserMenuInput()
{
    string input;
    cout << "Choose user menu: ";
    cin >> input;

    string processedInput = preprocessInput(input);

    return processedInput;
}

// 유저의 인풋을 스위치문으로 받기 위해서 선언한 Menu enum으로 변환
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


// 새로운 데이터를 받기 위한 함수
// Heap Class의 insert 함수 호출
void getNewData(Heap *pq)
{

    if (pq->getCurrentCount() == MAXHEAPSIZE)
    {
        cout << "The heap is full! You can not insert additional data.\n";
        return;
    }

    HeapNode newNode;
    string scoreInput;
    int score;

    cin.ignore(); // 버퍼에 남아있을 수 있는 개행문자 제거
    cout << "Enter the name of the student: ";
    getline(cin, newNode.name);

    // 제대로 된 값이 들어올때까지 루프
    while (true)
    {
        cout << "Enter the score of the element: ";
        getline(cin, scoreInput);

        // input에 문자나 공백이 포함되었는지 확인 함
        bool isValid = true;
        for (char chr : scoreInput)
        {
            if (!isdigit(chr))
            {
                isValid = false;
                break;
            }
        }

        if (!isValid)
        {
            cout << "Invalid Input. Only numbers are allowed. Try again.\n";
            continue;
        }

        // integer형으로 변환
        score = stoi(scoreInput);

        if (score < 0 || score > 100)
        {
            cout << "Number is out of the rannge 0 to 100\n";
            continue;
        }

        newNode.score = score;
        break;
    }

    cin.clear(); // 여기 중요! getline에 이후에 버퍼에 남겨져있는 개행문자 제거
    cout << "Enter the class name: ";
    getline(cin, newNode.className);

    // 새로운 데이터 추가
    pq->insert(newNode);
    cout << "New Element: [" << newNode.name << ", " << newNode.score << ", " << newNode.className << "] has been inserted.\n";
}


// Heap의 최대값 출력
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


// 루트노드 삭제
void deleteData(Heap *pq)
{
    if (pq->getCurrentCount() <= 0)
    {
        cout << "Cannot delete from an empty queue.\n";
        return;
    }
    HeapNode maxNode;
    maxNode = pq->extractMax();

    cout << "Deleted element: [" << maxNode.name << ", " << maxNode.score << ", " << maxNode.className << "]\n";

    cout << endl;
}