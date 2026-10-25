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


// ====================================================
// 高速素因数分解 (OSA-k法)
// ====================================================
struct Osa_k {
    int max_n;
    vector<int> spf; // spf[i] := i の最小の素因数 (Smallest Prime Factor)

    Osa_k(int max_n) : max_n(max_n), spf(max_n + 1) {
        iota(all(spf), 0); // 初期状態では spf[i] = i
        for (int i = 2; i * i <= max_n; i++) {
            if (spf[i] == i) {
                for (int j = i * i; j <= max_n; j += i) {
                    if (spf[j] == j) spf[j] = i;
                }
            }
        }
    }

    // 素因数分解を返す: {素因数, 指数} の配列
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

    // O(1) 素数判定
    bool is_prime(ll x) {
        if (x <= 1) return false;
        return spf[x] == x;
    }
};

// ====================================================
// O(√N) の約数全列挙 (単発の巨大な数用)
// ====================================================
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


/* 
 * メソッド仕様一覧:
 * 
 * --- Osa_k ---
 * 
 * - Osa_k osak(max_n);
 *   概要  : max_n までの SPF (最小素因数) テーブルを構築。通常 max_n は 10^6 〜 10^7 程度。
 *   計算量: O(max_n log log max_n) (エラトステネスの篩)
 * 
 * - osak.factorize(x);
 *   概要  : 数値 x を素因数分解し、{素因数, 指数} のペアの配列を返す。
 *           ※ RLE (ランレングス圧縮) と全く同じフォーマットで返却されるため扱いやすい。
 *   計算量: O(log x)
 * 
 * - osak.is_prime(x);
 *   概要  : [独自拡張] spf の値を利用し、数値 x が素数かどうかを O(1) で判定する。
 * 
 * --- get_divisors ---
 * 
 * - vl divs = get_divisors(n);
 *   概要  : 数値 n の約数を全て列挙し、昇順にソートした配列を返す。
 *           10^12 などの巨大な数値でも、単発であればこちらを使う。
 *   計算量: O(√n)
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例1: OSA-k法での高速素因数分解と素数判定
    // ====================================================
    // 10^6 までの素因数分解を高速に行う準備
    Osa_k osak(1000000);

    // 10080 の素因数分解 (10080 = 2^5 * 3^2 * 5^1 * 7^1)
    ll X = 10080;
    auto factors = osak.factorize(X);

    cout << "--- OSA-k法 ---" << '\n';
    cout << X << " の素因数分解:\n";
    for (auto [p, exp] : factors) {
        cout << p << "^" << exp << '\n';
    }

    // O(1) 素数判定
    cout << "999983 は素数か？: " << (osak.is_prime(999983) ? "Yes" : "No") << '\n';


    // ====================================================
    // 使用例2: 約数全列挙
    // ====================================================
    // Osa_k ではメモリが足りない 10^12 クラスの巨大な数の約数を列挙
    ll Y = 1000000000000LL;
    vl divs = get_divisors(Y);

    cout << "\n--- 約数全列挙 ---" << '\n';
    cout << Y << " の約数の個数: " << divs.size() << '\n';
    cout << "最小の5つの約数: ";
    rep(i, 0, min(5, (int)divs.size())) cout << divs[i] << " ";
    cout << '\n';

    return 0;
}