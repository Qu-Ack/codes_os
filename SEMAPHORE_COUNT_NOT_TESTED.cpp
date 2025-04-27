#include <bits/stdc++.h>
using namespace std;

class Semaphore {
    mutex m;
    condition_variable cv;
    int count;
public:
    Semaphore(int init = 0) : count(init) {}
    void P() {               // wait()
        unique_lock<mutex> lk(m);
        cv.wait(lk, [&]{ return count > 0; });
        --count;
    }
    void V() {               // signal()
        {
            lock_guard<mutex> lk(m);
            ++count;
        }
        cv.notify_one();
    }
};

Semaphore sem(1);
int shared = 0;

void process(int id) {
    sem.P();
    // critical section
    cout << "Process " << id << " entering CS\n";
    shared += id;
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "Process " << id << " leaving CS, shared=" << shared << "\n";
    sem.V();
}

int main() {
    thread t1(process, 1), t2(process, 2);
    t1.join(); t2.join();
    return 0;
}
