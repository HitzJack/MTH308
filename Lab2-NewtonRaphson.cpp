#include <bits/stdc++.h>
using namespace std;
#define int long long

double epsilon_max = 1e-5;
void Solve()
{
    auto F = [&](double x) -> double{
        double v = 0.0;
        v += 2 * x * x * x - 2.5 * x - 5;
        return v;
    };
    auto f = [&](double x) -> double{
        double v = 0.0;
        v += 6 * x * x - 2.5;
        return v;
    };
    double x0 = 2;
    double iterations = 0; // to keep count of number of iterations
    double xm_old = x0; // to keep track the last value of m ie xm_old
    vector < array < double , 4 >> TABLE; // to store all the needed values to make a table
    while(abs(F(xm_old)) > epsilon_max){ // while loop breaks when number of iterations exceed 10
    	double x1 = x0 - F(x0) / f(x0);
        TABLE.push_back({iterations , x0 , x1 , F(x1)});
        xm_old = x1;
        iterations++;
        x0 = x1;
    }
    for(auto &x : TABLE){
        int p = 0;
        for(auto &y : x){
            if(p == 0){
                cout << fixed << setprecision(0) << y << "\t";
            }
            else{
                cout << fixed << setprecision(10) << y << "  ";
            }
            p++;
        }
        cout << "\n";
    }
    cout << "\n";
}
int32_t main()
{
    int t = 1;
    for (int i = 1; i <= t; i++)
    {
        Solve();
    }
}
