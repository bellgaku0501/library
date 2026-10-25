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


struct UnionFind {
    ll n, comp_cnt;
    vl parent_or_size, edges;
    UnionFind(ll n) : n(n), comp_cnt(n), parent_or_size(n, -1), edges(n, 0) {}
    
    // [ACL互換] 代表元の取得
    ll leader(ll x) {
        if (parent_or_size[x] < 0) return x;
        return parent_or_size[x] = leader(parent_or_size[x]);
    }
    
    // [ACL互換(一部拡張)] 併合
    // ※ ACLは新しいleaderを返すが、実戦ではマージが発生したかのboolを返す方が
    //   クラスカル法などで使いやすいためbool型にしています
    bool merge(ll x, ll y) {
        ll rx = leader(x), ry = leader(y);
        if (rx == ry) { edges[rx]++; return false; }
        if (parent_or_size[rx] > parent_or_size[ry]) swap(rx, ry);
        parent_or_size[rx] += parent_or_size[ry];
        parent_or_size[ry] = rx;
        edges[rx] += edges[ry] + 1;
        comp_cnt--;
        return true;
    }
    
    // [ACL互換] 所属判定
    bool same(ll x, ll y) { return leader(x) == leader(y); }
    
    // [ACL互換] 連結成分のサイズ
    ll size(ll x) { return -parent_or_size[leader(x)]; }
    
    // [独自] 連結成分の辺の数
    ll edge_cnt(ll x) { return edges[leader(x)]; }
    
    // [ACL互換] グラフを連結成分ごとに分けた二次元配列を返す
    vvl groups() {
        vl leader_buf(n), group_size(n, 0);
        rep(i, 0, n) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vvl result(n);
        rep(i, 0, n) result[i].reserve(group_size[i]);
        rep(i, 0, n) result[leader_buf[i]].push_back(i);
        result.erase(
            remove_if(all(result), [](const vl& v) { return v.empty(); }),
            result.end()
        );
        return result;
    }
};


/* 
 * メソッド仕様一覧:
 * (0-indexed)
 * 
 * - UnionFind uf(n);
 *   概要  : 頂点数 n で初期化する。
 * 
 * - uf.merge(u, v);
 *   概要  : u と v をつなぐ。新たにつながったなら true、すでに同じ成分なら false (O(1))。
 * 
 * - uf.same(u, v);
 *   概要  : u と v が同じ成分に属するか (O(1))。
 * 
 * - uf.leader(v);
 *   概要  : v の属する成分の代表元 (O(1))。
 * 
 * - uf.size(v);
 *   概要  : v の属する成分の頂点数 (O(1))。
 * 
 * - uf.edge_cnt(v); [独自]
 *   概要  : v の属する成分の辺の数 (O(1))。
 * 
 * - uf.comp_cnt; [独自]
 *   概要  : 現在のグラフ全体の連結成分の数 (変数アクセス, O(1))。
 * 
 * - vvl g = uf.groups();
 *   概要  : 全ての連結成分をリスト化した二次元配列を取得する (O(N))。
 *           成分内の頂点はインデックスの昇順に並ぶことが保証される。
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例:
    // ACL互換の groups() と、独自機能 edge_cnt() の連携
    // ====================================================

    ll n = 6;
    UnionFind uf(n);

    uf.merge(0, 1); uf.merge(1, 2); // 成分A {0, 1, 2} (木)
    uf.merge(3, 4); uf.merge(4, 5); uf.merge(5, 3); // 成分B {3, 4, 5} (閉路あり)

    // 連結成分ごとにグループ分けして取得
    vvl g = uf.groups();

    cout << "全体の連結成分の数: " << uf.comp_cnt << "\n\n";

    // 取得したグループごとにループを回す
    for (const auto& comp : g) {
        // comp には成分に属する頂点が配列で入っている
        // comp[0] は確実にその成分に含まれる頂点なので、代表として情報を引くのに使える
        ll v = comp[0]; 
        
        cout << "頂点リスト: { ";
        for (ll x : comp) cout << x << " ";
        cout << "}\n";
        
        cout << "頂点数: " << uf.size(v) << ", 辺の数: " << uf.edge_cnt(v) << '\n';
        
        if (uf.size(v) - 1 == uf.edge_cnt(v)) {
            cout << "判定  : この成分は「木」です\n\n";
        } else {
            cout << "判定  : この成分は「木ではありません（閉路あり）」\n\n";
        }
    }

    return 0;
}