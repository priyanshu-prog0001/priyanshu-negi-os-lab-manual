// Program 10: Disk scheduling - FCFS, SSTF, SCAN, C-SCAN
// SCAN / C-SCAN: head first moves towards the higher cylinders.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int fcfs(const vector<int> &req, int head) {
    int total = 0, cur = head;
    for (int r : req) { total += abs(cur - r); cur = r; }
    return total;
}

int sstf(const vector<int> &req, int head) {
    int n = req.size(), total = 0, cur = head;
    vector<bool> visited(n, false);
    for (int c = 0; c < n; c++) {
        int idx = -1, best = 1 << 30;
        for (int i = 0; i < n; i++)
            if (!visited[i] && abs(cur - req[i]) < best) {
                best = abs(cur - req[i]);
                idx = i;
            }
        visited[idx] = true;
        total += best;
        cur = req[idx];
    }
    return total;
}

int scan(const vector<int> &req, int head, int diskSize) {
    vector<int> lo, hi;
    for (int r : req) (r < head ? lo : hi).push_back(r);
    sort(lo.begin(), lo.end());
    sort(hi.begin(), hi.end());
    int total = 0, cur = head;
    for (int r : hi) { total += abs(cur - r); cur = r; }
    if (!lo.empty()) {                         // go to the end, then reverse
        total += abs(cur - (diskSize - 1));
        cur = diskSize - 1;
        for (int i = (int)lo.size() - 1; i >= 0; i--) {
            total += abs(cur - lo[i]);
            cur = lo[i];
        }
    }
    return total;
}

int cscan(const vector<int> &req, int head, int diskSize) {
    vector<int> lo, hi;
    for (int r : req) (r < head ? lo : hi).push_back(r);
    sort(lo.begin(), lo.end());
    sort(hi.begin(), hi.end());
    int total = 0, cur = head;
    for (int r : hi) { total += abs(cur - r); cur = r; }
    if (!lo.empty()) {
        total += abs(cur - (diskSize - 1));    // to the last cylinder
        total += diskSize - 1;                 // jump back to cylinder 0
        cur = 0;
        for (int r : lo) { total += abs(cur - r); cur = r; }
    }
    return total;
}

int main() {
    int n, head, diskSize;
    cout << "Enter number of requests: ";
    cin >> n;
    vector<int> req(n);
    cout << "Enter the requests: ";
    for (auto &x : req) cin >> x;
    cout << "Enter initial head position: ";
    cin >> head;
    cout << "Enter disk size (max cylinder + 1): ";
    cin >> diskSize;

    cout << "FCFS   total head movement = " << fcfs(req, head) << "\n";
    cout << "SSTF   total head movement = " << sstf(req, head) << "\n";
    cout << "SCAN   total head movement = " << scan(req, head, diskSize) << "\n";
    cout << "C-SCAN total head movement = " << cscan(req, head, diskSize) << "\n";
    return 0;
}
