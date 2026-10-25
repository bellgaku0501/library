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


// ====================================================
// 拡張 Union-Find (クラスカル法の内部で使用)
// ====================================================
struct UnionFind {
    ll n, comp_cnt;
    vl parent_or_size, edges;
    UnionFind(ll n) : n(n), comp_cnt(n), parent_or_size(n, -1), edges(n, 0) {}
    ll leader(ll x) {
        if (parent_or_size[x] < 0) return x;
        return parent_or_size[x] = leader(parent_or_size[x]);
    }
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
    bool same(ll x, ll y) { return leader(x) == leader(y); }
    ll size(ll x) { return -parent_or_size[leader(x)]; }
    ll edge_cnt(ll x) { return edges[leader(x)]; }
};

// ====================================================
// クラスカル法 (最小全域木)
// ====================================================
struct Kruskal {
    struct Edge {
        ll u, v, cost, id;
        // コストの昇順にソートするための比較演算子
        bool operator<(const Edge& other) const {
            return cost < other.cost;
        }
    };

    ll n;
    vector<Edge> edges;
    vector<Edge> mst_edges; // MSTに採用された辺のリスト
    ll mst_cost;            // MSTの総コスト
    bool is_connected;      // グラフ全体が連結になったかどうか

    Kruskal(ll n) : n(n), mst_cost(0), is_connected(false) {}

    // 辺の追加 (id は入力順などを記憶しておくために使う)
    void add_edge(ll u, ll v, ll cost, ll id = -1) {
        edges.push_back({u, v, cost, id});
    }

    // 最小全域木の構築 O(E log E)
    ll build() {
        sort(all(edges));
        UnionFind uf(n);
        mst_cost = 0;
        mst_edges.clear();

        for (const auto& e : edges) {
            // 閉路を作らない（まだ繋がっていない）なら辺を採用
            if (uf.merge(e.u, e.v)) {
                mst_cost += e.cost;
                mst_edges.push_back(e);
            }
        }
        
        // 全ての頂点が1つの連結成分になったかを判定 (Union-Find の機能を利用)
        is_connected = (uf.comp_cnt == 1);
        return mst_cost;
    }
};


/* 
 * メソッド仕様一覧:
 * (0-indexed)
 * 
 * - Kruskal ks(n);
 *   概要  : 頂点数 n で初期化する。
 * 
 * - ks.add_edge(u, v, cost, id = -1);
 *   概要  : 頂点 u と v の間にコスト cost の無向辺を追加する。
 *           id は「何番目の入力辺か」を記録する独自機能。
 * 
 * - ks.build();
 *   概要  : クラスカル法を実行し、最小全域木の総コストを返す。
 *   計算量: O(E log E)
 * 
 * - ks.mst_cost;
 *   概要  : build() 実行後の最小全域木の総コスト。
 * 
 * - ks.mst_edges;
 *   概要  : [独自拡張] build() 実行後、実際に採用された辺(Edge構造体)のリスト。
 *           e.id を見ることで、「どの辺が使われたか」を復元できる。
 * 
 * - ks.is_connected;
 *   概要  : [独自拡張] build() 実行後、グラフ全体が1つの木になったか(連結か)を返す。
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例:
    // ====================================================
    ll n = 4;
    Kruskal ks(n);

    // 頂点u, 頂点v, コスト, 辺のID(0番目, 1番目...)
    ks.add_edge(0, 1, 10, 1);
    ks.add_edge(1, 2, 20, 2);
    ks.add_edge(2, 3, 30, 3);
    ks.add_edge(0, 3, 5,  4); // コスト5の辺が一番安いので採用される
    ks.add_edge(0, 2, 100, 5); // 高いので採用されない

    // クラスカル法の実行
    ll total_cost = ks.build();

    cout << "--- 最小全域木 (Kruskal) ---" << '\n';
    if (ks.is_connected) {
        cout << "全ての頂点を繋ぐことができます。\n";
        cout << "最小総コスト: " << total_cost << "\n\n";
        
        cout << "[採用された辺のリスト]" << '\n';
        for (const auto& e : ks.mst_edges) {
            cout << "辺ID: " << e.id << " (頂点 " << e.u << " - " << e.v << ", コスト " << e.cost << ")\n";
        }
    } else {
        cout << "グラフは非連結です（全ての頂点を繋ぐことはできません）。\n";
    }

    return 0;
}