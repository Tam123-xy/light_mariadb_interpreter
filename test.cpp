#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == string::npos) return ""; // all spaces
    return str.substr(first, last - first + 1);
}

int main() {
    string a = " name ";
    string b = "word  ";
    string c = "xin yi";

    a = trim(a);
    b = trim(b);
    c = trim(c);

    cout << "a = \"" << a << "\"" << endl;
    cout << "b = \"" << b << "\"" << endl;
    cout << "c = \"" << c << "\"" << endl;

    return 0;
}
