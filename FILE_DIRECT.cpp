#include <bits/stdc++.h>
using namespace std;

struct Record { 
    int id; 
    char name[20]; 
};

int main() {
    fstream file("records.dat", ios::in | ios::out | ios::binary);
    Record rec;
    // read record #5 (0-based)
    file.seekg(5 * sizeof(Record), ios::beg);
    file.read(reinterpret_cast<char*>(&rec), sizeof(rec));
    cout << rec.id << " " << rec.name << "\n";

    // modify and write back
    rec.id = 99;
    strcpy(rec.name, "Updated");
    file.seekp(5 * sizeof(Record), ios::beg);
    file.write(reinterpret_cast<char*>(&rec), sizeof(rec));
    file.close();
    return 0;
}
