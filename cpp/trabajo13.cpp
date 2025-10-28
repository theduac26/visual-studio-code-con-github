#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

void printArray(const std::vector<int>& arr) {
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

std::vector<int> createRandomArray(int size, int maxVal) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % maxVal + 1;
    }
    return arr;
}

int getMax(const std::vector<int>& arr) {
    return *std::max_element(arr.begin(), arr.end());
}

void countSort(std::vector<int>& arr, int n, int exp) {
    std::vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return;

    int m = getMax(arr);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    std::vector<int> arr = createRandomArray(15, 1000);
    
    std::cout << "Arreglo Original:" << std::endl;
    printArray(arr);

    radixSort(arr);

    std::cout << "\nArreglo Ordenado (Radix Sort):" << std::endl;
    printArray(arr);

    return 0;
}