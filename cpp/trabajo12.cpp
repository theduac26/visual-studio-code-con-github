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
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % maxVal + 1;
    }
    return arr;
}

void bucketSort(std::vector<int>& arr, int bucketSize = 10) {
    if (arr.empty()) {
        return;
    }

    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());

    int bucketCount = (maxVal - minVal) / bucketSize + 1;
    std::vector<std::vector<int>> buckets(bucketCount);

    for (int val : arr) {
        int bucketIndex = (val - minVal) / bucketSize;
        buckets[bucketIndex].push_back(val);
    }

    int index = 0;
    for (auto& bucket : buckets) {
        if (!bucket.empty()) {
            std::sort(bucket.begin(), bucket.end());
            for (int val : bucket) {
                arr[index++] = val;
            }
        }
    }
}

int main() {
    std::vector<int> arr = createRandomArray(15, 100);
    
    std::cout << "Arreglo Original:" << std::endl;
    printArray(arr);

    bucketSort(arr);

    std::cout << "\nArreglo Ordenado (Bucket Sort):" << std::endl;
    printArray(arr);

    return 0;
}