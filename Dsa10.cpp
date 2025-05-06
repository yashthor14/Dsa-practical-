#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    // Input validation
    if (n <= 0) {
        cout << "Invalid number of students.\n";
        return 1;
    }

    vector<int> marks(n);
    cout << "Enter marks of " << n << " students:\n";
    for (int i = 0; i < n; i++) {
        cout << "Student " << i + 1 << ": ";
        cin >> marks[i];
    }

    // Using max heap and min heap
    priority_queue<int> maxHeap; // max-heap for maximum
    priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap for minimum

    for (int i = 0; i < n; i++) {
        maxHeap.push(marks[i]);
        minHeap.push(marks[i]);
    }

    int maxMarks = maxHeap.top();
    int minMarks = minHeap.top();

    cout << "\nMaximum Marks: " << maxMarks << endl;
    cout << "Minimum Marks: " << minMarks << endl;

    return 0;
}
