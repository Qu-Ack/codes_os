#include <bits/stdc++.h>
using namespace std;

int optimal(vector<int> refs, int nFrames) {
    set<int> frames;
    int faults = 0;
    for (int i = 0; i < (int)refs.size(); ++i) {
        int page = refs[i];
        if (frames.count(page)) continue;
        if ((int)frames.size() < nFrames) {
            frames.insert(page);
        } else {
            // find victim: page not used for longest time
            int victim = -1, farthest = i+1;
            for (int p : frames) {
                int j = i+1;
                while (j < (int)refs.size() && refs[j] != p) j++;
                if (j > farthest) { farthest = j; victim = p; }
            }
            frames.erase(victim);
            frames.insert(page);
        }
        faults++;
    }
    return faults;
}

int main() {
    int nFrames, nRefs;
    cin >> nFrames >> nRefs;
    vector<int> refs(nRefs);
    for (int &x : refs) cin >> x;
    cout << "Page faults (Optimal): " << optimal(refs, nFrames) << "\n";
}
