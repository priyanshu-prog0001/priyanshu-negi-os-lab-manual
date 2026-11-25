// Program 11: File allocation methods - Contiguous, Linked, Indexed
#include <iostream>
#include <vector>
using namespace std;

const int MAXBLOCKS = 30;
vector<int> disk_(MAXBLOCKS, 0);   // 0 = free, 1 = allocated

void resetDisk() { disk_.assign(MAXBLOCKS, 0); }

void contiguousAllocation() {
    resetDisk();
    int nf;
    cout << "\n--- Contiguous Allocation ---\nEnter number of files: ";
    cin >> nf;
    for (int f = 1; f <= nf; f++) {
        int start, len;
        cout << "File " << f << " - starting block, length: ";
        cin >> start >> len;
        bool ok = start >= 0 && len > 0;
        for (int i = start; ok && i < start + len; i++)
            if (i >= MAXBLOCKS || disk_[i] == 1) ok = false;
        if (!ok) { cout << "Allocation failed: blocks not free/out of range.\n"; continue; }
        for (int i = start; i < start + len; i++) disk_[i] = 1;
        cout << "File " << f << " allocated blocks " << start
             << " to " << start + len - 1 << "\n";
    }
}

void linkedAllocation() {
    resetDisk();
    int nf;
    cout << "\n--- Linked Allocation ---\nEnter number of files: ";
    cin >> nf;
    for (int f = 1; f <= nf; f++) {
        int len, count = 0;
        cout << "File " << f << " - number of blocks: ";
        cin >> len;
        cout << "File " << f << " allocated blocks: ";
        for (int i = 0; i < MAXBLOCKS && count < len; i++) {
            if (disk_[i] == 0) {
                disk_[i] = 1;
                if (count > 0) cout << " -> ";
                cout << i;
                count++;
            }
        }
        cout << " -> NULL\n";
        if (count < len) cout << "Warning: disk full, could not allocate all blocks.\n";
    }
}

void indexedAllocation() {
    resetDisk();
    int nf;
    cout << "\n--- Indexed Allocation ---\nEnter number of files: ";
    cin >> nf;
    for (int f = 1; f <= nf; f++) {
        int len, count = 0, indexBlock = -1;
        cout << "File " << f << " - number of data blocks needed: ";
        cin >> len;
        for (int i = 0; i < MAXBLOCKS; i++)
            if (disk_[i] == 0) { indexBlock = i; disk_[i] = 1; break; }
        if (indexBlock == -1) { cout << "Disk full.\n"; continue; }
        cout << "File " << f << " - Index block: " << indexBlock << ", Data blocks: ";
        for (int i = 0; i < MAXBLOCKS && count < len; i++)
            if (disk_[i] == 0) { disk_[i] = 1; cout << i << " "; count++; }
        cout << "\n";
        if (count < len) cout << "Warning: disk full, could not allocate all blocks.\n";
    }
}

int main() {
    int choice;
    cout << "Menu:\n1. Contiguous Allocation\n2. Linked Allocation\n"
            "3. Indexed Allocation\nEnter choice: ";
    cin >> choice;
    switch (choice) {
        case 1: contiguousAllocation(); break;
        case 2: linkedAllocation(); break;
        case 3: indexedAllocation(); break;
        default: cout << "Invalid choice\n";
    }
    return 0;
}
