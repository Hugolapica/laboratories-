#include <iostream>
#include <exception>
#include <string>
#include <fstream>

// 1.d
class dynamic_array_out_of_range : public std::exception {
public:
    const char* what() const noexcept override {
        return "DynamicArray: out of range";
    }
};

// 1
template<typename T>
class DynamicArray {
private:
    // 1.a
    long capacity;
    T* arrayPointer;
    // 2.a
    std::ofstream fileStream;

public:
    // 2.b
    DynamicArray(long cap, std::string file_name) : capacity(cap) {
        // 1.b
        arrayPointer = new T[capacity];
        
        // 2.c
        fileStream.open(file_name);
        if (!fileStream.is_open()) {
            delete[] arrayPointer;
            throw std::runtime_error("File open error");
        }
    }

    ~DynamicArray() {
        // 1.c
        delete[] arrayPointer;
        
        // 2.d
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

    // 1.e
    void insert(long index, T element) {
        if (index < 0 || index >= capacity) {
            throw dynamic_array_out_of_range();
        }
        arrayPointer[index] = element;
    }

    // 1.f
    T& operator[](long index) {
        if (index < 0 || index >= capacity) {
            throw dynamic_array_out_of_range();
        }
        return arrayPointer[index];
    }

    // 2
    void saveContent() {
        if (fileStream.is_open()) {
            for (long i = 0; i < capacity; ++i) {
                fileStream << arrayPointer[i] << " ";
            }
        }
    }

    // 1.g
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<U>& arr);
};

// 1.g
template<typename U>
std::ostream& operator<<(std::ostream& os, const DynamicArray<U>& arr) {
    for (long i = 0; i < arr.capacity; ++i) {
        os << arr.arrayPointer[i] << " ";
    }
    return os;
}

// 3
template<typename T>
class MySmartPointer {
private:
    T* ptr;
public:
    // 3.a
    MySmartPointer(T* p) : ptr(p) {}

    // 3.b
    ~MySmartPointer() {
        delete ptr;
    }

    // 3.c
    T* operator->() { return ptr; }

    // 3.d
    T& operator*() { return *ptr; }
};

int main() {
    try {
        // 1 & 2
        DynamicArray<int> arr(3, "output.txt");
        arr.insert(0, 10);
        arr.insert(1, 20);
        arr.insert(2, 30);
        
        std::cout << arr << std::endl;
        arr.saveContent();

        // 2.e
        {
            DynamicArray<double>(2, "temp.txt").saveContent();
        }

        // 3.e
        MySmartPointer<int> smartPtr(new int(100));
        std::cout << *smartPtr << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
