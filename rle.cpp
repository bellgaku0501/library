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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // N: 元の配列や文字列の長さ

    // ====================================================
    // 【パターン1】文字列 (string) を圧縮する場合
    // ====================================================
    string S = "aaabbcdddd";

    // コンストラクタに渡すだけで圧縮完了: O(N)
    // ※ rle_s 自体が vector<pair<char, ll>> として振る舞う
    RLE<> rle_s(S);

    // vector標準の .size() で塊の総数を取得: O(1)
    cout << "Blocks count: " << rle_s.size() << "\n"; // 出力: 4

    // 通常の vector<pair<char, ll>> と全く同じように .first, .second でアクセス: O(1)
    rep(i, 0, rle_s.size()) {
        cout << rle_s[i].first << " : " << rle_s[i].second << "\n";
    }
    // 出力:
    // a : 3
    // b : 2
    // c : 1
    // d : 4


    // ====================================================
    // 【パターン2】数値配列 (vl) の圧縮と、動的な追加 (.add)
    // ====================================================
    vl A = {10, 10, 20, 30, 30, 30};

    // 配列から構築: O(N)
    // (※ もし純粋な vector<pl> 型として受け取りたいだけなら、
    //  vector<pl> rle_a = RLE<ll>(A); と書くことも可能)
    RLE<ll> rle_a(A);

    // 末尾に単一要素を追加: 均し O(1)
    // ※ 直前の要素(30)と同じなので、自動的に 30 の個数が 3 -> 4 に増える
    rle_a.add(30);

    // 末尾に「要素 x を c 個まとめて」追加: 均し O(1)
    rle_a.add(50, 1000000000LL);

    // 別の配列を末尾に連結して追加: O(追加する配列の長さ)
    vl B = {50, 50, 10};
    rle_a.add(B); // 先頭の 50(2個) は直前の 50(10億個) に自動で吸収される

    // rle_a 自体が vector なので、そのまま範囲for文で回せる: O(塊の数)
    cout << "\nArray RLE result:\n";
    for (auto [val, cnt] : rle_a) {
        cout << val << " x " << cnt << "\n";
    }
    // 出力:
    // 10 x 2
    // 20 x 1
    // 30 x 4
    // 50 x 1000000002
    // 10 x 1

    // vectorの標準関数 (.back(), .pop_back() など) もすべてそのまま使える: O(1)
    cout << "Last block: " << rle_a.back().first << " x " << rle_a.back().second << "\n"; // 出力: 10 x 1

}