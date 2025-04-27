#include <iostream>
using namespace std;

struct Process {
    int id, arrival, burst, priority, completion, waiting, turnaround;
};

void bubbleSortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                swap(p[j], p[j + 1]);
            }
        }
    }
}

void nonPreemptivePriorityScheduling(Process p[], int n) {
    bubbleSortByArrival(p, n);

    int completed = 0, currentTime = 0;

    while (completed < n) {
        int highestPriorityIndex = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currentTime && p[i].completion == 0) {
                if (highestPriorityIndex == -1 || p[i].priority > p[highestPriorityIndex].priority) {
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++;
        } else {
            currentTime += p[highestPriorityIndex].burst;
            p[highestPriorityIndex].completion = currentTime;
            p[highestPriorityIndex].turnaround = p[highestPriorityIndex].completion - p[highestPriorityIndex].arrival;
            p[highestPriorityIndex].waiting = p[highestPriorityIndex].turnaround - p[highestPriorityIndex].burst;
            completed++;
        }
    }

    cout << "\nNon-Preemptive Priority Scheduling Results:\n";
    cout << "PID\tArrival\tBurst\tPriority\tCompletion\tTAT\tWaiting\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].arrival << "\t" << p[i].burst << "\t" << p[i].priority << "\t\t"
             << p[i].completion << "\t\t" << p[i].turnaround << "\t" << p[i].waiting << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    cout << "Enter Process ID, Arrival Time, Burst Time, and Priority:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].id >> p[i].arrival >> p[i].burst >> p[i].priority;
        p[i].completion = 0;
    }

    nonPreemptivePriorityScheduling(p, n);
    return 0;
}
