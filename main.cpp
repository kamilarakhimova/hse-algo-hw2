#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
#include <chrono>
#include "algorithms.h"

using std::cin;
using std::cout;
using std::ios_base;
using std::max;
using std::swap;
using std::vector;
using std::string;
using std::to_string;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;

string bin_alphabet = "01";
string dnk_alphabet = "abcd";

// генератор текста в алфавите @alphabet, размера @param size
string generateText(string& alphabet, int size) {
    // устанавливаем начальную точку генерирования последовательности
    srand(time(NULL));
    string result(size, 'a');
    int alph_size = alphabet.length();
    for (int i = 0; i < size; ++i) {
        // теперь получаем рандомные символы в необходимом алфавите
        result[i] = alphabet[rand() % (alph_size)];
    }
    return result;
}

// функция, возвращающая время работы заданного алгоритма
int64_t algoTime(string& pattern, string& text, int choice) {
    int algo_answer;
    auto start = high_resolution_clock::now();
    switch (choice) {
        case 1:
            algo_answer = naive_mode(pattern, text);
            break;
        case 2:
            algo_answer = kmp1_mode(pattern, text);
            break;
        case 3:
            algo_answer = kmp2_mode(pattern, text);
            break;
        case 4:
            algo_answer = bmh_mode(pattern, text);
            break;
        default:
            break;
    }
    auto elapsed = high_resolution_clock::now() - start;
    int64_t elapsed_ms = duration_cast<nanoseconds>(elapsed).count();
    return elapsed_ms;
}

// функция, возвращающая усреднённое время работы алгоритма с 10 испытаний
int64_t midTime(string& pattern, string& text, int choice) {
    int64_t mtime = algoTime(pattern, text, choice) + algoTime(pattern, text, choice);
    mtime += algoTime(pattern, text, choice) + algoTime(pattern, text, choice);
    mtime += algoTime(pattern, text, choice) + algoTime(pattern, text, choice);
    mtime += algoTime(pattern, text, choice) + algoTime(pattern, text, choice);
    mtime += algoTime(pattern, text, choice) + algoTime(pattern, text, choice);
    mtime /= 10;
    return mtime;
}

// функция, создающая необходимые таблицы ("csv")
void createTables(string& text, int size, const string& name) {
    std::ofstream myfile;
    string folder = "TablesForGraphs/";
    srand(time(NULL));
    int pos = rand() % (size);
    int max_wildcards = 5;
    int max_algos = 5;
    for (int j = 0; j < max_wildcards; ++j) {
        myfile.open(folder + name + to_string(j) + ".csv");
        for (int i = 100; i <= 3000; i += 100) {
            string pattern = text.substr(pos, i);
            if (j > 0) {
                int pos_wc = rand() % j;
                while (pattern[pos_wc] == '?') {
                    pos_wc = rand() % j;
                }
                pattern[pos_wc] = '?';
            }
            myfile << i;
            for (int k = 1; k < max_algos; ++k) {
                myfile << ';' << midTime(pattern, text, k);
            }
            myfile << '\n';
        }
        myfile.close();
    }
}

int main() {
    cout << "The program starts the work.\n";
    const int size1 = 10000;
    const int size2 = 100000;
    string text_bin_first = generateText(bin_alphabet, size1);
    createTables(text_bin_first, size1, "Bin 10000 ");
    cout << "Processed 25%...\n";
    string text_bin_second = generateText(bin_alphabet, size2);
    createTables(text_bin_second, size2, "Bin 100000 ");
    cout << "Processed 50%...\n";
    string text_dnk_first = generateText(dnk_alphabet, size1);
    createTables(text_dnk_first, size1, "Dnk 10000 ");
    cout << "Processed 75%...\n";
    string text_dnk_second = generateText(dnk_alphabet, size2);
    createTables(text_dnk_second, size2, "Dnk 100000 ");
    cout << "Processed 100%!\n";
    cout << "Well done. The program ends its work.\n";
    return 0;
}
