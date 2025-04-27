#include <bits/stdc++.h>
using namespace std;

void SCAN(vector<int> req, int head, int disk_size, string dir) {
  vector<int> left, right;
  for (int r : req) {
    if (r < head)
      left.push_back(r);
    else
      right.push_back(r);
  }

  left.push_back(0);
  right.push_back(disk_size - 1);
  sort(left.begin(), left.end());
  sort(right.begin(), right.end());

  int seek = 0;
  cout << "SCAN service order: ";
  if (dir == "left") {
    for (int i = left.size() - 1; i >= 0; i--) {
      cout << left[i] << " ";
      seek += abs(head - left[i]);
      head = left[i];
    }
    // then right
    for (int r : right) {
      cout << r << " ";
      seek += abs(head - r);
      head = r;
    }
  } else {
    // go right
    for (int r : right) {
      cout << r << " ";
      seek += abs(head - r);
      head = r;
    }
    // then left
    for (int i = left.size() - 1; i >= 0; i--) {
      cout << left[i] << " ";
      seek += abs(head - left[i]);
      head = left[i];
    }
  }
  cout << "\nTotal head movement = " << seek << "\n\n";
}
