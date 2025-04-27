#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    int id, arrival, burst, priority, remaining, completion, turnaround, waiting;
};

struct ComparePriority {
    bool operator()(Process const& p1, Process const& p2) {
        if (p1.priority == p2.priority) {
            return p1.arrival > p2.arrival;
        }
        return p1.priority < p2.priority;
    }
};

void priorityPreemptiveScheduling(vector<Process> &processes) {
    priority_queue<Process, vector<Process>, ComparePriority> readyQueue;
    int currentTime = 0, idleTime = 0;
    const int contextSwitchTime = 2;
    int processIndex = 0;
    int n = processes.size();
    Process* currentProcess = nullptr;
    vector<Process> completedProcesses;
    
    while (processIndex < n || !readyQueue.empty() || (currentProcess && currentProcess->remaining > 0)) {
        while (processIndex < n && processes[processIndex].arrival <= currentTime) {
            readyQueue.push(processes[processIndex]);
            processIndex++;
        }
        
        if (currentProcess && currentProcess->remaining > 0) {
            readyQueue.push(*currentProcess);
        }
        
        if (!readyQueue.empty()) {
            Process nextProcess = readyQueue.top();
            readyQueue.pop();
            
            if (!currentProcess || currentProcess->id != nextProcess.id) {
                currentTime += contextSwitchTime;
                idleTime += contextSwitchTime;
            }
            
            nextProcess.remaining--;
            currentTime++;
            
            if (nextProcess.remaining == 0) {
                nextProcess.completion = currentTime;
                nextProcess.turnaround = nextProcess.completion - nextProcess.arrival;
                nextProcess.waiting = nextProcess.turnaround - nextProcess.burst;
                completedProcesses.push_back(nextProcess);
                currentProcess = nullptr;
            } else {
                currentProcess = new Process(nextProcess);
            }
        } else {
            idleTime++;
            currentTime++;
        }
    }
    
    double totalTAT = 0, totalWT = 0;
    cout << "\nProcess ID | Completion Time | Turnaround Time | Waiting Time" << endl;
    for (auto &p : completedProcesses) {
        cout << " " << p.id << "\t\t" << p.completion << "\t\t" << p.turnaround << "\t\t" << p.waiting << endl;
        totalTAT += p.turnaround;
        totalWT += p.waiting;
    }
    
    cout << "\nAverage Turnaround Time: " << (totalTAT / n) << "s" << endl;
    cout << "Average Waiting Time: " << (totalWT / n) << "s" << endl;
    cout << "CPU Idle Percentage: " << ((double)idleTime / currentTime) * 100 << "%" << endl;
}

int main() {
    int n;
    vector<Process> processes;
    
    cout << "Enter number of processes: ";
    cin >> n;
    
    cout << "Enter Process ID, Arrival Time, Burst Time, and Priority:\n";
    for (int i = 0; i < n; i++) {
        Process p;
        cin >> p.id >> p.arrival >> p.burst >> p.priority;
        p.remaining = p.burst;
        processes.push_back(p);
    }
    
    priorityPreemptiveScheduling(processes);
    return 0;
}
