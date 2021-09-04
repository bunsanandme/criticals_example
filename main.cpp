#include <windows.h>
#include <iostream>
#include <thread>

using namespace std;

CRITICAL_SECTION cs;

const int N = 100;
int a = 0;
int b = 0;

void thread1() {
    for(int i = 0; i < N; i++) {
        EnterCriticalSection(&cs);
        a = b + 3;
        b--;
        cout << "[Thread 1: a = " << a << ", b = " << b << ']' << endl;
        LeaveCriticalSection(&cs);
    }
}

void thread2() {
    for(int i = 0; i < N; i++) {
        EnterCriticalSection(&cs);
        b += 2;
        cout << "[Thread 2: b = " << b << ']' << endl;
        LeaveCriticalSection(&cs);
    }
}

int main() {
    InitializeCriticalSection(&cs);
    thread thr1(thread1);
    thread thr2(thread2);
    thr2.join();
    thr1.join();
    return 0;
}