// Program 3: CPU Scheduling - FCFS, SJF, Priority, Round Robin
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

struct Process {
    int pid, at, bt, pr;
    int ct = 0, tat = 0, wt = 0, rem = 0;
};

void printResult(vector<Process> p) {
    sort(p.begin(), p.end(),
         [](const Process &a, const Process &b) { return a.pid < b.pid; });
    double totalWT = 0, totalTAT = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &x : p) {
        cout << x.pid << '\t' << x.at << '\t' << x.bt << '\t'
             << x.ct << '\t' << x.tat << '\t' << x.wt << '\n';
        totalWT += x.wt;
        totalTAT += x.tat;
    }
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time    = " << totalWT / p.size() << '\n';
    cout << "Average Turnaround Time = " << totalTAT / p.size() << '\n';
}

void finish(Process &p, int time) {
    p.ct = time;
    p.tat = p.ct - p.at;
    p.wt = p.tat - p.bt;
}

void fcfs(vector<Process> p) {
    sort(p.begin(), p.end(), [](const Process &a, const Process &b) {
        return a.at != b.at ? a.at < b.at : a.pid < b.pid; });
    int time = 0;
    for (auto &x : p) {
        time = max(time, x.at) + x.bt;
        finish(x, time);
    }
    printResult(p);
}

// Generic non-preemptive scheduler; key() decides who runs next (smaller = better)
template <typename KeyFn>
void nonPreemptive(vector<Process> p, KeyFn key) {
    int n = p.size(), completed = 0, time = 0;
    vector<bool> done(n, false);
    while (completed < n) {
        int idx = -1, best = INT_MAX;
        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].at <= time && key(p[i]) < best) {
                best = key(p[i]);
                idx = i;
            }
        if (idx == -1) { time++; continue; }
        time += p[idx].bt;
        finish(p[idx], time);
        done[idx] = true;
        completed++;
    }
    printResult(p);
}

void roundRobin(vector<Process> p, int quantum) {
    int n = p.size(), time = 0, completed = 0;
    for (auto &x : p) x.rem = x.bt;
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b) {
        return p[a].at != p[b].at ? p[a].at < p[b].at : p[a].pid < p[b].pid; });

    queue<int> q;
    vector<bool> inQ(n, false);
    int next = 0;                       // next process (by arrival) to admit
    auto admit = [&]() {
        while (next < n && p[order[next]].at <= time) {
            q.push(order[next]);
            inQ[order[next]] = true;
            next++;
        }
    };
    admit();
    while (completed < n) {
        if (q.empty()) { time = p[order[next]].at; admit(); continue; }
        int idx = q.front(); q.pop();
        int slice = min(quantum, p[idx].rem);
        time += slice;
        p[idx].rem -= slice;
        admit();                         // new arrivals go before the preempted process
        if (p[idx].rem > 0) q.push(idx);
        else { finish(p[idx], time); completed++; }
    }
    printResult(p);
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Process " << i + 1 << " - Arrival Time, Burst Time, Priority: ";
        cin >> p[i].at >> p[i].bt >> p[i].pr;
    }
    cout << "\nMenu:\n1. FCFS\n2. SJF (Non-preemptive)\n"
            "3. Priority (Non-preemptive)\n4. Round Robin\nEnter choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1: fcfs(p); break;
        case 2: nonPreemptive(p, [](const Process &x) { return x.bt; }); break;
        case 3: nonPreemptive(p, [](const Process &x) { return x.pr; }); break;
        case 4: {
            int quantum;
            cout << "Enter time quantum: ";
            cin >> quantum;
            roundRobin(p, quantum);
            break;
        }
        default: cout << "Invalid choice\n";
    }
    return 0;
}
