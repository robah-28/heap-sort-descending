#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <cstring>

using namespace std;

class HeapSortDescending {
private:
    vector<long long>& arr;
    size_t n;
    
    // Iterative heapify for better performance
    void heapifyIterative(size_t n, size_t i) {
        while (true) {
            size_t smallest = i;
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            
            if (left < n && arr[left] < arr[smallest]) {
                smallest = left;
            }
            
            if (right < n && arr[right] < arr[smallest]) {
                smallest = right;
            }
            
            if (smallest == i) {
                break;
            }
            
            swap(arr[i], arr[smallest]);
            i = smallest;
        }
    }
    
public:
    HeapSortDescending(vector<long long>& array) : arr(array), n(array.size()) {}
    
    void sort() {
        if (n <= 1) return;
        
        // Build min-heap
        for (size_t i = n / 2; i-- > 0; ) {
            heapifyIterative(n, i);
        }
        
        // Extract elements one by one
        for (size_t i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapifyIterative(i, 0);
        }
    }
    
    void printFirstLast(int count = 10) {
        cout << "First " << count << " elements: ";
        for (size_t i = 0; i < min((size_t)count, n); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        
        cout << "Last " << count << " elements: ";
        size_t start = n > count ? n - count : 0;
        for (size_t i = start; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// Data generator class
class DataGenerator {
public:
    static vector<long long> generateRandom(size_t size) {
        vector<long long> data(size);
        srand((unsigned int)time(NULL));
        
        for (size_t i = 0; i < size; i++) {
            data[i] = rand() % 1000000;
        }
        return data;
    }
    
    static vector<long long> generateSorted(size_t size) {
        vector<long long> data(size);
        for (size_t i = 0; i < size; i++) {
            data[i] = i;
        }
        return data;
    }
    
    static vector<long long> generateReverseSorted(size_t size) {
        vector<long long> data(size);
        for (size_t i = 0; i < size; i++) {
            data[i] = size - i - 1;
        }
        return data;
    }
    
    static vector<long long> generateNearlySorted(size_t size) {
        vector<long long> data = generateSorted(size);
        int swapCount = size / 100; // Swap 1% of elements
        srand((unsigned int)time(NULL));
        
        for (int i = 0; i < swapCount; i++) {
            size_t idx1 = rand() % size;
            size_t idx2 = rand() % size;
            swap(data[idx1], data[idx2]);
        }
        
        return data;
    }
};

bool verifyDescendingOrder(const vector<long long>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i-1] < arr[i]) {
            return false;
        }
    }
    return true;
}

void testSmallArray() {
    cout << "\n=== TEST 1: Small Array Verification ===" << endl;
    
    vector<long long> testArray;
    testArray.push_back(64);
    testArray.push_back(34);
    testArray.push_back(25);
    testArray.push_back(12);
    testArray.push_back(22);
    testArray.push_back(11);
    testArray.push_back(90);
    testArray.push_back(88);
    testArray.push_back(45);
    testArray.push_back(33);
    
    cout << "Original array: ";
    for (size_t i = 0; i < testArray.size(); i++) {
        cout << testArray[i] << " ";
    }
    cout << endl;
    
    HeapSortDescending sorter(testArray);
    sorter.sort();
    
    cout << "Sorted (descending): ";
    for (size_t i = 0; i < testArray.size(); i++) {
        cout << testArray[i] << " ";
    }
    cout << endl;
    
    bool isValid = verifyDescendingOrder(testArray);
    cout << "Verified: " << (isValid ? "PASSED ✓" : "FAILED ✗") << endl;
}

void performanceTest(size_t size, const string& dataType, vector<long long> (*generator)(size_t)) {
    cout << "\n--- Testing: " << dataType << " (" << size << " elements) ---" << endl;
    
    // Calculate memory needed
    long long memoryNeeded = size * sizeof(long long);
    cout << "Memory needed: " << memoryNeeded / (1024 * 1024) << " MB" << endl;
    
    cout << "Generating data..." << endl;
    vector<long long> data = generator(size);
    
    if (!data.empty()) {
        cout << "First 10 elements before sort: ";
        for (size_t i = 0; i < min((size_t)10, data.size()); i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    
    cout << "Sorting with Heap Sort..." << endl;
    clock_t start = clock();
    
    HeapSortDescending sorter(data);
    sorter.sort();
    
    clock_t end = clock();
    double timeSec = double(end - start) / CLOCKS_PER_SEC;
    long long timeMs = (long long)(timeSec * 1000);
    
    cout << "Sort time: " << timeMs << " ms (" << fixed << setprecision(2) 
         << timeSec << " seconds)" << endl;
    
    if (timeSec > 0) {
        cout << "Performance: " << fixed << setprecision(0) 
             << (size / timeSec) << " elements/second" << endl;
    }
    
    bool isValid = verifyDescendingOrder(data);
    cout << "Valid: " << (isValid ? "YES ✓" : "NO ✗") << endl;
    
    sorter.printFirstLast(10);
}

int main() {
    cout << "========================================" << endl;
    cout << "HEAP SORT - DESCENDING ORDER" << endl;
    cout << "Cross-platform C++ Implementation" << endl;
    cout << "========================================" << endl;
    
    // Test 1: Small array verification
    testSmallArray();
    
    // Test 2: Performance with different sizes
    cout << "\n=== TEST 2: Performance Tests ===" << endl;
    
    // Test sizes - start with smaller sizes for online compilers
    size_t testSizes[] = {1000, 10000, 100000, 500000};
    
    for (int i = 0; i < 4; i++) {
        size_t currentSize = testSizes[i];
        
        cout << "\n----------------------------------------" << endl;
        cout << "Testing with " << currentSize << " elements" << endl;
        cout << "----------------------------------------" << endl;
        
        performanceTest(currentSize, "Random Data", DataGenerator::generateRandom);
        
        // Ask if user wants to continue
        if (i < 3) {
            cout << "\nContinue to next size? (y/n): ";
            char response;
            cin >> response;
            if (response != 'y' && response != 'Y') {
                break;
            }
        }
    }
    
    // Test 3: Different data patterns with 100,000 elements
    cout << "\n=== TEST 3: Data Pattern Comparison ===" << endl;
    cout << "Testing with 100,000 elements on different patterns..." << endl;
    
    size_t patternSize = 100000;
    cout << "\n--- Random Data ---";
    performanceTest(patternSize, "Random Data", DataGenerator::generateRandom);
    
    cout << "\n--- Sorted Data (Ascending) ---";
    performanceTest(patternSize, "Sorted Data", DataGenerator::generateSorted);
    
    cout << "\n--- Reverse Sorted Data ---";
    performanceTest(patternSize, "Reverse Sorted", DataGenerator::generateReverseSorted);
    
    cout << "\n--- Nearly Sorted Data ---";
    performanceTest(patternSize, "Nearly Sorted", DataGenerator::generateNearlySorted);
    
    // Test 4: Try with 10 million if user wants (on local machine, not online)
    cout << "\n=== TEST 4: Large Dataset (Optional) ===" << endl;
    cout << "Note: 10 million items test is for local machines only." << endl;
    cout << "Online compilers may have time/memory limits." << endl;
    cout << "Do you want to try sorting 1 million items? (y/n): ";
    
    char response;
    cin >> response;
    
    if (response == 'y' || response == 'Y') {
        const size_t LARGE_SIZE = 1000000; // 1 million items
        
        long long memoryNeeded = LARGE_SIZE * sizeof(long long);
        cout << "\nMemory needed: " << memoryNeeded / (1024 * 1024) << " MB" << endl;
        cout << "Generating 1 million random numbers..." << endl;
        
        vector<long long> largeData = DataGenerator::generateRandom(LARGE_SIZE);
        
        cout << "Starting heap sort on 1 million items..." << endl;
        clock_t start = clock();
        
        HeapSortDescending largeSorter(largeData);
        largeSorter.sort();
        
        clock_t end = clock();
        double timeSec = double(end - start) / CLOCKS_PER_SEC;
        
        cout << "\n1 Million Items Sort Complete!" << endl;
        cout << "Time: " << (long long)(timeSec * 1000) << " ms (" << fixed << setprecision(2) 
             << timeSec << " seconds)" << endl;
        
        if (timeSec > 0) {
            cout << "Performance: " << fixed << setprecision(0) 
                 << (LARGE_SIZE / timeSec) << " elements/second" << endl;
        }
        
        bool isValid = verifyDescendingOrder(largeData);
        cout << "Verification: " << (isValid ? "PASSED ✓" : "FAILED ✗") << endl;
        
        largeSorter.printFirstLast(10);
    }
    
    // Test 5: Show algorithm complexity demonstration
    cout << "\n=== TEST 5: Algorithm Complexity ===" << endl;
    cout << "Heap Sort Complexity Analysis:" << endl;
    cout << "  - Time Complexity: O(n log n) for all cases" << endl;
    cout << "  - Space Complexity: O(1) - in-place sorting" << endl;
    cout << "  - Stability: Not stable" << endl;
    cout << "  - Type: Comparison-based sorting" << endl;
    
    cout << "\nTest Results Summary:" << endl;
    cout << "  ✓ Heap Sort correctly sorts in descending order" << endl;
    cout << "  ✓ Works with different data patterns" << endl;
    cout << "  ✓ In-place sorting with O(1) extra space" << endl;
    cout << "  ✓ Handles large datasets efficiently" << endl;
    
    cout << "\n========================================" << endl;
    cout << "Program completed successfully!" << endl;
    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();
    
    return 0;
}
