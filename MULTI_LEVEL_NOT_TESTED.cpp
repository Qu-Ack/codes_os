#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid, at, bt, qno;  // queue number: 0 or 1
};

int main() {
    int n, Q;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum for Q0 (RR): ";
    cin >> Q;
    vector<Process> p(n);
    cout << "Enter PID, arrival time, burst time, queue (0 or 1):\n";
    for (int i = 0; i < n; i++)
        cin >> p[i].pid >> p[i].at >> p[i].bt >> p[i].qno;

    // sort by arrival time
    sort(p.begin(), p.end(), [](auto &a, auto &b){
        return a.at < b.at;
    });

    vector<int> rem(n), ct(n), tat(n), wt(n);
    for (int i = 0; i < n; i++) rem[i] = p[i].bt;

    queue<int> q0, q1;
    vector<bool> inQ(n, false);
    int completed = 0, t = 0;

    while (completed < n) {
        // enqueue arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && !inQ[i] && rem[i] > 0) {
                if (p[i].qno == 0) q0.push(i);
                else                 q1.push(i);
                inQ[i] = true;
            }
        }

        int idx = -1;
        if (!q0.empty()) {
            // Round Robin on Q0
            idx = q0.front(); q0.pop(); inQ[idx] = false;
            int exec = min(Q, rem[idx]);
            rem[idx] -= exec;
            t += exec;
        }
        else if (!q1.empty()) {
            // FCFS on Q1
            idx = q1.front(); q1.pop(); inQ[idx] = false;
            t += rem[idx];
            rem[idx] = 0;
        }
        else {
            t++;  // idle
            continue;
        }

        if (rem[idx] == 0) {
            completed++;
            ct[idx] = t;
            tat[idx] = ct[idx] - p[idx].at;
            wt[idx] = tat[idx] - p[idx].bt;
        } else {
            // re-enqueue if RR and not finished
            if (p[idx].qno == 0) {
                for (int i = 0; i < n; i++) {
                    if (p[i].at <= t && !inQ[i] && rem[i] > 0) {
                        // newly arrived
                        if (p[i].qno == 0) { q0.push(i); inQ[i] = true; }
                        else               { q1.push(i); inQ[i] = true; }
                    }
                }
                q0.push(idx);
                inQ[idx] = true;
            }
        }
    }

    cout << "PID\tAT\tBT\tQ#\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].at  << "\t"
             << p[i].bt  << "\t"
             << p[i].qno << "\t"
             << ct[i]    << "\t"
             << tat[i]   << "\t"
             << wt[i]    << "\n";
    }
    return 0;
}
