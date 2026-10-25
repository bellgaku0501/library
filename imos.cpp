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


template <typename T = ll>
struct Imos {
    int n;
    vector<T> v;
    Imos(int n) : n(n), v(n + 1, 0) {}
    
    // 半開区間 [l, r) に val を加算
    void add(int l, int r, T val = 1) {
        if (l < 0) l = 0;
        if (r > n) r = n;
        if (l >= r) return;
        v[l] += val;
        v[r] -= val;
    }
    
    // 全ての加算クエリが終わった後に1回だけ呼んで構築する
    void build() {
        rep(i, 0, n) v[i + 1] += v[i];
    }
    
    T get(int i) { return v[i]; }
    
    vector<T> get_vec() { return vector<T>(v.begin(), v.begin() + n); }
};


template <typename T = ll>
struct Imos2D {
    int h, w;
    vector<vector<T>> v;
    Imos2D(int h, int w) : h(h), w(w), v(h + 1, vector<T>(w + 1, 0)) {}
    
    // 2次元半開区間 [y1, y2) × [x1, x2) に val を加算
    void add(int y1, int x1, int y2, int x2, T val = 1) {
        if (y1 < 0) y1 = 0;
        if (y2 > h) y2 = h;
        if (x1 < 0) x1 = 0;
        if (x2 > w) x2 = w;
        if (y1 >= y2 || x1 >= x2) return;
        
        v[y1][x1] += val;
        v[y1][x2] -= val;
        v[y2][x1] -= val;
        v[y2][x2] += val;
    }
    
    // 全ての加算クエリが終わった後に1回だけ呼んで構築する
    void build() {
        rep(i, 0, h + 1) rep(j, 0, w) v[i][j + 1] += v[i][j]; // 横方向の累積和
        rep(j, 0, w + 1) rep(i, 0, h) v[i + 1][j] += v[i][j]; // 縦方向の累積和
    }
    
    T get(int y, int x) { return v[y][x]; }
    
    vector<vector<T>> get_vec() {
        vector<vector<T>> res(h, vector<T>(w));
        rep(i, 0, h) rep(j, 0, w) res[i][j] = v[i][j];
        return res;
    }
};


/* 
 * メソッド仕様一覧:
 * (0-indexed)
 * 
 * - Imos<ll> im(n);
 *   概要  : 長さ n の1次元いもす法配列を構築。サイズは内部的に n+1 取られる。
 * 
 * - im.add(l, r, val = 1);
 *   概要  : [l, r) の範囲に val を足す。区間は半開区間（rは含まれない）であることに注意。
 *           閉区間 [l, r] に足したい場合は im.add(l, r + 1, val) とする。
 * 
 * - Imos2D<ll> im2(h, w);
 *   概要  : h × w の2次元いもす法配列を構築。
 * 
 * - im2.add(y1, x1, y2, x2, val = 1);
 *   概要  : y方向 [y1, y2), x方向 [x1, x2) の矩形領域に val を足す。
 * 
 * - im.build(); / im2.build();
 *   概要  : 累積和をとって最終的な配列の値を確定させる。計算量 O(N) または O(HW)。
 * 
 * - im.get(i); / im2.get(y, x);
 *   概要  : build() 後の特定の座標の値を O(1) で返す。
 * 
 * - im.get_vec(); / im2.get_vec();
 *   概要  : build() 後の結果を、余分な番兵マスを取り除いた通常の vector として返す。
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例1: 1次元いもす法（イベントの重なりを数える）
    // ====================================================
    // 問題: 時刻 0〜10 の間に、3人の客が [1, 5), [2, 8), [4, 6) で滞在する。
    // 各時刻の滞在人数を求めよ。
    
    Imos<ll> im(10);
    im.add(1, 5);
    im.add(2, 8);
    im.add(4, 6);
    im.build();
    
    cout << "--- 1次元いもす法 ---" << '\n';
    rep(i, 0, 10) cout << "時刻" << i << ": " << im.get(i) << "人\n";
    // 0: 0人, 1: 1人, 2: 2人, 3: 2人, 4: 3人, 5: 2人...


    // ====================================================
    // 使用例2: 2次元いもす法（領域の塗りつぶし）
    // ====================================================
    // 問題: 4x4 のグリッドに、以下の矩形の紙を置く。各マスの紙の重なり枚数は？
    // 紙1: 左上(1, 1) から 右下(3, 3) を含むように置く。※閉区間 [1, 3] なので半開区間では [1, 4)
    // 紙2: 左上(2, 0) から 右下(3, 2) を含むように置く。※半開区間では [2, 4) x [0, 3)
    
    Imos2D<ll> im2(4, 4);
    
    // 閉区間 [y1, y2] を 半開区間 [y1, y2+1) として渡す
    im2.add(1, 1, 3 + 1, 3 + 1); // 紙1
    im2.add(2, 0, 3 + 1, 2 + 1); // 紙2
    im2.build();
    
    cout << "\n--- 2次元いもす法 ---" << '\n';
    vvl res = im2.get_vec();
    rep(i, 0, 4) {
        rep(j, 0, 4) cout << res[i][j] << " ";
        cout << '\n';
    }
    // 出力:
    // 0 0 0 0 
    // 0 1 1 1 
    // 1 2 2 1 
    // 1 2 2 1 

    return 0;
}