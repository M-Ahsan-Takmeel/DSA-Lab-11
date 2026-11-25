// Task 1: Merge Sort (stable, auxiliary arrays) with [low..high] merge trace
#include <iostream>
using namespace std;

static int mergeCalls = 0;
static bool trace = true;

void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) cout << arr[i] << (i + 1 < n ? ", " : "");
    cout << "]";
}

static int gN = 0;   // full array length, used only for tracing

// Merge two adjacent sorted halves arr[low..mid] and arr[mid+1..high]
void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;           // size of left half
    int n2 = high - mid;              // size of right half
    int* L = new int[n1];             // auxiliary storage
    int* R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];   // <= keeps stability
        else              arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];          // leftovers from L
    while (j < n2) arr[k++] = R[j++];          // leftovers from R

    delete[] L;                                // no memory leaks
    delete[] R;

    mergeCalls++;
    if (trace) {
        cout << "  merge [" << low << ".." << high << "] (mid=" << mid << ") -> ";
        printArray(arr, gN);
        cout << "\n";
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low >= high) return;                   // 0 or 1 element
    int mid = low + (high - low) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void runTest(const char* name, int arr[], int n) {
    cout << "\n=== " << name << " ===\nBefore: ";
    printArray(arr, n);
    cout << "\n";
    gN = n;
    mergeCalls = 0;
    mergeSort(arr, 0, n - 1);
    cout << "After : ";
    printArray(arr, n);
    cout << "\nmerge() calls: " << mergeCalls << "\n";
}

// Stability demo: sort pairs by key only, show equal keys keep original order
struct Item { int key; char tag; };
void mergeItems(Item a[], int low, int mid, int high) {
    int n1 = mid - low + 1, n2 = high - mid;
    Item* L = new Item[n1]; Item* R = new Item[n2];
    for (int i = 0; i < n1; i++) L[i] = a[low + i];
    for (int j = 0; j < n2; j++) R[j] = a[mid + 1 + j];
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) a[k++] = (L[i].key <= R[j].key) ? L[i++] : R[j++];
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    delete[] L; delete[] R;
}
void mergeSortItems(Item a[], int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    mergeSortItems(a, low, mid); mergeSortItems(a, mid + 1, high);
    mergeItems(a, low, mid, high);
}

int main() {
    int main1[] = {35, 12, 43, 8, 51, 27, 19};
    runTest("Main test {35,12,43,8,51,27,19}", main1, 7);

    trace = false;   // boundary cases: show only before/after
    int sorted[]   = {1, 2, 4, 5, 8};
    int reverse[]  = {8, 5, 4, 2, 1};
    int dups[]     = {5, 2, 5, 1, 2};
    int single[]   = {42};
    runTest("Already sorted", sorted, 5);
    runTest("Reverse sorted", reverse, 5);
    runTest("Repeated values", dups, 5);
    runTest("Single element (n = 1)", single, 1);
    runTest("Empty array (n = 0)", nullptr, 0);

    cout << "\n=== Stability demo (sort by number, letters = original order) ===\nBefore: ";
    Item s[] = {{5,'a'},{2,'b'},{5,'c'},{1,'d'},{2,'e'}};
    for (auto& x : s) cout << x.key << x.tag << " ";
    mergeSortItems(s, 0, 4);
    cout << "\nAfter : ";
    for (auto& x : s) cout << x.key << x.tag << " ";
    cout << "\n(equal keys keep original order -> stable)\n";
    return 0;
}
