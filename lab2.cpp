#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int getMinrun(int N)
{
    int r = 0;
    while (N >= 64) {
        r = r || (N & 1);
        N = N >> 1;
    }
    return N + r;
}

void readArr(vector<int> &arr, int N) {
    int val;
    for (int i = 0; i < N; ++i) {
         cin >> val;
        arr.push_back(val);
    }
}

void insertionSort (vector<int> &start, int i, vector<int> &inArr, int count) {
    for (int j = start[count - 1] + 1; j < i; ++j) {
        for (int k = j; k > start[count - 1]; --k) {
            if (inArr[k - 1] > inArr[k]) { // ошибка сегментации
                swap(inArr[k - 1], inArr[k]);
            }
        }
    }
}

int getSortRuns(vector<int> &start, vector<int> &len, vector<int> &inArr, int N, short minrun) {
    int count(1);
    start.push_back(0);
    len.push_back(minrun);
    insertionSort(start, minrun, inArr, count);
    int i(minrun);
    while (i < N) {
        ++count;
        start.push_back(i);
        if (N - start[count - 1] >= minrun) {
            len.push_back(minrun);
            i += minrun;
            insertionSort(start, i, inArr, count);
        } else {
            len.push_back(N - start[count - 1]);
            i += minrun;
            insertionSort(start, N, inArr, count);
        }
    }
    return count;
}

void mergeSort (vector<int> &start, vector<int> &len, vector<int> &bufStart,
vector<int> &bufLen, int &i, int &curFirst, int &curSecond, int &count, vector<int> &inArr, int &cur) {
    curFirst = start[i];
    curSecond = start[i + 1];
    int buf[len[i] + len[i + 1]];
    for (int j = 0; j < len[i] + len[i + 1]; ++j) { // сортируем два run'a и записываем в буфер
        if (curFirst != len[i] + start[i] && curSecond != len[i + 1] + start[i + 1]) { // пока не закончится один из run'ов
            if (inArr[curFirst] < inArr[curSecond]) {
                buf[j] = inArr[curFirst];
                ++curFirst;
            } else {
                buf[j] = inArr[curSecond];
                ++curSecond;
            }
        } else { // когда закончился один из run'ов - вывожу все оставшееся из другого
            if (curFirst == len[i] + start[i]) {
                while (curSecond != len[i + 1] + start[i + 1]) {
                    buf[j] = inArr[curSecond];
                    ++curSecond;
                }
            } else {
                while (curFirst != len[i] + start[i]) {
                    buf[j] = inArr[curFirst];
                    ++curFirst;
                }
            }
        }
    }
    for (int j = 0; j < len[i] + len[i + 1]; ++j) { // ввожу отсортированные данные из буфера в inArr
        inArr[cur] = buf[j];
        ++cur; // на выходе из этого цикла будет опережать слитый run на одну позицию - т.е. уже указывать на начало следующего run'а
    }
    bufStart.push_back(start[i]); // записываю старт и длину нового подмассива в буфер чтобы потом перезаписать основной массив
    bufLen.push_back(len[i] + len[i + 1]);
}

void resetStartAndLen (vector<int> &start, vector<int> &len, vector<int> &bufStart, vector<int> &bufLen, int count) {
    start.clear(); // дальше я перезаписываю массивы старт и длина с учетом новых данных(run'ов стало меньше => ячеек стало меньше и данные изм-сь)
    len.clear();
    for (int k = 0; k < count; ++k) {
        start.push_back(bufStart[k]);
        len.push_back(bufLen[k]);
    }
    bufStart.clear();
    bufLen.clear();
}

