#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid, at, bt, user;
};

int main() {
    int n, Q;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> Q;

    vector<Process> p(n);
    cout << "Enter PID, arrival time, burst time, user-ID:\n";
    for (int i = 0; i < n; i++)
        cin >> p[i].pid >> p[i].at >> p[i].bt >> p[i].user;

    // sort by arrival
    sort(p.begin(), p.end(), [](auto &a, auto &b){
        return a.at < b.at;
    });

    vector<int> rem(n), ct(n), tat(n), wt(n);
    for (int i = 0; i < n; i++) rem[i] = p[i].bt;

    // map user-ID → queue of process-indices
    unordered_map<int, queue<int>> userQ;
    vector<bool> inQ(n, false);
    vector<int> users; // track unique users in arrival order

    int completed = 0, t = 0;
    size_t uidx = 0;   // index in users for next user

    while (completed < n) {
        // enqueue newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!inQ[i] && p[i].at <= t && rem[i] > 0) {
                if (userQ.find(p[i].user) == userQ.end())
                    users.push_back(p[i].user);
                userQ[p[i].user].push(i);
                inQ[i] = true;
            }
        }

        if (users.empty()) {
            t++; continue; // no users ready
        }

        // find next user with nonempty queue
        int cnt = users.size();
        int uid;
        int idx = -1;
        for (int k = 0; k < cnt; k++) {
            uid = users[uidx];
            uidx = (uidx + 1) % cnt;
            if (!userQ[uid].empty()) {
                idx = userQ[uid].front();
                userQ[uid].pop();
                break;
            }
        }
        if (idx == -1) {
            t++; continue; // everyone’s queue is empty for now
        }

        // run one quantum slice
        int exec = min(Q, rem[idx]);
        rem[idx] -= exec;
        t += exec;

        if (rem[idx] == 0) {
            completed++;
            ct[idx] = t;
            tat[idx] = ct[idx] - p[idx].at;
            wt[idx] = tat[idx] - p[idx].bt;
            inQ[idx] = true;  // mark done
        } else {
            // re-enqueue this process in its user-queue
            userQ[p[idx].user].push(idx);
        }
    }

    cout << "PID\tAT\tBT\tUSER\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].at  << "\t"
             << p[i].bt  << "\t"
             << p[i].user<<"\t"
             << ct[i]    << "\t"
             << tat[i]   << "\t"
             << wt[i]    << "\n";
    }
    return 0;
}
