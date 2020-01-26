#include <iostream>
#include <conio.h>

using namespace std;

class Stack {
public:
    Stack(unsigned sizeIn);
    ~Stack();
    bool isEmpty();
    void print();
    void resize();
    void push_back(const int &val);
    void pop_back();

private:
    int *ptr;
    unsigned size; // сколько ячеек выделено
    unsigned sizeOG; // сколько ячеек занято
};

Stack::Stack(unsigned sizeIn) {
    size = sizeIn;
    sizeOG = 0;
    ptr = new int[size];
    for (int i = 0; i < size; ++i) {
        ptr[i] = 0;
    }
}

Stack::~Stack() {
    size = 0;
    sizeOG = 0;
    delete[] ptr;
}

bool Stack::isEmpty() {
    if (sizeOG)
        return false;
    else
        return true;
}

void Stack::resize() {
    size = static_cast<unsigned short>(size * 1.6);
    int *buf = new int[size];
    for (int i = 0; i < sizeOG; ++i) {
        buf[i] = ptr[i];
    }
    delete[] ptr;
    ptr = buf;
}

void Stack::push_back(const int &val) {
    if (size > sizeOG) {
        ptr[sizeOG] = val;
        ++sizeOG;
    }
    else {
        resize();
        ptr[sizeOG] = val;
        ++sizeOG;
    }
}

void Stack::pop_back() {
    if (isEmpty()) {
        cout << "Stack is empty\n";
    } else {
        ptr[sizeOG - 1] = 0;
        --sizeOG;
    }
}

void Stack::print() {
    if (isEmpty()) {
        cout << "Stack is empty\n";
    } else {
        for (int i = 0; i < sizeOG; ++i) {
            cout << ptr[i] << " ";
        }
        cout << "\n";
    }
}

int main() {
    unsigned size;
    cout << "Enter stack size:\n";
    cin >> size;
    Stack first(size);
    unsigned char act;
    cout << "Select the action:\n";
    cout << "[1] Add new element\n";
    cout << "[2] Delete element\n";
    cout << "[3] Print data\n";
    cout << "[4] Close program\n";
    cin >> act;
    do {
        switch (act) {
            case '1': {
                unsigned val;
                cout << "Enter value:\n";
                cin >> val;
                first.push_back(val);
                break;
            }
            case '2':
                first.pop_back();
                break;
            case '3':
                first.print();
                break;
            default:
                if (act != 13)
                    cout << "(!) There is no such action\n";
                break;
        }
        cout << "[+]Select the action:\n";
        cin >> act;
    } while (act != '4');
    return 0;
}
