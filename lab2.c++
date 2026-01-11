#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <iterator>

using namespace std;

// 1. a)
int random_value() {
    return rand() % 101;
}

// 1. c)
class RandomFunctor {
public:
    int operator()() {
        return rand() % 101;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    // 1.
    vector<int> v(10);

    // a)
    generate(v.begin(), v.end(), random_value);

    // b)
    generate(v.begin(), v.end(), []() { return rand() % 101; });

    // c)
    generate(v.begin(), v.end(), RandomFunctor());

    for (int n : v) cout << n << " ";
    cout << endl;

    // 2.
    int even_count = count_if(v.begin(), v.end(), [](int n) {
        return n % 2 == 0;
    });
    cout << even_count << endl;

    // 3.
    sort(v.begin(), v.end(), greater<int>());

    for (int n : v) cout << n << " ";
    cout << endl;

    // 4.
    if (v.size() >= 5) {
        v.erase(v.begin() + 4);
    }

    for (int n : v) cout << n << " ";
    cout << endl;

    // 5.
    int n = 10;
    vector<int> v_new;
    transform(v.begin(), v.end(), back_inserter(v_new), [n](int x) {
        return x * n;
    });

    for (int x : v_new) cout << x << " ";
    cout << endl;

    return 0;
}
