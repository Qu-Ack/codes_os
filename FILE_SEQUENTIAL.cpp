#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("data.txt");
    string line;
    while (getline(fin, line)) {
        cout << line << "\n";
    }
    fin.close();
    return 0;
}
