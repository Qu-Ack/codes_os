#include <iostream>
using namespace std;

struct Process {
    int id, arrival, burst, priority, remaining, completion, waiting, turnaround;
};

void bubbleSortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                swap(p[j], p[j + 1]);
            }
            else{
                if(p[j].arrival==p[j+1].arrival){
                    if(p[j].id>p[j+1].id){
                        swap(p[j], p[j + 1]);
                    }
                }
            }
        }
    }
}

void preemptivePriorityScheduling(Process p[], int n) {
    bubbleSortByArrival(p, n);

    int completed = 0, currentTime = 0, maxPriorityIndex;
    
    while (completed < n) {
        maxPriorityIndex = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= currentTime && p[i].remaining > 0) {
                if (maxPriorityIndex == -1 || p[i].priority > p[maxPriorityIndex].priority) {
                    maxPriorityIndex = i;
                }
            }
        }

        if (maxPriorityIndex == -1) {
            currentTime++;
        } else {
            p[maxPriorityIndex].remaining--;
            currentTime++;

            if (p[maxPriorityIndex].remaining == 0) {
                p[maxPriorityIndex].completion = currentTime;
                p[maxPriorityIndex].turnaround = p[maxPriorityIndex].completion - p[maxPriorityIndex].arrival;
                p[maxPriorityIndex].waiting = p[maxPriorityIndex].turnaround - p[maxPriorityIndex].burst;
                completed++;
            }
        }
    }

    cout << "\nPreemptive Priority Scheduling Results:\n";
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
        p[i].remaining = p[i].burst;
    }

    preemptivePriorityScheduling(p, n);
    return 0;
}