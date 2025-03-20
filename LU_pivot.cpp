#include<bits/stdc++.h>
using namespace std;

void doolittleLU(vector<vector<double>> &A, vector<vector<double>> &L, vector<vector<double>> &U, int n, int m) {
    L.assign(n, vector<double>(n, 0)); // L is square (n x n)
    U.assign(n, vector<double>(m, 0)); // U is upper triangular (n x m)

    for (int i = 0; i < n; i++) {
        
        int pivotRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > abs(A[pivotRow][i])) {
                pivotRow = k;
            }
        }
        // Swap rows if necessary
        if (pivotRow != i) {
            swap(A[i], A[pivotRow]);
        }
        // Compute Upper Triangular U
        for (int j = i; j < m; j++) {
            U[i][j] = A[i][j];
            for (int k = 0; k < i; k++){
                U[i][j] -= L[i][k] * U[k][j];
            }
        }

        // Compute Lower Triangular L
        for (int j = i; j < n; j++) {
            if (i == j)
                L[j][i] = 1; // Diagonal of L is 1
            else {
                L[j][i] = A[j][i];
                for (int k = 0; k < i; k++){
                    L[j][i] -= L[j][k] * U[k][i];
                }
                L[j][i] /= U[i][i];
            }
        }
    }
}

// Function to print a matrix
void printMatrix(const vector<vector<double>> &M, string name) {
    cout << name << " Matrix:\n";
    for (const auto &row : M) {
        for (double val : row)
            cout << setw(10) << fixed << setprecision(4) << val << " ";
        cout << endl;
    }
    cout << endl;
}

int main() {
    int n, m;
   
    cin >> n >> m;

    vector<vector<double>> A(n, vector<double>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> A[i][j];

    vector<vector<double>> L, U;
    doolittleLU(A, L, U, n, m);

    printMatrix(L, "Lower Triangular (L)");
    printMatrix(U, "Upper Triangular (U)");
    printMatrix(A, "Original  (A)");

    return 0;
}
