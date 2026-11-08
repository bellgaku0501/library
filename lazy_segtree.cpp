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



template <typename S, typename F, class D> S lseg_op(S a, S b) { return D::op(a, b); }
template <typename S, typename F, class D> S lseg_e() { return D::e(); }
template <typename S, typename F, class D> S lseg_mapping(F f, S x) { return D::mapping(f, x); }
template <typename S, typename F, class D> F lseg_composition(F f, F g) { return D::composition(f, g); }
template <typename S, typename F, class D> F lseg_id() { return D::id(); }

template <typename S, typename F, class D>
struct LazySegBase : lazy_segtree<S, lseg_op<S, F, D>, lseg_e<S, F, D>, F, lseg_mapping<S, F, D>, lseg_composition<S, F, D>, lseg_id<S, F, D>> {
    using lazy_segtree<S, lseg_op<S, F, D>, lseg_e<S, F, D>, F, lseg_mapping<S, F, D>, lseg_composition<S, F, D>, lseg_id<S, F, D>>::lazy_segtree;
    S operator[](int p) { return this->get(p); }
};

template <typename T> struct LazySegAddMin : LazySegBase<T, T, LazySegAddMin<T>> {
    using LazySegBase<T, T, LazySegAddMin<T>>::LazySegBase;
    static T op(T a, T b) { return min(a, b); }
    static T e() { return numeric_limits<T>::max(); }
    static T mapping(T f, T x) { return x + f; }
    static T composition(T f, T g) { return f + g; }
    static T id() { return T(0); }
};

template <typename T> struct LazySegAddMax : LazySegBase<T, T, LazySegAddMax<T>> {
    using LazySegBase<T, T, LazySegAddMax<T>>::LazySegBase;
    static T op(T a, T b) { return max(a, b); }
    static T e() { return numeric_limits<T>::lowest(); }
    static T mapping(T f, T x) { return x + f; }
    static T composition(T f, T g) { return f + g; }
    static T id() { return T(0); }
};

template <typename T> struct LazySegUpdateMin : LazySegBase<T, T, LazySegUpdateMin<T>> {
    using LazySegBase<T, T, LazySegUpdateMin<T>>::LazySegBase;
    static T op(T a, T b) { return min(a, b); }
    static T e() { return numeric_limits<T>::max(); }
    static T mapping(T f, T x) { return f == id() ? x : f; }
    static T composition(T f, T g) { return f == id() ? g : f; }
    static T id() { return numeric_limits<T>::max(); }
};

template <typename T> struct LazySegUpdateMax : LazySegBase<T, T, LazySegUpdateMax<T>> {
    using LazySegBase<T, T, LazySegUpdateMax<T>>::LazySegBase;
    static T op(T a, T b) { return max(a, b); }
    static T e() { return numeric_limits<T>::lowest(); }
    static T mapping(T f, T x) { return f == id() ? x : f; }
    static T composition(T f, T g) { return f == id() ? g : f; }
    static T id() { return numeric_limits<T>::max(); }
};

template <typename T> struct LazySegAddSum : LazySegBase<pair<T, ll>, T, LazySegAddSum<T>> {
    using S = pair<T, ll>; using F = T; using Base = LazySegBase<S, F, LazySegAddSum<T>>;
    LazySegAddSum() : Base() {}
    LazySegAddSum(int n) { std::vector<S> init(n, {0, 1}); *this = LazySegAddSum(init); }
    LazySegAddSum(const std::vector<T>& v) {
        std::vector<S> init(v.size()); rep(i, 0, v.size()) init[i] = {v[i], 1};
        *this = LazySegAddSum(init);
    }
    LazySegAddSum(const std::vector<S>& v) : Base(v) {}
    static S op(S a, S b) { return {a.first + b.first, a.second + b.second}; }
    static S e() { return {0, 0}; }
    static S mapping(F f, S x) { return {x.first + f * x.second, x.second}; }
    static F composition(F f, F g) { return f + g; }
    static F id() { return T(0); }
};

