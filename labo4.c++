#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <chrono>
#include <random>

// Helper
template<typename Func>
void measure_time(Func func) {
    auto clock_start = std::chrono::high_resolution_clock::now();
    func();
    auto clock_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> comp_duration = (clock_end - clock_start);
    std::cout << comp_duration.count() << "ms" << std::endl;
}

// 1
int* create_rand_tab(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100; // Generar numeros aleatorios simples
    }
    return arr;
}

int main() {
    srand(time(NULL));

    // 1 (Setup)
    int n_small = 20;
    int* rand_tab_small = create_rand_tab(n_small);

    // 1.1
    std::vector<int> v1;
    for (int i = 0; i < n_small; ++i) v1.push_back(rand_tab_small[i]);
    for (auto a : v1) std::cout << a << " ";
    std::cout << std::endl;

    // 1.2
    std::set<int> s1;
    for (int i = 0; i < n_small; ++i) s1.insert(rand_tab_small[i]);
    for (auto a : s1) std::cout << a << " ";
    std::cout << std::endl;

    // 1.3
    std::unordered_set<int> us1;
    for (int i = 0; i < n_small; ++i) us1.insert(rand_tab_small[i]);
    for (auto a : us1) std::cout << a << " ";
    std::cout << std::endl;

    // 1.4
    std::multiset<int> ms1;
    for (int i = 0; i < n_small; ++i) ms1.insert(rand_tab_small[i]);
    for (auto a : ms1) std::cout << a << " ";
    std::cout << std::endl;

    // 1.5
    std::unordered_multiset<int> ums1;
    for (int i = 0; i < n_small; ++i) ums1.insert(rand_tab_small[i]);
    for (auto a : ums1) std::cout << a << " ";
    std::cout << std::endl;

    // 1.6
    std::map<int, int> m1;
    for (int i = 0; i < n_small; ++i) m1.insert(std::pair<int, int>(i, rand_tab_small[i]));
    for (auto a : m1) std::cout << a.first << "," << a.second << " ";
    std::cout << std::endl;

    // 1.7
    std::unordered_map<int, int> um1;
    for (int i = 0; i < n_small; ++i) um1.insert(std::pair<int, int>(i, rand_tab_small[i]));
    for (auto a : um1) std::cout << a.first << "," << a.second << " ";
    std::cout << std::endl;

    // 1.8
    std::multimap<int, int> mm1;
    for (int i = 0; i < n_small; ++i) mm1.insert(std::pair<int, int>(i, rand_tab_small[i]));
    for (auto a : mm1) std::cout << a.first << "," << a.second << " ";
    std::cout << std::endl;

    // 1.9
    std::unordered_multimap<int, int> umm1;
    for (int i = 0; i < n_small; ++i) umm1.insert(std::pair<int, int>(i, rand_tab_small[i]));
    for (auto a : umm1) std::cout << a.first << "," << a.second << " ";
    std::cout << std::endl;

    delete[] rand_tab_small;

    // 2 (Setup)
    int N = 100000;
    int* rand_tab_large = create_rand_tab(N);

    // 2.1
    measure_time([&]() {
        std::vector<int> v;
        for (int i = 0; i < N; ++i) v.push_back(rand_tab_large[i]);
    });

    // 2.2
    measure_time([&]() {
        std::vector<int> v;
        v.reserve(N);
        for (int i = 0; i < N; ++i) v.push_back(rand_tab_large[i]);
    });

    // 2.3
    measure_time([&]() {
        std::vector<int> v(N);
        for (int i = 0; i < N; ++i) v[i] = rand_tab_large[i];
    });

    // 2.4
    measure_time([&]() {
        std::vector<int> v(rand_tab_large, rand_tab_large + N);
    });

    // 2.5
    measure_time([&]() {
        int* arr = new int[N];
        for (int i = 0; i < N; ++i) arr[i] = rand_tab_large[i];
        delete[] arr;
    });

    // 2.6
    measure_time([&]() {
        std::list<int> l;
        for (int i = 0; i < N; ++i) l.push_back(rand_tab_large[i]);
    });

    // 2.7
    measure_time([&]() {
        std::queue<int> q;
        for (int i = 0; i < N; ++i) q.push(rand_tab_large[i]);
    });

    // 2.8
    measure_time([&]() {
        std::priority_queue<int> pq;
        for (int i = 0; i < N; ++i) pq.push(rand_tab_large[i]);
    });

    // 2.9
    measure_time([&]() {
        std::set<int> s;
        for (int i = 0; i < N; ++i) s.insert(rand_tab_large[i]);
    });

    // 2.10
    measure_time([&]() {
        std::unordered_set<int> us;
        for (int i = 0; i < N; ++i) us.insert(rand_tab_large[i]);
    });

    // 3 (Setup - Creacion persistente para pruebas de busqueda)
    std::vector<int> vec3(rand_tab_large, rand_tab_large + N);
    std::priority_queue<int> pq3; for(int i=0; i<N; ++i) pq3.push(rand_tab_large[i]);
    std::set<int> set3(rand_tab_large, rand_tab_large + N);
    std::unordered_set<int> uset3(rand_tab_large, rand_tab_large + N);

    // 3.1
    measure_time([&]() {
        auto it = std::max_element(vec3.begin(), vec3.end());
    });

    // 3.2
    measure_time([&]() {
        int max_val = pq3.top();
    });

    // 3.3
    measure_time([&]() {
        int max_val = *set3.rbegin();
    });

    // 3.4
    measure_time([&]() {
        auto it = std::max_element(uset3.begin(), uset3.end());
    });

    // 4.1
    measure_time([&]() {
        auto it = std::find(vec3.begin(), vec3.end(), 42);
    });

    // 4.2
    measure_time([&]() {
        // Priority queue no tiene busqueda (find), se debe copiar y vaciar
        std::priority_queue<int> temp = pq3;
        bool found = false;
        while (!temp.empty()) {
            if (temp.top() == 42) { found = true; break; }
            temp.pop();
        }
    });

    // 4.3
    measure_time([&]() {
        auto it = set3.find(42);
    });

    // 4.4
    measure_time([&]() {
        auto it = uset3.find(42);
    });

    delete[] rand_tab_large;
    return 0;
}
