#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;         
    int arrival;    
    int burst;     
    int completion;
    int waiting;    
    int turnaround; 
    int remaining_burst_time;
    int response_time;
};

bool sameArrival(Process p1, Process p2) {
    return p1.arrival < p2.arrival;
}

bool compareBurst(Process p1, Process p2) {
    if (p1.burst == p2.burst) {
        return p1.arrival < p2.arrival;
    }
    return p1.burst < p2.burst;
}

void sort_by_pid(vector<Process>& v, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j].id > v[j + 1].id) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

void custom_sort(vector<Process>& v, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j].arrival > v[j + 1].arrival) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

void SJF(vector<Process>& v) {
    int n = v.size();
    int time = 0; 
    vector<bool> isCompleted(n, false);
    
    custom_sort(v, n);

    int completed = 0;
    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; ++i) {
            if (!isCompleted[i] && v[i].arrival <= time) {
                if (idx == -1 || v[i].burst < v[idx].burst || 
                    (v[i].burst == v[idx].burst && v[i].arrival < v[idx].arrival)) {
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            v[idx].completion = time + v[idx].burst;
            v[idx].turnaround = v[idx].completion - v[idx].arrival;
            v[idx].waiting = v[idx].turnaround - v[idx].burst;
            time = v[idx].completion;
            isCompleted[idx] = true;
            completed++;
        } else {
            time++; 
        }
    }

    sort_by_pid(v, n);

    cout << "Process ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time\n";
    for (int i = 0; i < n; ++i) {
        cout << v[i].id << "\t\t"
            << v[i].arrival << "\t\t"
            << v[i].burst << "\t\t"
            << v[i].completion << "\t\t"
            << v[i].waiting << "\t\t"
            << v[i].turnaround << "\n";
    }

    float totalTurnaround = 0, totalWaiting = 0;
    for (int i = 0; i < n; ++i) {
        totalTurnaround += v[i].turnaround;
        totalWaiting += v[i].waiting;
    }
    cout << endl;
    cout << "Total Turnaround Time: " << totalTurnaround << endl;
    cout << "Total Waiting Time: " << totalWaiting << endl;
    cout << "Average Turnaround Time: " << totalTurnaround / n << endl;
    cout << "Average Waiting Time: " << totalWaiting / n << endl;
}


void sjf_preemptive(vector<Process>& v, int n) {
    int time = 0;
    int completed = 0;
    vector<int> is_completed(n, false);
   
    custom_sort(v, n);
   
    while (completed < n) {
        int min_burst_time = INT_MAX;
        int index = -1;
       
        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && v[i].arrival <= time && v[i].remaining_burst_time > 0) {
                if (v[i].remaining_burst_time < min_burst_time) {
                    min_burst_time = v[i].remaining_burst_time;
                    index = i;
                }
            }
        }

        if (index == -1) {
            time++;
        } else {
            if (v[index].response_time == -1) {
                v[index].response_time = time - v[index].arrival;
            }
            v[index].remaining_burst_time--;
            time++;
           
            if (v[index].remaining_burst_time == 0) {
                v[index].completion = time;
                v[index].turnaround = v[index].completion - v[index].arrival;
                v[index].waiting = v[index].turnaround - v[index].burst;
                is_completed[index] = true;
                completed++;
            }
        }
    }
   
    sort_by_pid(v, n);

    float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += v[i].waiting;
        total_turnaround_time += v[i].turnaround;
        total_response_time += v[i].response_time;
    }
   
    cout << "PID\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\t\tRT\n";
    for (int i = 0; i < n; i++) {
        cout << v[i].id << "\t\t"
             << v[i].arrival << "\t\t"
             << v[i].burst << "\t\t"
             << v[i].completion <<"\t\t"
             << v[i].turnaround << "\t\t"
             << v[i].waiting << "\t\t"
             << v[i].response_time << "\n";
             
    }

    cout << "\nAverage Waiting Time: " << total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << total_turnaround_time / n << endl;
    cout << "Average Response Time: " << total_response_time / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<Process> v(n);
    
    for (int i = 0; i < n; ++i) {
        v[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> v[i].arrival >> v[i].burst;
    }
    
    SJF(v);
    
    return 0;
}