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



template <typename T = char>
struct RLE : vector<pair<T, ll>> {
    RLE() {}
    RLE(const vector<T>& a) { add(a); }
    RLE(const string& s) { add(s); }
    void add(T x, ll c = 1) {
        if (c == 0) return;
        if (!this->empty() && this->back().first == x) this->back().second += c;
        else this->emplace_back(x, c);
    }
    void add(const vector<T>& a) { for (const auto& x : a) add(x); }
    void add(const string& s) { for (char c : s) add(c); }
};



/* 
 * メソッド仕様一覧:
 * ※ vector<pair<T, ll>> を継承しているため、.size(), .back(), [], range-based for などの標準機能がそのまま使えます。
 * 
 * - RLE<char> rle(S); / RLE<ll> rle(A);
 *   概要  : 文字列 S や配列 A を用いてランレングス圧縮を構築する。
 *   計算量: O(N) (N は S や A の長さ)
 * 
 * - rle.add(x, c);
 *   概要  : 要素 x を c 個末尾に追加する（デフォルト c=1）。直前の要素と同じなら自動で結合される。
 *   計算量: 均し O(1)
 * 
 * - rle.add(A); / rle.add(S);
 *   概要  : 別の配列 A や文字列 S を末尾に追加する。境界で同じ要素が連続すれば自動で結合される。
 *   計算量: O(M) (M は追加する A や S の長さ)
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例:
    // ====================================================

    // 【1】文字列 (string) の圧縮
    string S = "aaabbcdddd";
    RLE<> rle_s(S); // T = char がデフォルト

    cout << "--- 文字列のRLE ---" << '\n';
    cout << "Blocks count: " << rle_s.size() << '\n';
    rep(i, 0, rle_s.size()) {
        cout << rle_s[i].first << " : " << rle_s[i].second << '\n';
    }
    // 出力:
    // a : 3
    // b : 2
    // c : 1
    // d : 4


    // 【2】数値配列 (vector) の圧縮と動的追加
    vl A = {10, 10, 20, 30, 30, 30};
    RLE<ll> rle_a(A);

    // 要素を動的に追加（直前の 30 と自動結合される）
    rle_a.add(30);
    // 大きな個数をまとめて追加
    rle_a.add(50, 1000000000LL);
    // 別の配列を追加（先頭の 50 は直前の 50 と自動結合される）
    vl B = {50, 50, 10};
    rle_a.add(B);

    cout << "\n--- 配列のRLE（追加後） ---" << '\n';
    for (auto [val, cnt] : rle_a) {
        cout << val << " x " << cnt << '\n';
    }
    // 出力:
    // 10 x 2
    // 20 x 1
    // 30 x 4
    // 50 x 1000000002
    // 10 x 1

    cout << "\nLast block: " << rle_a.back().first << " x " << rle_a.back().second << '\n';
    // 出力: Last block: 10 x 1

    return 0;
}