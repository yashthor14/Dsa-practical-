#include <iostream>
using namespace std;

void con_obst();
void print(int, int);

float a[20], b[20], wt[20][20], c[20][20];
int r[20][20], n;

int main() {
    int i;
    cout << "\n**** PROGRAM FOR OBST ******\n";
    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "\nEnter the probabilities for successful search:\n";
    for (i = 1; i <= n; i++) {
        cout << "p[" << i << "]: ";
        cin >> a[i];
    }

    cout << "\nEnter the probabilities for unsuccessful search:\n";
    for (i = 0; i <= n; i++) {
        cout << "q[" << i << "]: ";
        cin >> b[i];
    }

    con_obst();
    print(0, n);
    cout << endl;

    return 0;
}

void con_obst() {
    int i, j, k, l;
    
    // Initialize for chains of length 1
    for (i = 0; i < n; i++) {
        c[i][i] = 0.0;
        r[i][i] = 0;
        wt[i][i] = b[i];

        wt[i][i + 1] = b[i] + b[i + 1] + a[i + 1];
        c[i][i + 1] = wt[i][i + 1];
        r[i][i + 1] = i + 1;
    }

    c[n][n] = 0.0;
    r[n][n] = 0;
    wt[n][n] = b[n];

    // Dynamic programming for chains of length >= 2
    for (i = 2; i <= n; i++) { // length of chain
        for (j = 0; j <= n - i; j++) {
            int end = j + i;
            wt[j][end] = wt[j][end - 1] + a[end] + b[end];
            c[j][end] = 9999;

            for (l = j + 1; l <= end; l++) {
                float cost = c[j][l - 1] + c[l][end];
                if (cost < c[j][end]) {
                    c[j][end] = cost;
                    r[j][end] = l;
                }
            }
            c[j][end] += wt[j][end];
        }
    }

    cout << "\n\nOptimal BST is:\n";
    cout << "w[0][" << n << "] = " << wt[0][n] << endl;
    cout << "c[0][" << n << "] = " << c[0][n] << endl;
    cout << "r[0][" << n << "] = " << r[0][n] << endl;
}

void print(int l1, int r1) {
    if (l1 >= r1)
        return;

    int root = r[l1][r1];
    if (r[l1][root - 1] != 0)
        cout << "Left child of " << root << " is " << r[l1][root - 1] << endl;
    if (r[root][r1] != 0)
        cout << "Right child of " << root << " is " << r[root][r1] << endl;

    print(l1, root - 1);
    print(root, r1);
}
