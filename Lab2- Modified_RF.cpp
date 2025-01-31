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

 
void Solve(){
    
    // returns the value of function at a given point x;
    auto f = [&](double x) -> double{
        double v = 0.0;
        v += 2 * x * x * x - 2.5 * x - 5;
        // double pp = (98 * 1.0) / x;
        // v += 35 - (9.8 * x * (1 - pow(M_E, -pp))) / 14.0;
        return v;
    };
    double a = 1.0; // lower bound 
    double b = 2.0; // upper bound
    int il = 1;
    int iu = 1;
    double iterations = 0; // to keep count of number of iterations
    double w0 = b; // to keep track the last value of m ie xm_old
    double ea = 100; // the absolute relative error
    double F = f(a);
    double G = f(b);
    vector < array < double , 5 >> TABLE; // to store all the needed values to make a table
    while(abs(f(w0)) > epsilon_max){ // while loop breaks when number of iterations exceed 10
        double wn = (G * a - F * b) / (G - F);
        double z = f(wn) * f(a); // z checks the condition to whether switch xl to xm or xm to xl;
        TABLE.push_back({iterations , a , b , wn , f(wn)});
        w0 = wn;
        if(z > 0){ // if z > 0 i.e f(wn) * f(a) > 0 i.e a && wn are either both below x axis or above x axis hence we can use a to be wn now to shorten our bound
            a = wn;
            F = f(a); // Updating the value of the lower bound as lowe bound is changed to wn;
            il = 0;     /* Since lower_bound is changed il = 0 && iu is incremented by 1 */
            iu++;
            if(iu > 1){
                G /= 2.0;
            }
        }
        else{
            // f(a) * f(wn) < 0 i.e a and wn are on different sides of x - axis hence b = wn to shorten our bound
            
            b = wn; // Updating the value of the lower bound as lowe bound is changed to wn;
            G = f(b);   /* Since lower_bound is changed il = 0 && iu is incremented by 1 */
            iu = 0;
            il++;
            if(il > 1){
                F /= 2.0;
            }
        }
        iterations++;
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
