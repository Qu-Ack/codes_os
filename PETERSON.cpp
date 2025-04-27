#include <bits/stdc++.h>
using namespace std;

atomic<bool> flag[2];
atomic<int> turn;
int counter = 0;

void peterson(int self, int other, int loops) {
    for (int i = 0; i < loops; ++i) {
        flag[self] = true;
        turn = other;
        while (flag[other] && turn == other) {
            // busy-wait
        }
        // critical section
        counter++;
        cout << "Thread " << self << " -> counter = " << counter << "\n";
        flag[self] = false;
        // remainder section
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    const int LOOPS = 5;
    flag[0] = flag[1] = false;
    turn = 0;
    thread t0(peterson, 0, 1, LOOPS);
    thread t1(peterson, 1, 0, LOOPS);
    t0.join(); t1.join();
    cout << "Final counter: " << counter << "\n";
    return 0;
}
