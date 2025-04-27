#include <bits/stdc++.h>
using namespace std;

class SpinLock {
    atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        while (flag.test_and_set(memory_order_acquire)) {
            // busy-wait
        }
    }
    void unlock() {
        flag.clear(memory_order_release);
    }
};

int counter = 0;
SpinLock spin;

void worker(int id, int loops) {
    for (int i = 0; i < loops; i++) {
        spin.lock();
        // critical section
        counter++;
        cout << "Thread " << id << " incremented counter to " << counter << "\n";
        spin.unlock();
        // non-critical work
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    const int N = 2, LOOPS = 5;
    vector<thread> threads;
    for (int i = 0; i < N; i++)
        threads.emplace_back(worker, i+1, LOOPS);
    for (auto &t : threads) t.join();
    cout << "Final counter: " << counter << "\n";
    return 0;
}
