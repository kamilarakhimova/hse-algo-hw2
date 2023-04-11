#include <algorithms.h>

// реализация наивного алгоритма (с использованием простого посимвольного сравнения) [1.1]
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

// модификация наивного алгоритма для работы с символом подстановки (?) [1.2]
int naive_mode(string& pattern, string& text) {
    int answer = -1;
    int m = pattern.length();
    int n = text.length();
    int flag = 1;
    for (int i = 0; i < n; ++i) {
        flag = 1;
        for (int j = 0; j < m; ++j) {
            if (pattern[j] != '?' && text[i + j] != pattern[j]) {
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

// реализация алгоритма Кнута-Морриса-Прата (с применением стандартных граней) [2.1]
int kmp1(string& pattern, string& text) {
    int answer = -1;
    int m = pattern.length();
    int n = text.length();
    int* br = new int[m];
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
            ++k;
        }
        if (k == m) {
            answer = i - m + 1;
            k = br[m - 1];
        }
    }
    delete[] br;
    return answer;
}

// модификация алгоритма Кнута-Морриса-Прата (с применением стандартных граней) для работы с символом подстановки (?) [2.2]
int kmp1_mode(string& pattern, string& text) {
    int answer = -1;
    int m = pattern.length();
    int n = text.length();
    int* br = new int[m];
    br[0] = 0;
    int k = 0;
    for (int i = 0; i < m - 1; ++i) {
        // вычисляем элементы массива стандартных граней
        k = br[i];
        while (k > 0 && pattern[i + 1] != pattern[k] && pattern[k] != '?' && pattern[i + 1] != '?') {
            k = br[k - 1];
        }
        if (pattern[i + 1] == pattern[k] || pattern[k] == '?' || pattern[i + 1] == '?') {
            br[i + 1] = k + 1;
        } else {
            br[i + 1] = 0;
        }
    }
    k = 0;
    for (int i = 0; i < n; ++i) {
        while (k > 0 && pattern[k] != '?' && pattern[k] != text[i]) {
            k = br[k - 1];
        }
        if (pattern[k] == text[i] || pattern[k] == '?') {
            ++k;
        }
        if (k == m) {
            answer = i - m + 1;
            k = br[m - 1];
        }
    }
    delete[] br;
    return answer;
}

// реализация алгоритма Кнута-Морриса-Прата (с применением уточненных граней) [3.1]
int kmp2(string& pattern, string& text) {
    int answer = -1;
    int m = pattern.length();
    int n = text.length();
    int* br = new int[m];
    int* brs = new int[m];
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
    brs[m - 1] = br[m - 1];
    k = 0;
    for (int i = 0; i < n; ++i) {
        while (k > 0 && pattern[k] != text[i]) {
            k = brs[k - 1];
        }
        if (pattern[k] == text[i]) {
            ++k;
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

// модификация алгоритма Кнута-Морриса-Прата (с применением уточненных граней) для работы с символом подстановки (?) [3.2]
int kmp2_mode(string& pattern, string& text) {
    int answer = -1;
    int m = pattern.length();
    int n = text.length();
    int* br = new int[m];
    int* brs = new int[m];
    br[0] = 0;
    brs[0] = 0;
    int k = 0;
    for (int i = 0; i < m - 1; ++i) {
        // вычисляем элементы массива стандартных граней
        k = br[i];
        while (k > 0 && pattern[i + 1] != pattern[k] && pattern[k] != '?' && pattern[i + 1] != '?') {
            k = br[k - 1];
        }
        if (pattern[i + 1] == pattern[k] || pattern[k] == '?' || pattern[i + 1] == '?') {
            br[i + 1] = k + 1;
        } else {
            br[i + 1] = 0;
        }
        // вычисляем элементы массива уточненных граней
        if (pattern[i + 1] != pattern[br[i]] && pattern[br[i]] != '?' && pattern[i + 1] != '?') {
            brs[i] = br[i];
        } else {
            if (br[i] != 0) {
                brs[i] = brs[br[i] - 1];
            } else {
                brs[i] = 0;
            }
        }
    }
    brs[m - 1] = br[m - 1];
    k = 0;
    for (int i = 0; i < n; ++i) {
        while (k > 0 && pattern[k] != text[i] && pattern[k] != '?') {
            k = brs[k - 1];
        }
        if (pattern[k] == text[i] || pattern[k] == '?') {
            ++k;
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

// реализация алгоритма Бойера-Мура-Хорспула [4.1]
int bmh(string& pattern, string& text) {
    int answer = -1;
    int m = pattern.length();
    int n = text.length();
    map<char, int> table;
    for (int i = 0; i < 256; ++i) {
        table[(char) i] = m;
    }
    for (int i = 0; i < m - 1; ++i) {
        table[pattern[i]] = m - i - 1;
    }
    table[pattern[m - 1]] = m;
    int k = m - 1;
    int i = m - 1;
    while (i < n - 1) {
        int pos = i;
        k = i;
        while (pos >= 0 && i < n) {
            pos = m - 1;
            k = i;
            while (pos >= 0 && text[k] == pattern[pos]) {
                --pos;
                --k;
            }
            i += table[text[i]];
        }
    }
    if (k <= n - m) {
        answer = k + 1;
    }
    return answer;
}

// модификация алгоритма Бойера-Мура-Хорспула для работы с символом подстановки (?) [4.2]
int bmh_mode(string& pattern, string& text) {
    int answer = -1;
    int m = pattern.length();
    int n = text.length();
    map<char, int> table;
    for (int i = 0; i < 256; ++i) {
        table[(char) i] = m;
    }
    for (int i = 0; i < m - 1; ++i) {
        table[pattern[i]] = m - i - 1;
        if (pattern[i] == '?') {
            table['0'] = m - i - 1;
            table['1'] = m - i - 1;
            table['a'] = m - i - 1;
            table['b'] = m - i - 1;
            table['c'] = m - i - 1;
            table['d'] = m - i - 1;
        }
    }
    table[pattern[m - 1]] = m;
    int k = m - 1;
    int i = m - 1;
    while (i <= n - 1) {
        int pos = i;
        k = i;
        while (pos >= 0 && i < n) {
            pos = m - 1;
            k = i;
            while (pos >= 0 && (text[k] == pattern[pos] || pattern[pos] == '?')) {
                --pos;
                --k;
            }
            i += table[text[i]];
        }
    }
    if (k < n - m) {
        answer = k + 1;
    }
    return answer;
}
