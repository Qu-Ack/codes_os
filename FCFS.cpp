#include<bits/stdc++.h>
using namespace std;

bool compare(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
    if(a.first.first == b.first.first) return a.second<b.second;
    return a.first.first < b.first.first;
}

void fcfs(vector<pair<pair<int, int>, int>> p){
    sort(p.begin(), p.end(), compare);
    int n = p.size();
    int sum = 0;
    int ct[n], wt[n], tat[n];
    sum += p[0].first.first;
    for(int i = 0; i < n; i++){
        sum += p[i].first.second;
        ct[p[i].second] = sum;
        tat[p[i].second] = ct[p[i].second] - p[i].first.first;
        wt[p[i].second] = tat[p[i].second] - p[i].first.second;
        if (i < n - 1 && sum < p[i + 1].first.first){
            sum += p[i + 1].first.first - sum;
        }
    }
    float avgtat=0.0f,avgwt=0.0f;
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for(int i = 0; i < n; i++){
        cout << p[i].second+1<< "\t\t" << p[i].first.first << "\t\t" << p[i].first.second << "\t\t" 
             << ct[p[i].second] << "\t\t" << tat[p[i].second] << "\t\t" << wt[p[i].second] << endl;
    }
    for(int i = 0; i < n; i++){
        avgtat += tat[i];
        avgwt += wt[i];
    }
    avgtat /= n;
    avgwt /= n;
    cout << "Average Turnaround Time: " << avgtat << endl;
    cout << "Average Waiting Time: " << avgwt << endl;
}

int main(){
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<pair<pair<int, int>, int>> p(n);
    for(int i = 0; i < n; i++){
        cout << "Enter the arrival time and burst time of process " << i + 1 << ":\n";
        cin >> p[i].first.first >> p[i].first.second;
        p[i].second = i;
    }
    fcfs(p);
    
}