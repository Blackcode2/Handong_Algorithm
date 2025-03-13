// https://blog.naver.com/cksdn788/220794432210 -> transform
// https://cplusplus.com/reference/set/set/ -> set

#include <iostream>
#include <algorithm>
using namespace std;

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

int main()
{
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
            cout << "i\n";
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