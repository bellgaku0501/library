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
    vector<T> v;
    Compress() {}
    Compress(const vector<T>& a) : v(a) { build(); }
    void add(T x) { v.push_back(x); }
    void add(const vector<T>& a) { v.insert(v.end(), all(a)); }
    void build() {
        sort(all(v));
        v.erase(unique(all(v)), v.end());
    }
    int id(T x) const { return lower_bound(all(v), x) - v.begin(); }
    vector<int> id(const vector<T>& a) const {
        vector<int> res(a.size());
        rep(i, 0, a.size()) res[i] = id(a[i]);
        return res;
    }
    T val(int i) const { return v[i]; }
    int size() const { return v.size(); }
};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vl A = {1000000000, 10, 10, 500, 1000000000, -5};
    // N: 扱う要素の総数, K: 重複排除後の種類数

    //【パターン1】配列Aだけをサクッと圧縮したい場合
    // 配列を渡すと O(N log N) で自動的に build() まで完了する
    Compress<ll> comp1(A);

    //【パターン2】複数の配列やクエリをまとめて追加してから圧縮したい場合
    Compress<ll> comp2;
    comp2.add(A);       // 複数要素の追加: O(N)
    comp2.add(200);     // 単一要素の追加: 均しO(1)
    comp2.build();      // 構築: O(N log N) (※このパターンの場合は必ず呼ぶ！)

    // --- 以下、計算量は comp1 (構築済み) を用いた場合 ---

    // 圧縮された配列の取得: O(N log K)
    vector<int> B = comp1.id(A);
    
    cout << "Compressed array: ";
    rep(i, 0, B.size()) cout << B[i] << " "; // 出力: 3 1 1 2 3 0
    cout << "\n";

    // 圧縮後の値の取得: O(log K)
    int compressed_val = comp1.id(500); 
    cout << "ID of 500: " << compressed_val << "\n"; // 出力: 2

    // 元の値の復元: O(1)
    ll original_val = comp1.val(3);
    cout << "Original of ID 3: " << original_val << "\n"; // 出力: 1000000000

    // 種類数の取得: O(1)
    cout << "Unique sizes: " << comp1.size() << "\n"; // 出力: 4
    
}