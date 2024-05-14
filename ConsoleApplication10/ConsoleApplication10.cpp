#include <iostream>
#include <string>
#include <Chrono>

using namespace std;

struct List
{
    int data;
    List* head;
    List* tail;
};

void deleteFullList(List* list)
{
    List* next = list;
    while (list)
    {
        next = list->tail;
        delete list;
        list = next;
    }
}

void showData(List* beg)
{
    List* p = beg;
    while (p->tail)
    {
        cout << p->data << ' ';
        p = p->tail;
    }
    cout << p->data << ' ';
    cout << '\n';
}

int lengthOfList(List* list)
{
    int length = 0;
    List* curr = list;
    while (curr)
    {
        length++;
        curr = curr->tail;
    }
    return length;
}

void insert(List*& list, int pos, int value)
{
    auto clockStart = chrono::high_resolution_clock::now();
    List* curr = list;
    List* addElem = new List;
    addElem->data = value;
    if (pos == 1)
    {
        addElem->head = 0;
        addElem->tail = list;
        list->head = addElem;
        list = addElem;
    }
    else
    {
        for (int i = 1; i < pos - 1; i++)
        {
            curr = curr->tail;
        }
        if (curr->tail == 0)
        {
            curr->tail = addElem;
            addElem->tail = 0;
            addElem->head = curr->head->tail;
        }
        else
        {
            List* next = curr->tail;
            addElem->tail = next;
            addElem->head = curr;
            next->head = addElem;
            curr->tail = addElem;
        }
    }
    auto clockEnd = chrono::high_resolution_clock::now();
    cout << "Время list: ";
    cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
}

void deleteElem(List*& list, short option, int a)
{
    auto clockStart = chrono::high_resolution_clock::now();
    if (option)
    {
        List* curr = list;
        while (curr->data != a)
        {
            curr = curr->tail;
        }
        if (!curr->head)
        {
            list = curr->tail->tail->head;
            delete curr;
            list->head = 0;
        }
        else
        {
            if (!curr->tail)
            {
                curr->head->tail = 0;
                delete curr;
            }
            else
            {
                List* next = curr->tail;
                List* prev = curr->head;
                next->head = curr->head;
                prev->tail = curr->tail;
                delete curr;
            }
        }
    }
    else
    {
        List* curr = list;
        if (a == 1)
        {
            list = curr->tail->tail->head;
            delete curr;
            list->head = 0;
        }
        else
        {
            for (int i = 1; i < a; i++)
            {
                curr = curr->tail;
            }
            if (!curr->tail)
            {
                curr->head->tail = 0;
                delete curr;
            }
            else
            {
                List* next = curr->tail;
                List* prev = curr->head;
                next->head = curr->head;
                prev->tail = curr->tail;
                delete curr;
            }
        }
    }

    auto clockEnd = chrono::high_resolution_clock::now();
    cout << "Время list: ";
    cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
}

void swapElem(List* list, int pos1, int pos2)
{
    auto clockStart = chrono::high_resolution_clock::now();
    List* curr = list;
    List* currA = 0;
    List* currB = 0;
    for (int i = 1; i < max(pos1, pos2); i++)
    {
        if (i == min(pos1, pos2))
        {
            currA = curr;
        }
        curr = curr->tail;
    }
    currB = curr;
    if (pos1 == pos2)
    {
        currA = currB;
    }
    int t;
    t = currA->data;
    currA->data = currB->data;
    currB->data = t;
    auto clockEnd = chrono::high_resolution_clock::now();
    cout << "Время list: ";
    cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
}

void findElem(List* list, short option, int a)
{
    auto clockStart = chrono::high_resolution_clock::now();
    if (option)
    {
        int num = 0;
        bool isFind = false;
        List* curr = list;
        while (curr->tail)
        {
            if (curr->data == a)
            {
                isFind = true;
                cout << a << " - значение элемента с номером " << num + 1 << '\n';
                break;
            }
            else
            {
                num++;
                curr = curr->tail;
            }
        }
        if (curr->data == a)
        {
            isFind = true;
            cout << a << " - значение элемента с номером " << num + 1 << '\n';
        }
        if (!isFind)
        {
            cout << "такого значения нет в списке\n";
        }
    }
    else
    {
        List* curr = list;
        for (int i = 1; i < a; i++)
        {
            curr = curr->tail;
        }
        cout << "Элемент с номером " << a << ": " << curr->data << '\n';
    }
    auto clockEnd = chrono::high_resolution_clock::now();
    cout << "Время list: ";
    cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
}

