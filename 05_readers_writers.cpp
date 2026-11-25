// Program 5: Readers-Writers problem (first problem, readers preference)
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "sync_common.hpp"
using namespace std;

Semaphore mtx(1), wrt(1);
int read_count = 0;
int shared_data = 0;

void reader(int id) {
    mtx.wait();
    if (++read_count == 1) wrt.wait();      // first reader locks the resource
    mtx.post();

    SafePrint() << "Reader " << id << ": read shared_data = " << shared_data << "\n";
    this_thread::sleep_for(chrono::milliseconds(200));

    mtx.wait();
    if (--read_count == 0) wrt.post();      // last reader unlocks the resource
    mtx.post();
}

void writer(int id) {
    wrt.wait();
    shared_data++;
    SafePrint() << "Writer " << id << ": wrote shared_data = " << shared_data << "\n";
    this_thread::sleep_for(chrono::milliseconds(300));
    wrt.post();
}

int main() {
    vector<thread> t;
    t.emplace_back(writer, 1);
    this_thread::sleep_for(chrono::milliseconds(20));   // let writer 1 start first
    for (int i = 1; i <= 5; i++) t.emplace_back(reader, i);
    t.emplace_back(writer, 2);
    for (auto &x : t) x.join();
    return 0;
}
