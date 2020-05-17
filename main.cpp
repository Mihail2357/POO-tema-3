#include <iostream>
#include <string>
#include "include/Dictionary.h"

using namespace std;

int main()
{
    Dictionary<int, string> dict;
    dict.Add(23, "salut");
    dict.Add(14, "test1");
    dict.Add(35, "test2");
    cout << dict << "\n";
    return 0;
}
