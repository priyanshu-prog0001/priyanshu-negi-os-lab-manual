// Program 4: Producer-Consumer (bounded buffer) using semaphores
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include "sync_common.hpp"
using namespace std;

const int BUFFER_SIZE = 5;
const int ITEMS = 10;

int buffer_[BUFFER_SIZE];
int in_ = 0, out_ = 0;
Semaphore emptySlots(BUFFER_SIZE), fullSlots(0), mtx(1);

void producer() {
    for (int i = 1; i <= ITEMS; i++) {
        emptySlots.wait();
        mtx.wait();
        buffer_[in_] = i;
        SafePrint() << "Producer produced item " << i << " at slot " << in_ << "\n";
        in_ = (in_ + 1) % BUFFER_SIZE;
        mtx.post();
        fullSlots.post();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer() {
    for (int i = 1; i <= ITEMS; i++) {
        fullSlots.wait();
        mtx.wait();
        int item = buffer_[out_];
        SafePrint() << "\t\tConsumer consumed item " << item << " from slot " << out_ << "\n";
        out_ = (out_ + 1) % BUFFER_SIZE;
        mtx.post();
        emptySlots.post();
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

int main() {
    thread prod(producer), cons(consumer);
    prod.join();
    cons.join();
    cout << "All items produced and consumed." << endl;
    return 0;
}
