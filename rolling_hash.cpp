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


struct RollingHash {
    static const uint64_t mod = (1ULL << 61) - 1;
    uint64_t base;
    vector<uint64_t> hash, power;

    // ハッシュ衝突対策として、実行時にランダムな基数を生成
    static inline uint64_t generate_base() {
        mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<uint64_t> rand(1, mod - 1);
        return rand(mt);
    }

    // 2^61-1 での安全な乗算 (AtCoderのGCC環境でのみ動作する __uint128_t を使用)
    inline uint64_t mul(uint64_t a, uint64_t b) const {
        return (uint64_t)((__uint128_t)a * b % mod);
    }

    RollingHash() {}
    RollingHash(const string &s, uint64_t b = 0) {
        if (b == 0) b = generate_base();
        base = b;
        int n = s.size();
        hash.assign(n + 1, 0);
        power.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            hash[i + 1] = (mul(hash[i], base) + s[i]) % mod;
            power[i + 1] = mul(power[i], base);
        }
    }

    // 半開区間 [l, r) のハッシュ値を取得
    uint64_t query(int l, int r) const {
        uint64_t res = hash[r] + mod - mul(hash[l], power[r - l]);
        if (res >= mod) res -= mod;
        return res;
    }

    // [独自拡張] ハッシュ h1 (長さ len1) と ハッシュ h2 を結合したハッシュ値を計算
    uint64_t combine(uint64_t h1, uint64_t h2, int len2) const {
        uint64_t res = mul(h1, power[len2]) + h2;
        if (res >= mod) res -= mod;
        return res;
    }
};


/* 
 * メソッド仕様一覧:
 * (0-indexed)
 * 
 * - RollingHash rh(S);
 *   概要  : 文字列 S のローリングハッシュを構築する。
 *           基数 (base) は初期化時に自動でランダム生成され、Hackを防止する。
 *   計算量: O(|S|)
 * 
 * - rh.query(l, r);
 *   概要  : S の半開区間 [l, r) のハッシュ値を O(1) で返す。
 *           ※ 異なる区間でも、このハッシュ値が一致すれば、文字列が一致していると判定できる。
 *   計算量: O(1)
 * 
 * - rh.combine(h1, h2, len2);
 *   概要  : [独自拡張] 2つの部分文字列のハッシュ h1 と h2 (長さlen2) をくっつけた場合の
 *           新しいハッシュ値を O(1) で計算する。文字列を直接繋がずに一致判定ができる。
 *   計算量: O(1)
 * 
 * ※注意※
 * 複数の文字列 (S と T など) の部分文字列同士を比較したい場合は、
 * RollingHash rhT(T, rhS.base); のように、「必ず同じ基数 (base)」を使って構築すること。
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例1: 部分文字列の一致判定
    // ====================================================
    string S = "abacaba";
    RollingHash rh(S);

    cout << "--- 部分文字列の一致判定 ---" << '\n';
    // S[0, 3) = "aba", S[4, 7) = "aba" なので一致するはず
    if (rh.query(0, 3) == rh.query(4, 7)) {
        cout << "S[0:3] と S[4:7] は一致します！\n";
    }

    // ====================================================
    // 使用例2: O(1) 回文判定（D・E問題で超頻出！）
    // ====================================================
    // 文字列 T と、それを反転させた revT の両方でローリングハッシュを作る
    string T = "level";
    string revT = T;
    reverse(all(revT));
    
    // 【重要】比較対象は必ず base を合わせる！
    RollingHash rh1(T);
    RollingHash rh2(revT, rh1.base);

    // T の区間 [l, r) が回文かどうか判定するラムダ式
    int n = T.size();
    auto is_palindrome = [&](int l, int r) -> bool {
        // 元の文字列の [l, r) のハッシュ
        uint64_t h_normal = rh1.query(l, r);
        
        // 反転した文字列における対応する区間は [n - r, n - l) になる
        uint64_t h_reverse = rh2.query(n - r, n - l);
        
        return h_normal == h_reverse;
    };

    cout << "\n--- O(1) 回文判定 ---" << '\n';
    cout << "T全体 (level) は回文か？: " << (is_palindrome(0, 5) ? "Yes" : "No") << '\n';
    cout << "T[0:3) (lev)  は回文か？: " << (is_palindrome(0, 3) ? "Yes" : "No") << '\n';
    cout << "T[1:4) (eve)  は回文か？: " << (is_palindrome(1, 4) ? "Yes" : "No") << '\n';

    return 0;
}