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

using mint = modint998244353;

struct Comb {
    int max_n;
    vector<mint> fact, fact_inv;
    Comb(int max_n) : max_n(max_n), fact(max_n + 1), fact_inv(max_n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= max_n; i++) fact[i] = fact[i - 1] * i;
        fact_inv[max_n] = fact[max_n].inv();
        for (int i = max_n - 1; i >= 0; i--) fact_inv[i] = fact_inv[i + 1] * (i + 1);
    }
    mint nCr(int n, int r) {
        if (n < r || n < 0 || r < 0) return 0;
        return fact[n] * fact_inv[r] * fact_inv[n - r];
    }
    mint nPr(int n, int r) {
        if (n < r || n < 0 || r < 0) return 0;
        return fact[n] * fact_inv[n - r];
    }
    mint nHr(int n, int r) {
        if (n == 0 && r == 0) return 1;
        if (n <= 0 || r < 0) return 0;
        return nCr(n + r - 1, r);
    }
    // [独自拡張] 階乗 n!
    mint fac(int n) {
        if (n < 0 || n > max_n) return 0;
        return fact[n];
    }
    // [独自拡張] 階乗の逆元 (n!)^-1
    mint finv(int n) {
        if (n < 0 || n > max_n) return 0;
        return fact_inv[n];
    }
    // [独自拡張] 単一の逆元 n^-1 を O(1) で取得
    mint inv(int n) {
        if (n <= 0 || n > max_n) return 0;
        return fact_inv[n] * fact[n - 1];
    }
};


/* 
 * メソッド仕様一覧:
 * 
 * - using mint = modint998244353;
 *   概要  : ACLの機能。出力時は cout << ans.val() << '\n'; とすること。
 * 
 * - Comb cb(max_n);
 *   概要  : n の最大値で初期化し、階乗と逆元を O(N) で事前計算する。
 * 
 * - cb.nCr(n, r); / cb.nPr(n, r); / cb.nHr(n, r);
 *   概要  : 組合せ、順列、重複組合せをそれぞれ O(1) で返す。
 * 
 * - cb.fac(n);
 *   概要  : [独自機能] n! を O(1) で返す。
 * 
 * - cb.finv(n);
 *   概要  : [独自機能] (n!)^-1 を O(1) で返す。
 * 
 * - cb.inv(n);
 *   概要  : [独自機能] n の逆元 (1/n の mod) を O(1) で返す。
 *           ※ 通常 mint(n).inv() は O(log N) かかるが、これを使えば O(1) になる。
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例:
    // ====================================================

    ll max_n = 500000;
    Comb cb(max_n);

    // 10個から3個選ぶ (10C3 = 120)
    mint ans1 = cb.nCr(10, 3);
    cout << "10C3 : " << ans1.val() << '\n';

    // 階乗の直接取得 (5! = 120)
    mint ans2 = cb.fac(5);
    cout << "5!   : " << ans2.val() << '\n';

    // O(1) での逆元取得 (3 の逆元)
    // 3 * 332748118 = 1 (mod 998244353)
    mint ans3 = cb.inv(3);
    cout << "3^-1 : " << ans3.val() << '\n';

    return 0;
}