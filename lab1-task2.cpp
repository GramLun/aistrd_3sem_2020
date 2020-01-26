#include <iostream>

using namespace std;

using T = int;

struct list {
    T val;
    list *next,
            *prev;
};

list *create(unsigned short size) {
    if (size > 0) {
        list *cur = nullptr,
                *next = nullptr;
        for (int i = 0; i < size; ++i) {
            cur = new list;
            cur->next = next;
            cout << "Enter value:" << endl;
            cin >> cur->val;
            if (next) {
                next->prev = cur;
            }
            next = cur;
        }
        cur->prev = nullptr;
        return cur;
    } else {
        cout << "Enter size larger than 0" << endl;
    }
}

list *addBeg(list *&cur, unsigned short &size) {
    list *item = new list;
    cur->prev = item;
    item->prev = nullptr;
    item->next = cur;
    cout << "Enter value:" << endl;
    cin >> item->val;
    cur = item;
    size++;
    return item;
}

list *addEnd(list *&cur, unsigned short &size) {
    list *item = new list;
    list *buf;
    buf = cur->next;
    for (int i = 0; i < size - 2; ++i) {
        buf = buf->next;
    }
    item->prev = buf;
    item->next = nullptr;
    cout << "Enter value:" << endl;
    cin >> item->val;
    buf->next = item;
    size++;
    return item;
}

bool delBeg(list *&cur, unsigned short &size) {
    if (cur != nullptr) {
        if (size > 1) {
            list *buf;
            buf = cur->next;
            delete cur;
            buf->prev = nullptr;
            cur = buf;
            size--;
            return true;
        }
        else {
            delete cur;
            cout << "You have completely delete the list" << endl;
            return false;
        }
    } else {
        cout << "There is no more items" << endl;
        return false;
    }
}

bool delEnd(list *&cur, unsigned short &size) {
    if (cur != nullptr) {
        if (size > 1) {
            list *buf;
            list *buf2;
            buf = cur->next;
            for (int i = 0; i < size - 2; ++i) {
                buf = buf->next;
            }
            buf2 = buf->prev;
            delete buf;
            buf2->next = nullptr;
            size--;
            return true;
        }
        else {
            delete cur;
            cout << "You have completely delete the list" << endl;
            return false;
        }
    } else {
        cout << "There is no more items" << endl;
        return false;
    }
}

void printAll(list *&cur) {
    cout << "Your data: " << endl;
    list *buf;
    buf = cur;
    while (buf) {
        cout << buf->val << endl;
        buf = buf->next;
    }
}

bool isEmpty(list *&cur) {

}

int main() {
    char select;
    unsigned short size(0);
    unsigned short act;
    bool keep = true;
    bool ok = true;
    list *cur = nullptr;
    cout << "Do you want to create list?" << endl;
    cout << "-------(Y)--or--(N)--------" << endl;
    cin >> select;
    if (select == 'y' || select == 'Y') {
        cout << "Enter size of list: " << endl;
        while (!size) {
            cin >> size;
            cur = create(size);
        }
    } else {
        return 0;
    }
    cout << "Select act: " << endl;
    cout << "1. Add new item to begin" << endl;
    cout << "2. Add new item to end" << endl;
    cout << "3. Remove item from begin" << endl;
    cout << "4. Remove item from end" << endl;
    cout << "5. Print all data" << endl;
    cin >> act;
    while (ok) {
        switch (act) {
            case 1:
                addBeg(cur, size);
                break;
            case 2:
                addEnd(cur, size);
                break;
            case 3:
                keep = delBeg(cur, size);
                if (!keep)
                    return 0;
                break;
            case 4:
                keep = delEnd(cur, size);
                if (!keep)
                    return 0;
                break;
            case 5:
                printAll(cur);
                break;
            default:
                cout << "Enter the right action number:" << endl;
        }
        cout << "Do you want to continue working?" << endl;
        cout << "----------(Y)--or--(N)----------" << endl;
        cin >> select;
        if (select == 'y' || select == 'Y') {
            cout << "Select act: " << endl;
            cin >> act;
        } else
            ok = false;
    }
    return 0;
}