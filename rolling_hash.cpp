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
#define rep(i, s, n) for (ll i = (s); i < (ll)(n); i++)
template <class T> bool chmin(T& a, T b){ if(a > b){ a = b; return 1; } return 0; }
template <class T> bool chmax(T& a, T b){ if(a < b){ a = b; return 1; } return 0; }
const ll INF = 1LL << 60;
const ll MOD = 998244353;



struct RollingHash {
    static const uint64_t mod = (1ULL << 61) - 1;
    uint64_t base;
    vector<uint64_t> hash, power;

    static inline uint64_t generate_base() {
        mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<uint64_t> rand(1, mod - 1);
        return rand(mt);
    }

    inline uint64_t mul(uint64_t a, uint64_t b) const {
        return (uint64_t)((__uint128_t)a * b % mod);
    }

    RollingHash() {}
    RollingHash(const string &s, uint64_t b = 0) {
        if (b == 0) b = generate_base();
        base = b;
        ll n = s.size();
        hash.assign(n + 1, 0);
        power.assign(n + 1, 1);
        rep(i, 0, n) {
            hash[i + 1] = (mul(hash[i], base) + s[i]) % mod;
            power[i + 1] = mul(power[i], base);
        }
    }

    uint64_t query(ll l, ll r) const {
        uint64_t res = hash[r] + mod - mul(hash[l], power[r - l]);
        if (res >= mod) res -= mod;
        return res;
    }

    uint64_t combine(uint64_t h1, uint64_t h2, ll len2) const {
        uint64_t res = mul(h1, power[len2]) + h2;
        if (res >= mod) res -= mod;
        return res;
    }
};



/* 
 * メソッド仕様一覧:
 * (0-indexed)
 * 
 * - RollingHash rh(s);
 *   概要  : 文字列 s のローリングハッシュを構築する。(基数はハック防止のため自動ランダム生成)
 *   計算量: O(|s|)
 * 
 * - rh.query(l, r);
 *   概要  : s の半開区間 [l, r) のハッシュ値を O(1) で返す。
 *   計算量: O(1)
 * 
 * - rh.combine(h1, h2, len2);
 *   概要  : 2つの部分文字列のハッシュ h1 と h2 (長さlen2) をくっつけた場合の
 *           新しいハッシュ値を O(1) で計算する。
 *   計算量: O(1)
 * 
 * ※注意※
 * 複数の文字列 (s と t など) の部分文字列同士を比較したい場合は、
 * RollingHash rh_t(t, rh_s.base); のように、「必ず同じ基数 (base)」を使って構築すること。
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例1: 部分文字列の一致判定
    // ====================================================
    string s = "abacaba";
    RollingHash rh(s);

    cout << "--- 部分文字列の一致判定 ---" << '\n';
    if (rh.query(0, 3) == rh.query(4, 7)) {
        cout << "s[0:3] と s[4:7] は一致します！\n";
    }

    // ====================================================
    // 使用例2: O(1) 回文判定
    // ====================================================
    string t = "level";
    string rev_t = t;
    reverse(all(rev_t));
    
    // 比較対象は必ず base を合わせる
    RollingHash rh1(t);
    RollingHash rh2(rev_t, rh1.base);

    ll n = t.size();
    auto is_palindrome = [&](ll l, ll r) -> bool {
        uint64_t h_normal = rh1.query(l, r);
        uint64_t h_reverse = rh2.query(n - r, n - l);
        return h_normal == h_reverse;
    };

    cout << "\n--- O(1) 回文判定 ---" << '\n';
    cout << "t全体 (level) は回文か？: " << (is_palindrome(0, 5) ? "Yes" : "No") << '\n';
    cout << "t[0:3) (lev)  は回文か？: " << (is_palindrome(0, 3) ? "Yes" : "No") << '\n';
    cout << "t[1:4) (eve)  は回文か？: " << (is_palindrome(1, 4) ? "Yes" : "No") << '\n';

}