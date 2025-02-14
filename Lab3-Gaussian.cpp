#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18
#define fi first
#define se second
#define pii pair<int,int>
const int MOD = 1e9 + 7;
mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

#ifndef ONLINE_JUDGE
#include "/Users/saaumitraraaj/Desktop/cp/debugtemp.cpp"
#else
#define debug(...)
#define debugArr(...)
#endif
 
void Solve()
{
    int n = 3;
    vector <vector <double>> A(n , vector <double>(n));
    for(auto &x : A){
        for(auto &y : x){
            cin >> y;   
        }
    }
    vector <double> B(n);
    for(auto &x : B) cin >> x;
    
    for(int i = 0 ; i < n ; i++){
        for(int j = i + 1 ; j < n ; j++){
            double x = A[j][i] / A[i][i];
            A[j][i] = 0.0;
            B[j] = B[j] - x * B[i];
            for(int k = i + 1 ; k < n ; k++){
                A[j][k] = A[j][k] - x * A[i][k];
            }
        }
    }
    vector <double> X(n);
    for(int i = n - 1 ; i >= 0 ; i--){
        double tmp = B[i] * 1.0;
        for(int j = i + 1 ; j < n ; j++){
            tmp -= A[i][j] * X[j];
        }
        X[i] = tmp / A[i][i];
    }
    for(auto &x : X){
        cout << x << " ";
    }
    cout << "\n";
    debug(A);
    debug(B);
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