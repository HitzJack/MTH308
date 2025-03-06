#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18
#define fi first
#define se second
#define pii pair<int,int>
const int MOD = 1e9 + 7;
mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

const double eps = 0.0001;
#ifndef ONLINE_JUDGE
#include "/Users/saaumitraraaj/Desktop/cp/debugtemp.cpp"
#else
#define debug(...)
#define debugArr(...)
#endif
 
void Solve(int n)
{
	auto make_K = [&](double x1 , double x2) -> vector < vector <double>> {
		vector < vector <double>> K(n , vector <double> (n));
		K[0][0] = 2 * x1 + x2;
		K[0][1] = x1;
		K[1][0] = 3 * x2 * x2;
		K[1][1] = 1 + 6 * x1 * x2;
		return K;
	};
	auto inv_K = [&](vector <vector <double>> K) -> vector < vector <double>>{
		vector <vector <double>>inv(n , vector <double>(n));
		double det = K[0][0] * K[1][1] - K[1][0] * K[0][1];
		inv[0][0] = K[1][1] / det;
		inv[0][1] = -K[0][1] / det;
		inv[1][0] = -K[1][0] / det;
		inv[1][1] = K[0][0] / det;
		return inv;
	};
	auto make_f = [&](double x1 , double x2) -> vector <double>{
		vector <double> f(n);
		f[0] = x1 * x1 + x1 * x2 - 10;
		f[1] = x2 + 3 * x1 * x2 * x2 - 57;
		return f;
	};
	auto error = [&](double x1 , double x2 , double dx1 , double dx2) -> double{
		double z1 = sqrt(dx1 * dx1 + dx2 * dx2);
		double z2 = sqrt(x1 * x1 + x2 * x2);
		double z = z1 / z2;
		return z;
	};
	double x1in = 1.5;
	double x2in = 3.5;
	double x1out = 1.5;
	double x2out = 3.5;
	double its = 1;
	double dx1 = 100;
	double dx2 = 100;
	auto delta_x = [&](vector <vector <double>> inv , vector < double> f) -> vector <double>{
		vector <double> dx(n);
		for(int i = 0 ; i < n ; i++){
			double z = 0;
			for(int c = 0 ; c < n ; c++){
				z += inv[i][c] * f[c];
			}
			dx[i] = -z;
		}	
		return dx;
	};
	while(error(x1out , x2out , dx1 , dx2) > eps){
		auto K = make_K(x1in , x2in);
		auto inv = inv_K(K);
		auto f = make_f(x1in , x2in);
		auto dx = delta_x(inv , f);
		dx1 = dx[0];
		dx2 = dx[1];
		x1out = x1in + dx1;
		x2out = x2in + dx2;
		double err = error(x1out , x2out , dx1 , dx2);
		debug(x1in , x2in , K , f , dx , x1out , x2out , err);
		x1in = x1out;
		x2in = x2out;
		
		
		its++;
	}
	
}
int32_t main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif 
    int N; cin >> N;
    Solve(N);
}