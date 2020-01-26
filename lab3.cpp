#include <iostream>

using namespace std;

struct node // структура узла
{
    int key;
    unsigned char height;
    node* left;
    node* right;

    node(int k) { // конструктор
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

unsigned char height(node* p)
{
    if (p)
        return p->height;
    else
        return 0;
}

int bfactor(node* p)
{
    return height(p->right)-height(p->left);
}

void fixHeight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    if (hl > hr)
        p->height = hl + 1;
    else
        p->height = hr + 1;
}

node* rotateRight(node* p) // правый поворот вокруг p
{
    node* buf = p->left;
    p->left = buf->right;
    buf->right = p;
    fixHeight(p);
    fixHeight(buf);
    return buf;
}

node* rotateLeft(node* q) // левый поворот вокруг q
{
    node* buf = q->right;
    q->right = buf->left;
    buf->left = q;
    fixHeight(q);
    fixHeight(buf);
    return buf;
}

node* balance(node* p) // балансировка узла p
{
    fixHeight(p);
    if (bfactor(p)==2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (bfactor(p)==-2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
    if (!p)
        return new node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

node* findMin(node* p) // поиск узла с минимальным ключом в дереве p
{
    if (p->left)
        findMin(p->left);
    else
        return p;
}

node* removeMin(node* p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == nullptr)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
    if (!p) return nullptr;
    if (k < p->key)
        p->left = remove(p->left,k);
    else
        if (k > p->key)
            p->right = remove(p->right,k);
        else {
            node* q = p->left;
            node* r = p->right;
            delete p;
            if (!r)
                return q;
            node* min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            return balance(min);
        }
    return balance(p);
}

node* find(node* p, int k) // поиск ключа k в дереве p
{
    node* res = nullptr;
    if (p) {
        if (k == p->key)
            return p;
        if (k < p->key)
            res = find(p->left, k);
        if (k > p->key)
            res = find(p->right, k);
    }
    return res;
}

void print_Tree(node* p, short height) // печать дерева p с отступом слева на height
{
    if(p) {
        print_Tree(p->right,height + 1);
        cout << "| ";
        for(int i = 1; i < height; i++) {
            cout << "---";
        }
        cout << p->key << endl;
        print_Tree(p->left,height + 1);
    }
}

int main() {
    node* Tree;
    int val;
    int act;
    cout << "Enter first key:\n";
    cin >> val;
    Tree = new node(val);
    cout << "Choose action:\n";
    cout << "[0]Close program\n";
    cout << "[1]Insert node\n";
    cout << "[2]Delete node\n";
    cout << "[3]Find node\n";
    cout << "[4]Print node\n";
    cin >> act;
    while (act < 1 || act > 4) {
        cout << "(!)Enter right number\n";
        cin >> act;
    }
    while (act) {
        switch (act) {
            case 1: {
                cout << "Enter key: ";
                cin >> val;
                Tree = insert(Tree, val);
                break;
            }
            case 2: {
                cout << "Enter key: ";
                cin >> val;
                Tree = remove(Tree, val);
                break;
            }
            case 3: {
                cout << "Enter key: ";
                cin >> val;
                if (find(Tree, val))
                    cout << "Value was found\n";
                else
                    cout << "There is no such value\n";
                break;
            }
            case 4: {
                print_Tree(Tree, 1);
                break;
            }
        }
        cout << "Choose action:\n";
        cin >> act;
    }
    return 0;
}