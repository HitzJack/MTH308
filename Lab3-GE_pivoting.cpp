#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void gaussianElimination(vector<vector<double>> &A, vector<double> &B, int n) {
    for (int i = 0; i < n; i++) {
        // Partial Pivoting (optional but improves numerical stability)
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        swap(A[i], A[maxRow]);
        swap(B[i], B[maxRow]);

        // Make diagonal element 1 (not necessary for upper triangular, but useful for scaling)
        double diagElement = A[i][i];
        if (diagElement == 0) {
            cout << "Mathematical Error: Singular Matrix" << endl;
            return;
        }

        // Forward Elimination
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            B[j] -= factor * B[i]; // Modify B accordingly
        }
    }
}

void printMatrix(const vector<vector<double>> &A, const vector<double> &B, int n) {
    cout << "\nUpper Triangular Matrix (A) and Modified Vector (B):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(8) << setprecision(4) << A[i][j] << " ";
        }
        cout << " | " << setw(8) << setprecision(4) << B[i] << endl;
    }
}

int main() {
    int n;
    cout << "Enter the size of the matrix (n): ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> B(n);

    cout << "Enter the elements of matrix A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Enter the elements of vector B (" << n << "x1):\n";
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }

    gaussianElimination(A, B, n);
    printMatrix(A, B, n);

    return 0;
}
