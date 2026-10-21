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

template <typename T, typename D> T seg_op(T a, T b) { return D::op(a, b); }
template <typename T, typename D> T seg_e() { return D::e(); }

template <typename T, typename D>
struct SegBase : segtree<T, seg_op<T, D>, seg_e<T, D>> {
    using segtree<T, seg_op<T, D>, seg_e<T, D>>::segtree;
    T operator[](int p) const { return this->get(p); }
    void add(int p, T x) { this->set(p, this->get(p) + x); }
    void mul(int p, T x) { this->set(p, this->get(p) * x); }
    void chmax(int p, T x) { if (x > this->get(p)) this->set(p, x); }
    void chmin(int p, T x) { if (x < this->get(p)) this->set(p, x); }
    void add_xor(int p, T x) { this->set(p, this->get(p) ^ x); }
    void add_or(int p, T x) { this->set(p, this->get(p) | x); }
    void add_and(int p, T x) { this->set(p, this->get(p) & x); }
};

template <typename T>
struct SegMax : SegBase<T, SegMax<T>> {
    using SegBase<T, SegMax<T>>::SegBase;
    static T op(T a, T b) { return max(a, b); }
    static T e() { return numeric_limits<T>::lowest(); }
};

template <typename T>
struct SegMin : SegBase<T, SegMin<T>> {
    using SegBase<T, SegMin<T>>::SegBase;
    static T op(T a, T b) { return min(a, b); }
    static T e() { return numeric_limits<T>::max(); }
};

template <typename T>
struct SegSum : SegBase<T, SegSum<T>> {
    using SegBase<T, SegSum<T>>::SegBase;
    static T op(T a, T b) { return a + b; }
    static T e() { return T(0); }
};

template <typename T>
struct SegMul : SegBase<T, SegMul<T>> {
    using SegBase<T, SegMul<T>>::SegBase;
    static T op(T a, T b) { return a * b; }
    static T e() { return T(1); }
};

template <typename T>
struct SegXor : SegBase<T, SegXor<T>> {
    using SegBase<T, SegXor<T>>::SegBase;
    static T op(T a, T b) { return a ^ b; }
    static T e() { return T(0); }
};

template <typename T>
struct SegOr : SegBase<T, SegOr<T>> {
    using SegBase<T, SegOr<T>>::SegBase;
    static T op(T a, T b) { return a | b; }
    static T e() { return T(0); }
};

template <typename T>
struct SegAnd : SegBase<T, SegAnd<T>> {
    using SegBase<T, SegAnd<T>>::SegBase;
    static T op(T a, T b) { return a & b; }
    static T e() { return ~T(0); }
};

template <typename T>
struct SegGcd : SegBase<T, SegGcd<T>> {
    using SegBase<T, SegGcd<T>>::SegBase;
    static T op(T a, T b) { return gcd(a, b); }
    static T e() { return T(0); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 5;
    vl A = {10, 20, 30, 40, 50};

    // ====================================================
    // 1. コンストラクタ (構築): O(N)
    // ====================================================
    
    // (A) 要素数 N で初期化（初期値はすべて単位元 e() になる）: O(N)
    SegSum<ll> seg_empty(N);

    // (B) 既存の配列 A から構築: O(N)
    SegSum<ll> seg(A);


    // ====================================================
    // 2. 点更新・便利更新関数: O(log N)
    // ====================================================

    // [ACL標準] p番目の要素を x に上書きする: O(log N)
    seg.set(0, 15); // A[0] を 10 -> 15 に変更 (配列は {15, 20, 30, 40, 50})

    // [追加機能] p番目の要素に x を加算する: O(log N)
    seg.add(1, 5);  // A[1] に 5 を足して 25 に変更 (配列は {15, 25, 30, 40, 50})
    // ※ 他にも chmax, chmin, mul, add_xor, add_or, add_and が O(log N) で使用可能


    // ====================================================
    // 3. 点取得: O(1)
    // ====================================================

    // [追加機能] 配列ライクなアクセス: O(1)
    cout << "seg[1]: " << seg[1] << "\n";       // 出力: 25

    // [ACL標準] get関数によるアクセス: O(1)
    cout << "seg.get(1): " << seg.get(1) << "\n"; // 出力: 25


    // ====================================================
    // 4. 区間クエリ: O(log N) / 全区間クエリ: O(1)
    // ====================================================

    // [ACL標準] 半開区間 [l, r) の集計結果を取得: O(log N)
    // ※ l == r のときは単位元 e() が返る
    cout << "prod [1, 4): " << seg.prod(1, 4) << "\n"; // A[1]+A[2]+A[3] = 25+30+40 = 95

    // [ACL標準] 全区間 [0, N) の集計結果を取得: O(1)
    cout << "all_prod: " << seg.all_prod() << "\n";    // 15+25+30+40+50 = 160


    // ====================================================
    // 5. セグ木上の二分探索: O(log N)
    // ====================================================

    // [ACL標準] max_right(l, f): O(log N)
    // 左端 l を固定し、区間 [l, r) の集計結果が「条件 f を満たす最大の r」を返す。
    // 例: 左端 l = 1 からスタートして、区間和が 60 以下である最大の r を求める
    int r = seg.max_right(1, [](ll x) {
        return x <= 60; // 単位元 e() に対して必ず true になる条件を書く
    });
    cout << "max_right: " << r << "\n"; // 出力: 3 ([1, 3)の和は55、[1, 4)の和は95なので3)

    // [ACL標準] min_left(r, f): O(log N)
    // 右端 r を固定し、区間 [l, r) の集計結果が「条件 f を満たす最小の l」を返す。
    // 例: 右端 r = 4 から左に伸ばして、区間和が 70 以下である最小の l を求める
    int l = seg.min_left(4, [](ll x) {
        return x <= 70; // 単位元 e() に対して必ず true になる条件を書く
    });
    cout << "min_left: " << l << "\n";  // 出力: 2 ([2, 4)の和は70、[1, 4)の和は95なので2)

}