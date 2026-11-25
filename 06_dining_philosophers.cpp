// Program 6: Dining Philosophers (deadlock avoided by allowing at most N-1 at the table)
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <memory>
#include "sync_common.hpp"
using namespace std;

const int N = 5;
vector<unique_ptr<Semaphore>> forks;
Semaphore room(N - 1);

void philosopher(int id) {
    int left = id, right = (id + 1) % N;
    for (int cycle = 0; cycle < 2; cycle++) {
        SafePrint() << "Philosopher " << id << " is thinking\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        room.wait();
        forks[left]->wait();
        forks[right]->wait();
        SafePrint() << "Philosopher " << id << " is eating (fork " << left
                    << " and fork " << right << ")\n";
        this_thread::sleep_for(chrono::milliseconds(150));
        forks[right]->post();
        forks[left]->post();
        room.post();
        SafePrint() << "Philosopher " << id << " finished eating and put down forks\n";
    }
}

int main() {
    for (int i = 0; i < N; i++) forks.emplace_back(new Semaphore(1));
    vector<thread> t;
    for (int i = 0; i < N; i++) t.emplace_back(philosopher, i);
    for (auto &x : t) x.join();
    return 0;
}
