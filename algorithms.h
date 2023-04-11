#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::ios_base;
using std::string;

int naive(string& pattern, string& text);
int naive_mode(string& pattern, string& text);
int kmp1(string& pattern, string& text);
int kmp1_mode(string& pattern, string& text);
int kmp2(string& pattern, string& text);
int kmp2_mode(string& pattern, string& text);
int bmh(string& pattern, string& text);
int bmh_mode(string& pattern, string& text);
