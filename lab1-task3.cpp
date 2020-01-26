#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <conio.h>

using namespace std;

int main() {
//    char highPrior[1] = {'!'};
//    char midPrior[4] = {'s', 'c', 't', 'n'};
//    char lowPrior[1] = {'*'};
//    char lowestPrior[2] = {'-', '+'};
    string strIn;
    char strOut[300];
    unsigned cur(0); // указатель на текущий элемент в постфиксной строке
    vector<char> sym; // стек символов
    unsigned s(0); // счетчик элементов в стеке символов
    unsigned open(0); // счетчик откр-их скобок
    unsigned close(0); // счетчик зак-их скобок
    cout << "Enter string: " << endl;
    getline(cin, strIn);
    for (int j = 0; j < strIn.length(); ++j) {
        if (strIn[j] == '(') {
            ++open;
        }
        if (strIn[j] == ')') {
            ++close;
        }
    }
    if (open == close) {
        unsigned i(0);
        while (i < strIn.length()) {
            if (strIn[i] - '0' <= 9 && strIn[i] - '0' >= 0) {
                strOut[cur] = strIn[i];
                ++cur;
            } else {
                if (strIn[i] == '(') {
                    sym.push_back(strIn[i]);
                    ++s;
                    strOut[cur] = ' ';
                    ++cur;
                } else {
                    if (sym.empty()) {
                        sym.push_back(strIn[i]);
                        ++s;
                        if (strIn[i] != '!') {
                            strOut[cur] = ' ';
                            ++cur;
                        }
                    } else {
                        switch (strIn[i]) {
                            case ')': {
                                if (strIn[i + 1] != '^') {
                                    unsigned j(s - 1);
                                    if (open == 1) {
                                        while (sym[j] != '(') {
                                            strOut[cur] = sym[j];
                                            ++cur;
                                            --j;
                                        }
                                        --open;
                                        --close;
                                        for (int k = j - 1; k >= 0; --k) {
                                            strOut[cur] = sym[k];
                                            ++cur;
                                        }
                                        sym.clear();
                                        s = 0;
                                    } else {
                                        while (sym[j] != '(') {
                                            strOut[cur] = sym[j];
                                            ++cur;
                                            --s;
                                            sym.pop_back();
                                            --j;
                                        }
                                        --s;
                                        sym.pop_back();
                                        --open;
                                        --close;
                                    }
                                } else {
                                    unsigned j(s - 1);
                                    while (sym[j] != '(') {
                                        strOut[cur] = sym[j];
                                        ++cur;
                                        --s;
                                        sym.pop_back();
                                        --j;
                                    }
                                    --s;
                                    sym.pop_back();
                                }
                            }
                            break;
                            case '+': {
                                if (s > 1) {
                                    strOut[cur] = ' ';
                                    ++cur;
                                    for (int j = s - 1; j >= 0; --j) {
                                        if (sym[j] != '(') {
                                            if (sym[j] == '*' || sym[j] == '/' || sym[j] == 's' || sym[j] == 'c' ||
                                                sym[j] == 't' ||
                                                sym[j] == 'n' || sym[j] == '!' || sym[j] == '-' || sym[j] == '+' ||
                                                sym[j] == '^') {
                                                strOut[cur] = sym[j];
                                                ++cur;
                                                --s;
                                                sym.pop_back();
                                                strOut[cur] = ' ';
                                                ++cur;
                                            } else {
                                                sym.push_back(strIn[i]);
                                                ++s;
                                            }
                                        } else {
                                            break;
                                        }
                                    }
                                    sym.push_back(strIn[i]);
                                    ++s;
                                } else {
                                    strOut[cur] = ' ';
                                    ++cur;
                                    if (sym[s - 1] == '*' || sym[s - 1] == '/' || sym[s - 1] == 's' ||
                                        sym[s - 1] == 'c' ||
                                        sym[s - 1] == 't' || sym[s - 1] == 'n' || sym[s - 1] == '!' ||
                                        sym[s - 1] == '-' || sym[s - 1] == '+' || sym[s - 1] == '^') {
                                        strOut[cur] = sym[s - 1];
                                        sym[s - 1] = strIn[i];
                                        ++cur;
                                        strOut[cur] = ' ';
                                        ++cur;
                                    } else {
                                        sym.push_back(strIn[i]);
                                        ++s;
                                    }
                                }
                            }
                                break;
                            case '-': {
                                if (s > 1) {
                                    strOut[cur] = ' ';
                                    ++cur;
                                    for (int j = s - 1; j >= 0; --j) {
                                        if (sym[j] != '(') {
                                            if (sym[j] == '*' || sym[j] == '/' || sym[j] == 's' || sym[j] == 'c' ||
                                                sym[j] == 't' ||
                                                sym[j] == 'n' || sym[j] == '!' || sym[j] == '+' || sym[j] == '-' ||
                                                sym[j] == '^') {
                                                strOut[cur] = sym[j];
                                                ++cur;
                                                --s;
                                                sym.pop_back();
                                                strOut[cur] = ' ';
                                                ++cur;
                                            } else {
                                                sym.push_back(strIn[i]);
                                                ++s;
                                            }
                                        } else {
                                            break;
                                        }
                                    }
                                    sym.push_back(strIn[i]);
                                    ++s;
                                } else {
                                    strOut[cur] = ' ';
                                    ++cur;
                                    if (sym[s - 1] == '*' || sym[s - 1] == '/' || sym[s - 1] == 's' ||
                                        sym[s - 1] == 'c' ||
                                        sym[s - 1] == 't' || sym[s - 1] == 'n' || sym[s - 1] == '!' ||
                                        sym[s - 1] == '+' || sym[s - 1] == '-' || sym[s - 1] == '^') {
                                        strOut[cur] = sym[s - 1];
                                        sym[s - 1] = strIn[i];
                                        ++cur;
                                    } else {
                                        sym.push_back(strIn[i]);
                                        ++s;
                                    }
                                }
                            }
                                break;
                            case '*': {
                                strOut[cur] = ' ';
                                ++cur;
                                if (sym[s - 1] == '/' || sym[s - 1] == 's' || sym[s - 1] == 'c' || sym[s - 1] == 't' ||
                                    sym[s - 1] == 'n' ||
                                    sym[s - 1] == '!' || sym[s - 1] == '*' || sym[s - 1] == '^') {
                                    strOut[cur] = sym[s - i];
                                    sym[s - 1] = strIn[i];
                                    ++cur;
                                    strOut[cur] = ' ';
                                    ++cur;
                                } else {
                                    sym.push_back(strIn[i]);
                                    ++s;
                                }
                            }
                                break;
                            case '/': {
                                strOut[cur] = ' ';
                                ++cur;
                                if (sym[s - 1] == '/' || sym[s - 1] == 's' || sym[s - 1] == 'c' || sym[s - 1] == 't' ||
                                    sym[s - 1] == 'n' ||
                                    sym[s - 1] == '!' || sym[s - 1] == '*' || sym[s - 1] == '^') {
                                    strOut[cur] = sym[s - i];
                                    sym[s - 1] = strIn[i];
                                    ++cur;
                                    strOut[cur] = ' ';
                                    ++cur;
                                } else {
                                    sym.push_back(strIn[i]);
                                    ++s;
                                }
                            }
                                break;
                            case 's': {
                                if (sym[s - 1] == '!' || sym[s - 1] == 's' || sym[s - 1] == 'c' || sym[s - 1] == 't' ||
                                    sym[s - 1] == 'n') {
                                    strOut[cur] = sym[s - i];
                                    sym[s - 1] = strIn[i];
                                    ++cur;
                                    strOut[cur] = ' ';
                                    ++cur;
                                } else {
                                    sym.push_back(strIn[i]);
                                    ++s;
                                }
                            }
                                break;
                            case 'c': {
                                if (sym[s - 1] == '!' || sym[s - 1] == 's' || sym[s - 1] == 'c' || sym[s - 1] == 't' ||
                                    sym[s - 1] == 'n') {
                                    strOut[cur] = sym[s - i];
                                    sym[s - 1] = strIn[i];
                                    ++cur;
                                    strOut[cur] = ' ';
                                    ++cur;
                                } else {
                                    sym.push_back(strIn[i]);
                                    ++s;
                                }
                            }
                                break;
                            case 't': {
                                if (sym[s - 1] == '!' || sym[s - 1] == 's' || sym[s - 1] == 'c' || sym[s - 1] == 't' ||
                                    sym[s - 1] == 'n') {
                                    strOut[cur] = sym[s - i];
                                    sym[s - 1] = strIn[i];
                                    ++cur;
                                    strOut[cur] = ' ';
                                    ++cur;
                                } else {
                                    sym.push_back(strIn[i]);
                                    ++s;
                                }
                            }
                                break;
                            case 'n'/*not-tg*/: {
                                if (sym[s - 1] == '!' || sym[s - 1] == 's' || sym[s - 1] == 'c' || sym[s - 1] == 't' ||
                                    sym[s - 1] == 'n') {
                                    strOut[cur] = sym[s - i];
                                    sym[s - 1] = strIn[i];
                                    ++cur;
                                    strOut[cur] = ' ';
                                    ++cur;
                                } else {
                                    sym.push_back(strIn[i]);
                                    ++s;
                                }
                            }
                                break;
                            case '!': {
                                if (sym[s - 1] == '!') {
                                    strOut[cur] = sym[s - i];
                                    sym[s - 1] = strIn[i];
                                    ++cur;
                                    strOut[cur] = ' ';
                                    ++cur;
                                } else {
                                    sym.push_back(strIn[i]);
                                    ++s;
                                }
                            }
                                break;
                            case '^': {
                                if (sym[s - 1] == '^') {
                                    strOut[cur] = sym[s - i];
                                    sym[s - 1] = strIn[i];
                                    ++cur;
                                    strOut[cur] = ' ';
                                    ++cur;
                                } else {
                                    sym.push_back(strIn[i]);
                                    ++s;
                                }
                            }
                                break;
                        }
                    }
                }
            }
            ++i;
        }
        if (s != 0) {
            for (int j = s - 1; j >= 0; --j) {
                strOut[cur] = sym[j];
                ++cur;
                return 0;
            }
        }
        cout << "\nPostfix string is:\n";
        for (unsigned m = 0; m < cur; ++m) {
            cout << strOut[m];
        }
    } else {
        if (open > close)
            cout << "Missing closing brackets";
        else
            cout << "Missing opening brackets";
    }
    return 0;
}
