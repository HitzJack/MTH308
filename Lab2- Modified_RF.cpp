#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18
#define ld long double
#define fi first
#define se second
#define pii pair<int,int>
const int MOD = 1e9 + 7;
mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

double epsilon_max = 1e-5;
#ifndef ONLINE_JUDGE
#include "/Users/saaumitraraaj/Desktop/cp/debugtemp.cpp"
#else
#define debug(...)
#define debugArr(...)
#endif
 
void Solve(){
    
    // returns the value of function at a given point x;
    auto f = [&](double x) -> double{
        double v = 0.0;
        // v += 2 * x * x * x - 2.5 * x - 5;
        double pp = (98 * 1.0) / x;
        v += 35 - (9.8 * x * (1 - pow(M_E, -pp))) / 14.0;
        return v;
    };
    double xl = 0.0; // lower bound 
    double xu = 100.0; // upper bound
    int il = 1;
    int iu = 1;
    double iterations = 0; // to keep count of number of iterations
    double xm_old = -1; // to keep track the last value of m ie xm_old
    double ea = 100; // the absolute relative error
    double F = f(xl);
    double G = f(xu);
    vector < array < double , 6 >> TABLE; // to store all the needed values to make a table
    while(abs(f(xm_old)) > epsilon_max){ // while loop breaks when number of iterations exceed 10
        double xm = (G * xl - F * xu) / (G - F);
        debug(xl , xu);
        double z = f(xl) * f(xm); // z checks the condition to whether switch xl to xm or xm to xl;
        double xm_new = xm;
        if(xm_old == -1){
            TABLE.push_back({iterations , xl , xu , xm , -1 , f(xm)});
            xm_old = xm_new;
        }
        else{
            ea = abs(xm_new - xm_old);
            ea /= abs(xm_new);
            ea *= 100; // ea represents absolute relative approximate error ie ea = abs(xm_old - xm_new) / abs(xm_new) * 100
            TABLE.push_back({iterations , xl , xu , xm , ea , f(xm)});
            xm_old = xm_new;
        }
        if(z > 0){ // if z > 0 i.e f(xl) * f(xm) > 0 i.e xl && xm are either both below x axis or above x axis hence we can use xl to be xm now to shorten our bound
            xl = xm;
            F = f(xl);
            il = 0;
            iu++;
            if(iu > 1){
                G /= 2.0;
            }
        }
        else{
            // f(xl) * f(xm) < 0 i.e xl and xm are on different sides of x - axis hence xu = xm to shorten our bound
            xu = xm;
            G = f(xu);
            iu = 0;
            il++;
            if(il > 1){
                F /= 2.0;
            }
        }
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
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif 
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; i++)
    {
        // cout << "Case #" << i << ": ";
        Solve();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
    return 0;
}