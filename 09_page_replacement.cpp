// Program 9: Page replacement - FIFO, LRU, Optimal
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int fifo(const vector<int> &ref, int nf) {
    vector<int> frames(nf, -1);
    int front = 0, faults = 0;
    for (int page : ref) {
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            frames[front] = page;
            front = (front + 1) % nf;
            faults++;
        }
    }
    return faults;
}

int lru(const vector<int> &ref, int nf) {
    vector<int> frames, lastUsed;
    int faults = 0;
    for (int i = 0; i < (int)ref.size(); i++) {
        auto it = find(frames.begin(), frames.end(), ref[i]);
        if (it != frames.end()) {
            lastUsed[it - frames.begin()] = i;
            continue;
        }
        faults++;
        if ((int)frames.size() < nf) {
            frames.push_back(ref[i]);
            lastUsed.push_back(i);
        } else {
            int victim = min_element(lastUsed.begin(), lastUsed.end()) - lastUsed.begin();
            frames[victim] = ref[i];
            lastUsed[victim] = i;
        }
    }
    return faults;
}

int optimal(const vector<int> &ref, int nf) {
    vector<int> frames;
    int faults = 0, n = ref.size();
    for (int i = 0; i < n; i++) {
        if (find(frames.begin(), frames.end(), ref[i]) != frames.end()) continue;
        faults++;
        if ((int)frames.size() < nf) { frames.push_back(ref[i]); continue; }
        int victim = -1, farthest = -1;
        for (int j = 0; j < nf; j++) {
            int k = i + 1;
            while (k < n && ref[k] != frames[j]) k++;
            if (k == n) { victim = j; break; }          // never used again
            if (k > farthest) { farthest = k; victim = j; }
        }
        frames[victim] = ref[i];
    }
    return faults;
}

int main() {
    int n, nf;
    cout << "Enter number of pages in reference string: ";
    cin >> n;
    vector<int> ref(n);
    cout << "Enter the reference string: ";
    for (auto &x : ref) cin >> x;
    cout << "Enter number of frames: ";
    cin >> nf;
    if (nf <= 0) { cout << "Number of frames must be positive.\n"; return 1; }

    cout << "FIFO Page Faults    = " << fifo(ref, nf) << "\n";
    cout << "LRU Page Faults     = " << lru(ref, nf) << "\n";
    cout << "Optimal Page Faults = " << optimal(ref, nf) << "\n";
    return 0;
}
