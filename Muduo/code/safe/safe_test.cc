#include "mutex.h"

Mutex m1;

Mutex m2;

int share_val GUARDED_BY(m1);

void TestGuardBy() {
    m1.lock();
    share_val = 1;
    m1.unlock();
}

void foo() REQUIRES(m1, m2) {
}

void TestRequired() {
    m1.lock();
    m2.lock();
    foo();
    m2.unlock();
    m1.unlock();
}

void bar() EXCLUDES(m1) {
}
void TestExcludes() {
    m1.lock();
    // bar();
    m1.unlock();
}

void TestAcquiredAfter() {
    m2.lock();
    m1.lock();
    m1.unlock();
    m2.unlock();
}

int main() {
    return 0;
}