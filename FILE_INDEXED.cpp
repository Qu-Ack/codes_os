#include <bits/stdc++.h>
using namespace std;

struct Record {
    int id;
    char name[20];
};

int main() {
    // build index
    map<int, streampos> index;
    fstream file("records.dat", ios::in | ios::binary);
    Record rec;
    while (file.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        index[rec.id] = file.tellg() - streampos(sizeof(rec));
    }
    file.close();

    // lookup id = 42
    auto it = index.find(42);
    if (it != index.end()) {
        file.open("records.dat", ios::in | ios::binary);
        file.seekg(it->second);
        file.read(reinterpret_cast<char*>(&rec), sizeof(rec));
        cout << rec.id << " " << rec.name << "\n";
        file.close();
    } else {
        cout << "Record not found\n";
    }
    return 0;
}
