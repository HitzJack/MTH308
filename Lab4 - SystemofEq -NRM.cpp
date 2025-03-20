#include <bits/stdc++.h> // Includes all standard C++ libraries
using namespace std;

const double eps = 0.0001; // Convergence threshold for error

// Structure to store iteration results
struct Z {
    vector<double> xin;          // Input x values
    vector<vector<double>> K;    // Jacobian matrix (K matrix)
    vector<double> f;            // Function values
    vector<double> dx;           // Change in x values (Δx)
    vector<double> xout;         // Updated x values
    double err;                  // Error value
};

// Function to solve the nonlinear system using Newton-Raphson method
void Solve(int n) {
    // Lambda function to create the Jacobian matrix (K)
    auto make_K = [&](double x1, double x2) -> vector<vector<double>> {
        vector<vector<double>> K(n, vector<double>(n));
        K[0][0] = 2 * x1 + x2;       // ∂f1/∂x1
        K[0][1] = x1;                // ∂f1/∂x2
        K[1][0] = 3 * x2 * x2;       // ∂f2/∂x1
        K[1][1] = 1 + 6 * x1 * x2;   // ∂f2/∂x2
        return K;
    };

    // Lambda function to compute the inverse of K matrix
    auto inv_K = [&](vector<vector<double>> K) -> vector<vector<double>> {
        vector<vector<double>> inv(n, vector<double>(n));
        double det = K[0][0] * K[1][1] - K[1][0] * K[0][1]; // Determinant of K
        inv[0][0] = K[1][1] / det;
        inv[0][1] = -K[0][1] / det;
        inv[1][0] = -K[1][0] / det;
        inv[1][1] = K[0][0] / det;
        return inv;
    };

    // Lambda function to compute the function values f(x)
    auto make_f = [&](double x1, double x2) -> vector<double> {
        vector<double> f(n);
        f[0] = x1 * x1 + x1 * x2 - 10;        // f1(x1, x2)
        f[1] = x2 + 3 * x1 * x2 * x2 - 57;    // f2(x1, x2)
        return f;
    };

    // Lambda function to compute the error
    auto error = [&](double x1, double x2, double dx1, double dx2) -> double {
        double z1 = sqrt(dx1 * dx1 + dx2 * dx2); // Norm of change in x
        double z2 = sqrt(x1 * x1 + x2 * x2);     // Norm of x values
        return z1 / z2; // Relative error
    };

    // Lambda function to compute Δx using the inverse Jacobian and f
    auto delta_x = [&](vector<vector<double>> inv, vector<double> f) -> vector<double> {
        vector<double> dx(n);
        for (int i = 0; i < n; i++) {
            double z = 0;
            for (int c = 0; c < n; c++) {
                z += inv[i][c] * f[c];
            }
            dx[i] = -z; // Newton-Raphson formula: Δx = -K⁻¹ * f
        }
        return dx;
    };

    // Initial values
    double x1in = 1.5, x2in = 3.5;
    double x1out = x1in, x2out = x2in;
    double dx1 = 100, dx2 = 100; // Initial large values to enter the loop

    vector<Z> ANS; // Vector to store iteration results

    // Iteration loop until error is within threshold
    while (error(x1out, x2out, dx1, dx2) > eps) {
        auto K = make_K(x1in, x2in);     // Compute Jacobian matrix
        auto inv = inv_K(K);             // Compute inverse of Jacobian
        auto f = make_f(x1in, x2in);     // Compute function values
        auto dx = delta_x(inv, f);       // Compute Δx values

        // Update values
        dx1 = dx[0];
        dx2 = dx[1];
        x1out = x1in + dx1;
        x2out = x2in + dx2;

        double err = error(x1out, x2out, dx1, dx2); // Compute error

        // Store iteration data
        vector<double> xin = {x1in, x2in};
        vector<double> xout = {x1out, x2out};
        Z data = {xin, K, f, dx, xout, err};
        ANS.push_back(data);

        // Move to next iteration
        x1in = x1out;
        x2in = x2out;
    }

    // Set decimal precision for output
    cout << fixed << setprecision(5);

    // Print table header
    cout << setw(10) << "Iteration"
         << setw(12) << "x_1 in" << setw(12) << "x_2 in"
         << "  |  " << setw(10) << "K matrix"
         << "  |  " << setw(10) << "f"
         << "  |  " << setw(12) << "Δ x"
         << "  |  " << setw(12) << "x_1 out" << setw(12) << "x_2 out"
         << "  |  " << setw(10) << "er"
         << "\n";

    cout << string(120, '-') << "\n"; // Print a separator line

    // Print iteration results
    for (size_t i = 0; i < ANS.size(); i++) {
        const Z& data = ANS[i];

        // First row (Iteration, x_1 in, x_2 in, K matrix, f, Δx_1, x_1 out, x_2 out, er)
        cout << setw(10) << (i + 1)
             << setw(12) << data.xin[0] << setw(12) << data.xin[1]
             << "  |  " << setw(10) << data.K[0][0] << setw(10) << data.K[0][1]
             << "  |  " << setw(10) << data.f[0]
             << "  |  " << "Δ x_1 " << setw(6) << data.dx[0]
             << "  |  " << setw(12) << data.xout[0] << setw(12) << data.xout[1]
             << "  |  " << setw(10) << data.err << "\n";

        // Second row (empty iteration number, K matrix second row, f2, Δx_2)
        cout << setw(10) << " "
             << setw(12) << " " << setw(12) << " "
             << "  |  " << setw(10) << data.K[1][0] << setw(10) << data.K[1][1]
             << "  |  " << setw(10) << data.f[1]
             << "  |  " << "Δ x_2 " << setw(6) << data.dx[1]
             << "\n";

        cout << string(120, '-') << "\n"; // Print separator
    }
}

int32_t main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif 

    int N;
    cin >> N; // Read number of equations
    Solve(N); // Call solver
}
