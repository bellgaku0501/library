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
template <class T> bool chmin(T& a, T b){ if(a > b){ a = b; return 1; } return 0; }
template <class T> bool chmax(T& a, T b){ if(a < b){ a = b; return 1; } return 0; }
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

template <typename T> struct SegMax : SegBase<T, SegMax<T>> {
    using SegBase<T, SegMax<T>>::SegBase;
    static T op(T a, T b) { return max(a, b); }
    static T e() { return numeric_limits<T>::lowest(); }
};

template <typename T> struct SegMin : SegBase<T, SegMin<T>> {
    using SegBase<T, SegMin<T>>::SegBase;
    static T op(T a, T b) { return min(a, b); }
    static T e() { return numeric_limits<T>::max(); }
};

template <typename T> struct SegSum : SegBase<T, SegSum<T>> {
    using SegBase<T, SegSum<T>>::SegBase;
    static T op(T a, T b) { return a + b; }
    static T e() { return T(0); }
};

template <typename T> struct SegMul : SegBase<T, SegMul<T>> {
    using SegBase<T, SegMul<T>>::SegBase;
    static T op(T a, T b) { return a * b; }
    static T e() { return T(1); }
};

template <typename T> struct SegXor : SegBase<T, SegXor<T>> {
    using SegBase<T, SegXor<T>>::SegBase;
    static T op(T a, T b) { return a ^ b; }
    static T e() { return T(0); }
};

template <typename T> struct SegOr : SegBase<T, SegOr<T>> {
    using SegBase<T, SegOr<T>>::SegBase;
    static T op(T a, T b) { return a | b; }
    static T e() { return T(0); }
};

template <typename T> struct SegAnd : SegBase<T, SegAnd<T>> {
    using SegBase<T, SegAnd<T>>::SegBase;
    static T op(T a, T b) { return a & b; }
    static T e() { return ~T(0); }
};

template <typename T> struct SegGcd : SegBase<T, SegGcd<T>> {
    using SegBase<T, SegGcd<T>>::SegBase;
    static T op(T a, T b) { return gcd(a, b); }
    static T e() { return T(0); }
};



/* 
 * メソッド仕様一覧 (計算量は特記なき限りすべて O(log N)):
 * 
 * - struct SegMax, SegMin, SegSum, SegMul, SegXor, SegOr, SegAnd, SegGcd
 *   概要: 1要素の更新と、任意の区間に対する演算（最大値・最小値・和・積・XOR・OR・AND・GCD）を
 *   高速に処理する。
 * 
 *   [点アクセス・更新]
 *     - seg[p]        : p 番目の要素の値を取得する。(O(1))
 *     - set(p, x)     : p 番目の要素を x に上書き更新する。
 *     - add(p, x)     : p 番目の要素に x を加算する (元の値 + x)。
 *     - mul(p, x)     : p 番目の要素に x を乗算する (元の値 * x)。
 *     - chmax(p, x)   : p 番目の要素を max(現在値, x) で更新する。
 *     - chmin(p, x)   : p 番目の要素を min(現在値, x) で更新する。
 *     - add_xor(p, x) : p 番目の要素と x の XOR をとり更新する (元の値 ^ x)。
 *     - add_or(p, x)  : p 番目の要素と x の OR をとり更新する (元の値 | x)。
 *     - add_and(p, x) : p 番目の要素と x の AND をとり更新する (元の値 & x)。
 * 
 *   [区間クエリ・二分探索]
 *     - prod(l, r)    : 半開区間 [l, r) の演算結果を取得する。
 *     - all_prod()    : 全区間 [0, N) の演算結果を取得する。(O(1))
 *     - max_right     : 左端を固定し、条件を満たす最大の右端を探索する。
 *     - min_left      : 右端を固定し、条件を満たす最小の左端を探索する。
 */



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vl A = {10, 20, 30, 40, 50};
    SegSum<ll> seg(A);

    // --- 1. 全ての更新・拡張メソッド ---
    seg.set(0, 15);      // set     : 10 を 15 に上書き            -> {15, 20, 30, 40, 50}
    seg.add(1, 5);       // add     : 20 に 5 を加算               -> {15, 25, 30, 40, 50}
    seg.mul(2, 2);       // mul     : 30 に 2 を乗算               -> {15, 25, 60, 40, 50}
    seg.chmax(3, 100);   // chmax   : max(40, 100) で更新          -> {15, 25, 60, 100, 50}
    seg.chmin(4, 10);    // chmin   : min(50, 10) で更新           -> {15, 25, 60, 100, 10}
    seg.add_xor(0, 3);   // add_xor : 15 ^ 3 = 12 で更新           -> {12, 25, 60, 100, 10}
    seg.add_or(1, 2);    // add_or  : 25 | 2 = 27 で更新           -> {12, 27, 60, 100, 10}
    seg.add_and(2, 62);  // add_and : 60 & 62 = 60 で更新          -> {12, 27, 60, 100, 10}

    // --- 2. 点取得メソッド ---
    cout << "seg[3] : " << seg[3] << '\n';           // 出力: 100
    cout << "seg.get(4) : " << seg.get(4) << '\n';   // 出力: 10

    // --- 3. 区間取得メソッド ---
    cout << "prod[1, 4) : " << seg.prod(1, 4) << '\n'; // 27 + 60 + 100 = 187
    cout << "all_prod : " << seg.all_prod() << '\n';   // 12 + 27 + 60 + 100 + 10 = 209

    // --- 4. セグ木上の二分探索 ---
    int r = seg.max_right(1, [](ll x) { return x <= 100; });
    cout << "max_right : " << r << '\n'; // 出力: 3
    
    int l = seg.min_left(4, [](ll x) { return x <= 150; });
    cout << "min_left : " << l << '\n';  // 出力: 3

    return 0;
}