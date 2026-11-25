// Program 2: Thread creation and management (POSIX threads)
#include <iostream>
#include <pthread.h>
using namespace std;

const int NUM_THREADS = 4;

struct PartialSum {
    int start, end;
    long long sum;
};

void *sumRange(void *arg) {
    PartialSum *p = static_cast<PartialSum *>(arg);
    p->sum = 0;
    for (int i = p->start; i < p->end; i++) p->sum += i;
    // single stream insertion keeps output lines from interleaving badly
    cout << ("Thread " + to_string(pthread_self() % 100000) + ": sum[" +
             to_string(p->start) + ".." + to_string(p->end) + ") = " +
             to_string(p->sum) + "\n");
    pthread_exit(nullptr);
}

int main() {
    pthread_t threads[NUM_THREADS];
    PartialSum data[NUM_THREADS];
    const int n = 1000000;
    const int chunk = n / NUM_THREADS;
    long long total = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        data[i].start = i * chunk;
        data[i].end = (i == NUM_THREADS - 1) ? n : (i + 1) * chunk;
        pthread_create(&threads[i], nullptr, sumRange, &data[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], nullptr);
        total += data[i].sum;
    }
    cout << "Total sum (0 to " << n - 1 << ") computed using "
         << NUM_THREADS << " threads = " << total << endl;
    return 0;
}