void workList(List* beg, int listLength)
{
    cout << '\n';
    List* list = beg;

    bool isEnd = false;
    while (!isEnd)
    {
        cout << "Двусвязный список:\n";
        showData(list);
        cout << "\nВыберите действие:\n[1] Вставка элемента\n[2] Удаление элемента\n[3] Обмен\n[4] Получение элемента\n[0] Выход\n\n";
        short choise;
        cin >> choise;
        switch (choise)
        {
        case (1):
            system("cls");
            int value, pos;
            cout << "Введите номер позиции, куда Вы хотите вставить элемент: ";
            cin >> pos;
            cout << "Введите значение элемента: ";
            cin >> value;
            insert(list, pos, value);
            system("cls");
            break;
        case (2):
            system("cls");
            short option;
            cout << "[1] Удалить по значению\n[0] Удалить по индексу\n";
            cin >> option;
            int a;
            if (option)
            {
                cout << "Введите значение, которое Вы хотите удалить: ";
                cin >> a;
            }
            else
            {
                cout << "Введите номер элемента, который Вы хотите удалить: ";
                cin >> a;
            }
            if (lengthOfList(list) <= 2)
            {
                cout << "В списке слишком мало элементов\n";
            }
            else
            {
                deleteElem(list, option, a);
            }
            system("cls");
            break;
        case (3):
            system("cls");
            int pos1, pos2;
            cout << "Введите номера элементов, которые хотите поменять местами: ";
            cin >> pos1;
            cin >> pos2;
            swapElem(list, pos1, pos2);
            system("cls");
            break;
        case (4):
            system("cls");
            short option1;
            cout << "[1] Найти по значению\n[0] Найти по индексу\n";
            cin >> option1;
            int a1;
            if (option1)
            {
                cout << "Введите значение, которое Вы хотите найти: ";
                cin >> a1;
            }
            else
            {
                cout << "Введите номер элемента, который Вы хотите найти: ";
                cin >> a1;
            }
            findElem(list, option1, a1);
            system("pause");
            system("cls");
            break;
        default:
            isEnd = true;
            break;
        }
    }
    deleteFullList(list);
}

void randList()
{
    auto clockStart = chrono::high_resolution_clock::now();
    int listLength;
    srand(time(NULL));
    cout << "Введите длину списка: ";
    cin >> listLength;
    List* curr = 0;
    List* next = 0;
    for (int i = 1; i <= listLength; i++)
    {
        curr = new List;
        curr->data = rand() % 100;
        curr->tail = next;
        if (next)
        {
            next->head = curr;
        }
        next = curr;
    }
    curr->head = 0;
    List* beg = curr;
    auto clockEnd = chrono::high_resolution_clock::now();
    cout << "Время list: ";
    cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
    workList(beg, listLength);

}

void fillList()
{
    auto clockStart = chrono::high_resolution_clock::now();
    bool isEnd = false;
    List* curr = 0;
    List* next = 0;
    List* beg = 0;
    int listLength = 0;
    cout << "Введите число или ""end"", если хотите завершить ввод\n";
    while (!isEnd)
    {
        string a;
        cin >> a;
        if (a == "end")
        {
            isEnd = true;
        }
        else
        {
            curr = new List;
            if (!listLength)
            {
                beg = curr;
            }
            listLength++;
            curr->data = stoi(a);
            curr->head = next;
            if (next)
            {
                next->tail = curr;
            }
            next = curr;
        }
    }
    curr->tail = 0;
    auto clockEnd = chrono::high_resolution_clock::now();
    cout << "Время list: ";
    cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
    workList(beg, listLength);
}

int main() {
    setlocale(LC_ALL, "RU");
    int choise;
    cout << "Команды:\n"
        "[1]Создание массива(автоматическое заполнение)\n"
        "[2]Создание массива(ручное заполнение)\n"
        "[0]Выход\n\n"
        "Выбор: ";
    cin >> choise;
    switch (choise) {
    case(1):
        system("cls");
        randList();
        break;
    case(2):
        system("cls");
        fillList();
        break;
    }
    return 0;
}