template <typename T> struct LazySegUpdateSum : LazySegBase<pair<T, ll>, T, LazySegUpdateSum<T>> {
    using S = pair<T, ll>; using F = T; using Base = LazySegBase<S, F, LazySegUpdateSum<T>>;
    LazySegUpdateSum() : Base() {}
    LazySegUpdateSum(int n) { std::vector<S> init(n, {0, 1}); *this = LazySegUpdateSum(init); }
    LazySegUpdateSum(const std::vector<T>& v) {
        std::vector<S> init(v.size()); rep(i, 0, v.size()) init[i] = {v[i], 1};
        *this = LazySegUpdateSum(init);
    }
    LazySegUpdateSum(const std::vector<S>& v) : Base(v) {}
    static S op(S a, S b) { return {a.first + b.first, a.second + b.second}; }
    static S e() { return {0, 0}; }
    static S mapping(F f, S x) { return f == id() ? x : S{f * x.second, x.second}; }
    static F composition(F f, F g) { return f == id() ? g : f; }
    static F id() { return numeric_limits<T>::max(); }
};



/* 
 * メソッド仕様一覧 (計算量は特記なき限りすべて O(log N)):
 * 
 * - struct LazySegAddMin, LazySegAddMax, LazySegUpdateMin, LazySegUpdateMax
 * - struct LazySegAddSum, LazySegUpdateSum
 *   概要: 配列の「区間に対する加算・更新」と「区間クエリ」を高速に処理する。
 *         ※ Sum系は区間長を自動で管理するため、初期化時に vector<ll> をそのまま渡せば完了する。
 * 
 *   [区間更新・点更新]
 *     - apply(l, r, f) : 半開区間 [l, r) の要素すべてに作用素 f (加算値や更新値) を適用する。
 *     - apply(p, f)    : p 番目の要素のみに作用素 f を適用する。
 *     - set(p, x)      : p 番目の要素を直接 x に上書きする。
 *                        ※ 遅延評価を強制解決させるため重い。通常は apply(p, x) を推奨。
 *                        ※ Sum系で set を使う場合は {x, 1} のペアを渡す必要がある。
 * 
 *   [区間クエリ・点取得・二分探索]
 *     - seg[p]         : p 番目の要素の値を取得する。(Sum系は {和, 1} のペアが返る) 
 *     - prod(l, r)     : 半開区間 [l, r) の演算結果を取得する。(Sum系は {和, 区間長} が返る)
 *     - all_prod()     : 全区間 [0, N) の演算結果を取得する。(O(1))
 *     - max_right      : 左端を固定し、条件を満たす最大の右端を探索する。
 *     - min_left       : 右端を固定し、条件を満たす最小の左端を探索する。
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vl A = {10, 20, 30, 40, 50};
    
    // ====================================================
    // 1. 【区間加算・区間和】 (LazySegAddSum)
    // ====================================================
    LazySegAddSum<ll> seg_sum(A);
    
    // [1, 4) に 5 を加算 -> {10, 25, 35, 45, 50}
    seg_sum.apply(1, 4, 5); 
    
    // 区間 [1, 4) の和を取得
    // ※ Sum系は {和, 区間長} の pair が返るため .first で取り出す
    cout << "AddSum prod[1, 4) : " << seg_sum.prod(1, 4).first << '\n'; // 25+35+45 = 105
    
    // 点取得
    cout << "AddSum seg_sum[2] : " << seg_sum[2].first << '\n'; // 35


    // ====================================================
    // 2. 【区間更新・区間最小値】 (LazySegUpdateMin)
    // ====================================================
    LazySegUpdateMin<ll> seg_min(A);
    
    // [2, 5) を 15 に更新 -> {10, 20, 15, 15, 15}
    seg_min.apply(2, 5, 15);
    
    // 区間 [1, 4) の最小値を取得
    // ※ Min系、Max系は値がそのまま返る
    cout << "UpdateMin prod[1, 4) : " << seg_min.prod(1, 4) << '\n'; // min(20, 15, 15) = 15
    
    // 点取得
    cout << "UpdateMin seg_min[4] : " << seg_min[4] << '\n'; // 15


    // ====================================================
    // 3. 【区間加算・区間最大値】 (LazySegAddMax)
    // ====================================================
    LazySegAddMax<ll> seg_max(A);
    
    // [0, 3) に 100 を加算 -> {110, 120, 130, 40, 50}
    seg_max.apply(0, 3, 100);
    
    cout << "AddMax all_prod : " << seg_max.all_prod() << '\n'; // 130

    return 0;
}