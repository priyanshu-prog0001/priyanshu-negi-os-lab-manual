// Program 8: Contiguous memory allocation - First Fit, Best Fit, Worst Fit
#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum class Strategy { First, Best, Worst };

void allocate(const vector<int> &bsize, const vector<int> &psize,
              Strategy s, const string &title) {
    vector<int> block = bsize;
    vector<int> alloc(psize.size(), -1);

    for (size_t i = 0; i < psize.size(); i++) {
        int pick = -1;
        for (size_t j = 0; j < block.size(); j++) {
            if (block[j] < psize[i]) continue;
            if (pick == -1) pick = j;
            else if (s == Strategy::Best && block[j] < block[pick]) pick = j;
            else if (s == Strategy::Worst && block[j] > block[pick]) pick = j;
            if (s == Strategy::First) break;
        }
        if (pick != -1) {
            alloc[i] = pick;
            block[pick] -= psize[i];
        }
    }

    cout << "\n--- " << title << " ---\n";
    cout << "Process No.\tProcess Size\tBlock No.\n";
    for (size_t i = 0; i < psize.size(); i++) {
        cout << "P" << i + 1 << "\t\t" << psize[i] << "\t\t";
        if (alloc[i] != -1) cout << "B" << alloc[i] + 1 << "\n";
        else cout << "Not Allocated\n";
    }
    int frag = 0;
    for (int b : block) frag += b;
    cout << "Total remaining free memory (fragments) = " << frag << "\n";
}

int main() {
    int bn, pn;
    cout << "Enter number of memory blocks: ";
    cin >> bn;
    vector<int> bsize(bn);
    cout << "Enter sizes of blocks: ";
    for (auto &x : bsize) cin >> x;
    cout << "Enter number of processes: ";
    cin >> pn;
    vector<int> psize(pn);
    cout << "Enter sizes of processes: ";
    for (auto &x : psize) cin >> x;

    allocate(bsize, psize, Strategy::First, "First Fit");
    allocate(bsize, psize, Strategy::Best, "Best Fit");
    allocate(bsize, psize, Strategy::Worst, "Worst Fit");
    return 0;
}
