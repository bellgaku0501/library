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


template <typename T>
struct Compress {
    vector<T> xs;
    Compress() {}
    Compress(const vector<T>& v) {
        xs = v;
        build();
    }
    void add(T x) {
        xs.push_back(x);
    }
    void build() {
        sort(all(xs));
        xs.erase(unique(all(xs)), xs.end());
    }
    int get(T x) const {
        return lower_bound(all(xs), x) - xs.begin();
    }
    T inv(int i) const {
        return xs[i];
    }
    int size() const {
        return xs.size();
    }
    vector<int> get_vec(const vector<T>& v) const {
        vector<int> res(v.size());
        rep(i, 0, v.size()) res[i] = get(v[i]);
        return res;
    }
};


/* 
 * メソッド仕様一覧:
 * (0-indexed)
 * 
 * - Compress<ll> comp(A);
 *   概要  : 配列 A をもとに座標圧縮を構築する（重複削除とソートが行われる）。
 *   計算量: O(N log N)
 * 
 * - comp.add(x); 
 *   概要  : 構築前に値を動的に追加する。クエリを先読みして追加する際に使う。
 *           ※ 追加後は必ず comp.build() を呼ぶこと。
 *   計算量: O(1)
 * 
 * - comp.build();
 *   概要  : add() で追加した値をもとに圧縮配列を構築する。
 *   計算量: O(N log N)
 * 
 * - comp.get(x);
 *   概要  : 元の値 x が圧縮後に何番目(0-indexed)になるかを返す。
 *   計算量: O(log N)
 * 
 * - comp.inv(i);
 *   概要  : 圧縮後のインデックス i が元のどんな値だったかを返す（逆変換）。
 *   計算量: O(1)
 * 
 * - comp.size();
 *   概要  : 圧縮後の要素の種類数（一意な値の数）を返す。セグメント木の初期化サイズなどに使う。
 *   計算量: O(1)
 * 
 * - vector<int> C = comp.get_vec(A);
 *   概要  : [独自拡張] 元の配列 A をすべて圧縮後の値に置き換えた新しい配列を返す。
 *   計算量: O(N log N)
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例1: 既存の配列を一括で圧縮する
    // ====================================================
    vl A = {1000000000, 10, 500, 10, -300};
    
    Compress<ll> comp(A);
    vector<int> C = comp.get_vec(A);

    cout << "--- 一括圧縮 ---" << '\n';
    cout << "圧縮後の要素の種類数: " << comp.size() << '\n';
    
    rep(i, 0, A.size()) {
        cout << A[i] << " -> " << C[i] << '\n';
    }
    // 出力:
    // 1000000000 -> 3
    // 10 -> 1
    // 500 -> 2
    // 10 -> 1
    // -300 -> 0


    // ====================================================
    // 使用例2: クエリを先読みして動的に追加し、後から構築する
    // ====================================================
    Compress<ll> dynamic_comp;
    
    // イベントやクエリなどで登場する座標を追加していく
    dynamic_comp.add(55555);
    dynamic_comp.add(11111);
    dynamic_comp.add(99999);
    
    // 全ての追加が終わったら構築
    dynamic_comp.build();

    cout << "\n--- 動的追加と逆変換 ---" << '\n';
    // 値 55555 のインデックスを取得
    int idx = dynamic_comp.get(55555);
    cout << "55555 のインデックス: " << idx << '\n';
    
    // インデックスからの逆変換
    cout << "インデックス " << idx << " の元の値: " << dynamic_comp.inv(idx) << '\n';

    return 0;
}