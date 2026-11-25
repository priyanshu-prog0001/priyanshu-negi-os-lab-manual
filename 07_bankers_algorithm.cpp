// Program 7: Deadlock avoidance - Banker's Algorithm
#include <iostream>
#include <vector>
using namespace std;

const int P = 5;   // processes
const int R = 3;   // resource types

int available[R], maximum[P][R], allocation[P][R], need_[P][R];

void calculateNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need_[i][j] = maximum[i][j] - allocation[i][j];
}

bool isSafe(vector<int> &safeSeq) {
    int work[R];
    vector<bool> finish(P, false);
    for (int j = 0; j < R; j++) work[j] = available[j];
    safeSeq.clear();
    while ((int)safeSeq.size() < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (finish[i]) continue;
            bool ok = true;
            for (int j = 0; j < R; j++)
                if (need_[i][j] > work[j]) { ok = false; break; }
            if (ok) {
                for (int k = 0; k < R; k++) work[k] += allocation[i][k];
                safeSeq.push_back(i);
                finish[i] = true;
                found = true;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool requestResources(int pid, const int request[]) {
    for (int j = 0; j < R; j++) {
        if (request[j] > need_[pid][j]) {
            cout << "Error: process has exceeded its maximum claim.\n";
            return false;
        }
        if (request[j] > available[j]) {
            cout << "Request denied: not enough resources available.\n";
            return false;
        }
    }
    for (int j = 0; j < R; j++) {            // tentative allocation
        available[j] -= request[j];
        allocation[pid][j] += request[j];
        need_[pid][j] -= request[j];
    }
    vector<int> seq;
    if (isSafe(seq)) {
        cout << "Request can be granted safely.\nSafe sequence: ";
        for (int s : seq) cout << "P" << s << " ";
        cout << "\n";
        return true;
    }
    for (int j = 0; j < R; j++) {            // rollback
        available[j] += request[j];
        allocation[pid][j] -= request[j];
        need_[pid][j] += request[j];
    }
    cout << "Request denied: would lead to an unsafe state.\n";
    return false;
}

int main() {
    cout << "Enter available resources of each type (" << R << " types): ";
    for (int j = 0; j < R; j++) cin >> available[j];
    cout << "Enter Maximum matrix (" << P << " processes x " << R << " resources):\n";
    for (int i = 0; i < P; i++) for (int j = 0; j < R; j++) cin >> maximum[i][j];
    cout << "Enter Allocation matrix:\n";
    for (int i = 0; i < P; i++) for (int j = 0; j < R; j++) cin >> allocation[i][j];
    calculateNeed();

    vector<int> seq;
    if (isSafe(seq)) {
        cout << "System is in a SAFE state.\nSafe sequence: ";
        for (int s : seq) cout << "P" << s << " ";
        cout << "\n";
    } else {
        cout << "System is in an UNSAFE state.\n";
    }

    int pid, request[R];
    cout << "\nEnter process number requesting resources: ";
    cin >> pid;
    if (pid < 0 || pid >= P) { cout << "Invalid process number.\n"; return 1; }
    cout << "Enter request vector (" << R << " values): ";
    for (int j = 0; j < R; j++) cin >> request[j];
    requestResources(pid, request);
    return 0;
}
