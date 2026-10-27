#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
using pl = pair<ll,ll>;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;
using vvvl = vector<vector<vector<ll>>>;
#define all(x) (x).begin(), (x).end()
#define rep(i, s, n) for (int i = (s); i < (int)(n); i++)
const ll INF = 1LL << 60;
const ll MOD = 998244353;



ll isqrt(ll n){
    if(n<=0)return 0;
    ll ok=0,ng=3000000000LL;
    while(abs(ok-ng)>1){
        ll mid=(ok+ng)/2;
        if(mid*mid<=n)ok=mid;
        else ng=mid;
    }
    return ok;
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 巨大な数の平方根 (例: 10^18 - 1)
    ll N = 999999999999999999LL;
    
    cout << "--- 誤差のない整数平方根 ---" << '\n';
    cout << "N = " << N << '\n';
    cout << "isqrt(N) = " << isqrt(N) << '\n';
    
    // 境界値のテスト
    // 10^18 の平方根は 10^9 ちょうど。
    ll M = 1000000000000000000LL;
    cout << "\nN = " << M << '\n';
    cout << "isqrt(N) = " << isqrt(M) << '\n';
    // 出力: 1000000000
}