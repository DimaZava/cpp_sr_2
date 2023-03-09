#include <iostream>

#define UNUSED(variable) (void)variable

// Basic
void example_1() {

    int i = 42;
    decltype(i) di = 57;

    const int ci = 0;
    decltype(ci) dci = 0;

    const int volatile cvi = 32;
    decltype(cvi) dcvi = 57;

    int *ptr = nullptr;
    decltype(ptr) dptr = nullptr;

    const int *const cptrc = &i;
    decltype(cptrc) dcptrc = &i;

    const int &iref = i;
    decltype(iref) diref = iref;

    UNUSED(di);
    UNUSED(dci);
    UNUSED(dcvi);
    UNUSED(dptr);
    UNUSED(dcptrc);
    UNUSED(diref);
}

// Middle
int func(int a, int b) {
    return a * b;
}

void example_2() {

    decltype(func(1, 2)) dfunc = 54; // func type ? A: int

    UNUSED(dfunc);
}

// Hard
void example_3() {
    int i = 42;

    int *ptr = nullptr;
    decltype(*ptr) ddefer = i;

    // Warning - this huck doesn't work in this case!
    // ddefer.trololo

    std::cout << "i = " << i << std::endl;
    ddefer = 138;
    std::cout << "i = " << i << std::endl;

    decltype(i) j = i;
    j = 139;
    std::cout << "i = " << i << std::endl;

    decltype((i)) j2 = i;
    j2 = 140;
    std::cout << "i = " << i << std::endl;

    UNUSED(j);
}

// Strange
void example_4() {

    int i = 42;

    const int *ptr = &i;

    decltype(auto) daptr = ptr; // daptr type ? A: const int *

    const volatile int cvi = 158;

    decltype(auto) dacvi = cvi; // const volatile int

    UNUSED(daptr);
    UNUSED(dacvi);
}

template <typename T, typename R>
auto tfunc(T a, R b) -> decltype(a * b) {
    // some very strange logic here
    return a * b;
}

int main() {

    example_1();
    example_2();
    example_3();
    example_4();

    return 0;
}
