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



struct Osa_k {
    int max_n;
    vector<int> spf;

    Osa_k(int max_n) : max_n(max_n), spf(max_n + 1) {
        iota(all(spf), 0);
        for (ll i = 2; i * i <= max_n; i++) {
            if (spf[i] == i) {
                for (long long j = i * i; j <= max_n; j += i) {
                    if (spf[j] == j) spf[j] = i;
                }
            }
        }
    }

    vector<pair<ll, ll>> factorize(ll x) {
        vector<pair<ll, ll>> res;
        if (x <= 1) return res;
        while (x > 1) {
            ll p = spf[x];
            ll count = 0;
            while (spf[x] == p) {
                count++;
                x /= p;
            }
            res.push_back({p, count});
        }
        return res;
    }

    bool is_prime(ll x) {
        if (x <= 1) return false;
        return spf[x] == x;
    }
};



vl get_divisors(ll n) {
    vl res;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i * i != n) res.push_back(n / i);
        }
    }
    sort(all(res));
    return res;
}



vector<pair<ll, ll>> prime_factorize(ll n) {
    vector<pair<ll, ll>> res;
    for (ll a = 2; a * a <= n; ++a) {
        if (n % a != 0) continue;
        ll ex = 0;
        while (n % a == 0) {
            ++ex;
            n /= a;
        }
        res.push_back({a, ex});
    }
    if (n != 1) res.push_back({n, 1});
    return res;
}



/* 
 * メソッド仕様一覧:
 * 
 * --- Osa_k ---
 * 
 * - Osa_k osak(max_n);
 *   概要  : max_n までの SPF (最小素因数) テーブルを構築。通常 max_n は 10^6 ～ 10^7 程度。
 *   計算量: O(max_n log log max_n) (エラトステネスの篩)
 * 
 * - osak.factorize(x);
 *   概要  : 数値 x を素因数分解し、{素因数, 指数} のペアの配列を返す。
 *   計算量: O(log x)
 * 
 * - osak.is_prime(x);
 *   概要  : 数値 x が素数かどうかを O(1) で判定する。
 * 
 * --- 単発用 (N <= 10^18) ---
 * 
 * - vl divs = get_divisors(n);
 *   概要  : 数値 n の約数を全て列挙し、昇順にソートした配列を返す。
 *   計算量: O(√n)
 * 
 * - auto factors = prime_factorize(n);
 *   概要  : 巨大な数値 n を素因数分解し、{素因数, 指数} の配列を返す。
 *   計算量: O(√n)
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例1: OSA-k法での高速素因数分解と素数判定
    // ====================================================
    Osa_k osak(1000000);
    ll X = 10080;
    auto factors = osak.factorize(X);

    cout << "--- OSA-k法 ---" << '\n';
    cout << X << " の素因数分解:\n";
    for (auto [p, exp] : factors) {
        cout << p << "^" << exp << '\n';
    }

    cout << "999983 は素数か？: " << (osak.is_prime(999983) ? "Yes" : "No") << '\n';


    // ====================================================
    // 使用例2: 約数全列挙 & 素因数分解 (巨大な数)
    // ====================================================
    ll Y = 1000000000000LL; // 10^12
    vl divs = get_divisors(Y);
    auto p_factors = prime_factorize(Y);

    cout << "\n--- 約数全列挙 & O(√N) 素因数分解 ---" << '\n';
    cout << Y << " の約数の個数: " << divs.size() << '\n';
    
    cout << Y << " の素因数分解:\n";
    for (auto [p, exp] : p_factors) {
        cout << p << "^" << exp << '\n';
    }

    return 0;
}