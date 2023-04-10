#include <algorithms.h>

// реализация наивного алгоритма (с использованием простого посимвольного сравнения) [1]
int naive(string& pattern, string& text) {
    int answer = -1;
    int m = pattern.length();
    int n = text.length();
    int flag = 1;
    for (int i = 0; i < n; ++i) {
        flag = 1;
        for (int j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j]) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            answer = i;
        }
    }
    return answer;
}

// реализация алгоритма Кнута-Морриса-Прата (с применением стандартных граней) [2]
int kmp1(string& pattern, string& text) {
    int answer = -1;
    int m = pattern.length();
    int n = text.length();
    int* br = new int[n];
    br[0] = 0;
    int k = 0;
    for (int i = 0; i < m - 1; ++i) {
        // вычисляем элементы массива стандартных граней
        k = br[i];
        while (k > 0 && pattern[i + 1] != pattern[k]) {
            k = br[k - 1];
        }
        if (pattern[i + 1] == pattern[k]) {
            br[i + 1] = k + 1;
        } else {
            br[i + 1] = 0;
        }
    }
    k = 0;
    for (int i = 0; i < n; ++i) {
        while (k > 0 && pattern[k] != text[i]) {
            k = br[k - 1];
        }
        if (pattern[k] == text[i]) {
            k += 1;
        }
        if (k == m) {
            answer = i - m + 1;
            k = br[m];
        }
    }
    delete[] br;
    return answer;
}

// реализация алгоритма Кнута-Морриса-Прата (с применением уточненных граней) [3]
int kmp2(string& pattern, string& text) {
    int answer = -1;
    int m = pattern.length();
    int n = text.length();
    int* br = new int[n];
    int* brs = new int[n];
    br[0] = 0;
    brs[0] = 0;
    int k = 0;
    for (int i = 0; i < m - 1; ++i) {
        // вычисляем элементы массива стандартных граней
        k = br[i];
        while (k > 0 && pattern[i + 1] != pattern[k]) {
            k = br[k - 1];
        }
        if (pattern[i + 1] == pattern[k]) {
            br[i + 1] = k + 1;
        } else {
            br[i + 1] = 0;
        }
        // вычисляем элементы массива уточненных граней
        if (pattern[i + 1] != pattern[br[i]]) {
            brs[i] = br[i];
        } else {
            if (br[i] != 0) {
                brs[i] = brs[br[i] - 1];
            } else {
                brs[i] = 0;
            }
        }
    }
    brs[n - 1] = br[n - 1];
    k = 0;
    for (int i = 0; i < n; ++i) {
        while (k > 0 && pattern[k] != text[i]) {
            k = brs[k - 1];
        }
        if (pattern[k] == text[i]) {
            k += 1;
        }
        if (k == m) {
            answer = i - m + 1;
            k = brs[m - 1];
        }
    }
    delete[] br;
    delete[] brs;
    return answer;
}

// реализация автомата Кнута-Морриса-Прата [4]
