#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int pid;
    int total_time;
    int io_start, compute_time, io_end;
    int remaining_compute;
    bool completed;
};

void bubbleSort(vector<Process> &readyQueue) {
    int n = readyQueue.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (readyQueue[j].remaining_compute > readyQueue[j + 1].remaining_compute) {
                swap(readyQueue[j], readyQueue[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter total execution time for Process " << i + 1 << ": ";
        cin >> processes[i].total_time;
        processes[i].pid = i + 1;
        processes[i].completed = false;
        processes[i].io_start = processes[i].total_time * 0.2;
        processes[i].compute_time = processes[i].total_time * 0.7;
        processes[i].io_end = processes[i].total_time * 0.1;
        processes[i].remaining_compute = processes[i].compute_time;
    }

    int time = 0, idle_time = 0;
    vector<Process> readyQueue;
    vector<Process> ioQueue = processes;
    bool cpu_idle = true;

    while (true) {
        bool allCompleted = true;
        for (auto it = ioQueue.begin(); it != ioQueue.end();) {
            if (it->io_start <= time && !it->completed) {
                readyQueue.push_back(*it);
                it = ioQueue.erase(it);
            } else {
                ++it;
            }
        }

        bubbleSort(readyQueue);

        if (!readyQueue.empty()) {
            if (cpu_idle) {
                cout << "CPU Idle from t = " << time - idle_time << " to " << time << endl;
                cpu_idle = false;
            }

            Process &current = readyQueue.front();
            int exec_time = current.remaining_compute;
            time += exec_time;
            current.remaining_compute = 0;

            // Move process to final I/O phase
            current.io_start = time;
            ioQueue.push_back(current);
            readyQueue.erase(readyQueue.begin());
            current.completed = true;
        } else {
            if (!cpu_idle) {
                cout << "CPU Idle from t = " << time;
                cpu_idle = true;
            }
            idle_time++;
            time++;
        }

        for (const auto &p : processes) {
            if (!p.completed) {
                allCompleted = false;
                break;
            }
        }
        if (allCompleted) break;
    }

    if (cpu_idle) {
        cout << " to " << time << endl;
    }

    cout << "Total execution time: " << time << " units" << endl;
    cout << "CPU Idle Time: " << idle_time << " units" << endl;
    cout << "CPU Idle Percentage: " << (float(idle_time) / time) * 100 << "%" << endl;

    return 0;
}