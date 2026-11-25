// Task 2: Quick Sort, Lomuto partition, last element as pivot
#include <iostream>
using namespace std;

static long long comparisons = 0;   // counts arr[j] <= pivot tests
static bool trace = true;
static int gN = 0;

void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) cout << arr[i] << (i + 1 < n ? ", " : "");
    cout << "]";
}

void swapInts(int& a, int& b) { int t = a; a = b; b = t; }

// Lomuto partition: pivot = arr[high]; returns pivot's final index
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;                       // end of "<= pivot" region
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swapInts(arr[i], arr[j]);
        }
    }
    swapInts(arr[i + 1], arr[high]);       // put pivot in final place
    int pi = i + 1;
    if (trace) {
        cout << "  partition [" << low << ".." << high << "] pivot=" << pivot
             << " pi=" << pi << " -> ";
        printArray(arr, gN);
        cout << "\n";
    }
    return pi;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);       // exclude pi
        quickSort(arr, pi + 1, high);
    }
}

void runTest(const char* name, int arr[], int n, bool showTrace) {
    cout << "\n=== " << name << " ===\nBefore: ";
    printArray(arr, n);
    cout << "\n";
    gN = n; comparisons = 0; trace = showTrace;
    quickSort(arr, 0, n - 1);
    cout << "After : ";
    printArray(arr, n);
    cout << "\nTotal comparisons (arr[j] <= pivot): " << comparisons << "\n";
}

// First partition pass of {2,1,5,4,6,3} showing i, j and swaps
void firstPassTrace() {
    int a[] = {2, 1, 5, 4, 6, 3};
    int low = 0, high = 5, pivot = a[high], i = low - 1;
    cout << "\n=== Hand-trace: first partition of {2,1,5,4,6,3}, pivot=3 ===\n";
    for (int j = low; j < high; j++) {
        cout << "  j=" << j << " arr[j]=" << a[j] << (a[j] <= pivot ? " <= " : " > ") << pivot;
        if (a[j] <= pivot) {
            i++;
            swapInts(a[i], a[j]);
            cout << " -> i=" << i << ", swap arr[" << i << "] & arr[" << j << "] -> ";
        } else cout << " -> no swap, i=" << i << "   -> ";
        printArray(a, 6); cout << "\n";
    }
    swapInts(a[i + 1], a[high]);
    cout << "  final: swap arr[" << i + 1 << "] with pivot -> ";
    printArray(a, 6); cout << "  pi=" << i + 1 << "\n";
}

int main() {
    firstPassTrace();

    int t1[] = {2, 1, 5, 4, 6, 3};
    int t2[] = {35, 12, 43, 8, 51, 27, 19};
    runTest("Trace {2,1,5,4,6,3}", t1, 6, true);
    runTest("Trace {35,12,43,8,51,27,19}", t2, 7, true);

    int rnd[]  = {5, 1, 4, 2, 8};
    int srt[]  = {1, 2, 4, 5, 8};
    int rev[]  = {8, 5, 4, 2, 1};
    int rep[]  = {7, 7, 7, 7, 7};
    int one[]  = {9};
    runTest("Random order {5,1,4,2,8}", rnd, 5, true);
    runTest("Already sorted {1,2,4,5,8}", srt, 5, true);
    runTest("Reverse sorted {8,5,4,2,1}", rev, 5, true);
    runTest("Repeated {7,7,7,7,7}", rep, 5, true);
    runTest("Single element (n = 1)", one, 1, true);
    runTest("Empty array (n = 0)", nullptr, 0, true);

    cout << "\nNote: sorted/reverse/all-equal inputs each give n(n-1)/2 = 10 comparisons for n=5.\n";
    return 0;
}