void mergeRuns (vector<int> &start, vector<int> &len, vector<int> &inArr, int &count) {
    if (count % 2 == 0) {
        while (count != 1) {
            int i(0); // указатель на первый run из двух сливаемых в данную секунду
            int cur(0); // указатель на текущую позицию в inArr, всегда равно началу первого из двух сливаемых run'ов
            int curFirst; // указатели на индексы текущих элементов
            int curSecond;
            vector<int> bufStart;
            vector<int> bufLen;
            while (i < count - 1) { // сливаем по 2 run'а пока не доберемся до конца
                mergeSort(start, len, bufStart, bufLen, i, curFirst, curSecond, count, inArr, cur);
                i += 2;
            }
            count = count / 2;
            resetStartAndLen(start, len, bufStart, bufLen, count);
        }
    } else {
        while (count != 1) {
            int i(0); // указатель на первый run из двух сливаемых в данную секунду
            int cur(0); // указатель на текущую позицию в inArr, всегда равно началу первого из двух сливаемых run'ов
            int curFirst; // указатели на
            int curSecond; // индексы текущих элементов
            vector<int> bufStart;
            vector<int> bufLen;
            while (i < count - 4) { // сливаем по 2 run'а пока не доберемся до 3 последних эл-тов
                mergeSort(start, len, bufStart, bufLen, i, curFirst, curSecond, count, inArr, cur);
                i += 2;
            }
            bufStart.push_back(start[i]); // записываю данные пред-предпоследнего подмассива в буфер
            bufLen.push_back(len[i]);
//            ++i;
            mergeSort(start, len, bufStart, bufLen, i, curFirst, curSecond, count, inArr, cur); // сливаем последний и предпоследний подмассивы
            --i;
            resetStartAndLen(start, len, bufStart, bufLen, count); // записываем данные из буфера в основной массив
            for (int j = 0; j < count - 2; ++j) { // записываю в буфер данные о всех подмассивах кроме последних двух
                bufStart.push_back(start[i]);
                bufLen.push_back(len[i]);
            }
            mergeSort(start, len, bufStart, bufLen, i, curFirst, curSecond, count, inArr, cur); // сливаем последний и предпосл-ий(по новым данным) подмассивы
            resetStartAndLen(start, len, bufStart, bufLen, count);
            count = (count - 1) / 2;
        }
    }
}

void printArr(vector<int> &inArr, vector<int> &len, int N) {
    cout << "Sort array:\n";
    for (int i = 0; i < N; ++i) {
        cout << inArr[i] << " ";
    }
}

int main() {
//    vector<int> inArr = {12, 32, 32, 6554, 64949, 493, 3490, 580, 27, 8, 8430, 9430, 4, 53, 3455, 1, 424, 53, 4343, 665, 564, // 21
//                         5786, 43, 87, 930, 942, 6906, 843, 430, 8, 94, 5, 12, 443, 54, 7654, 286, 653, 4678, 854, 24, 6345, // 21
//                         902, 8340, 8482, 4573, 895, 8, 83, 50, 9539, 828483, 85, 85640, 9237, 42, 2256, 522, 223, 66, 865, 43, 124, 741, // 22
//                         1840, 589, 930, 9033, 457, 30, 10, 5999, 73284, 845838, 99, 9320, 57, 480, 93920, 1, 28, 684, 9205, 9560, 24, 5643, 2, 86, 42}; // 25
    vector<int> inArr;
    vector<int> start;
    vector<int> len;
    int act;
    int N;
    cout << "Do you want enter random numbers?" << "\n";
    cout << "[1] Yes" << "\n" << "[2] No" << "\n";
    cin >> act;
    switch (act) {
        case 1: {
            cout << "Enter size of array:\n";
            cin >> N;
            srand(time(nullptr));
            for (int i = 0; i < N; ++i) {
                inArr.push_back(rand() % 200);
            }
            short minrun = getMinrun(N);
            cout << "Minrun: " << minrun << "\n";
            int count = getSortRuns(start, len, inArr, N, minrun);
            mergeRuns(start, len, inArr, count);
            printArr(inArr, len, N);
        }
            break;
        case 2: {
            cout << "Enter size of array:\n";
            cin >> N;
            cout << "Enter values:\n";
            readArr(inArr, N);
            short minrun = getMinrun(N);
            cout << "Minrun: " << minrun << "\n";
            int count = getSortRuns(start, len, inArr, N, minrun);
            mergeRuns(start, len, inArr, count);
            printArr(inArr, len, N);
        }
            break;
        default:
            cout << "(!)Wrong number" << "\n";
            break;
    }
    return 0;
}
