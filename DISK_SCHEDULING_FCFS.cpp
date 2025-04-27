#include <bits/stdc++.h>
using namespace std;

void FCFS(const vector<int> &req, int head) {
  int seek = 0;
  cout << "FCFS service order: ";
  for (int track : req) {
    cout << track << " ";
    seek += abs(track - head);
    head = track;
  }
  cout << "\nTotal head movement = " << seek << "\n\n";
}
