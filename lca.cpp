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


struct LCA {
    ll n, log_size;
    vvl G;
    vvl parent; // parent[k][v] := 頂点 v から 2^k 回親をたどった頂点
    vl depth;
    bool built;

    LCA(ll n) : n(n), G(n), depth(n, 0), built(false) {
        log_size = 1;
        while ((1LL << log_size) < n) log_size++;
        parent.assign(log_size, vl(n, -1));
    }

    void add_edge(ll u, ll v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void build(ll root = 0) {
        built = true;
        vl dist(n, -1);
        queue<ll> q;
        q.push(root);
        dist[root] = 0;
        
        // BFSで深さと1個上の親を初期化
        while (!q.empty()) {
            ll v = q.front(); q.pop();
            for (ll u : G[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    parent[0][u] = v;
                    q.push(u);
                }
            }
        }
        depth = dist;

        // ダブリングで 2^k 個上の親を計算
        rep(k, 0, log_size - 1) {
            rep(v, 0, n) {
                if (parent[k][v] < 0) parent[k + 1][v] = -1;
                else parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    ll get(ll u, ll v) {
        if (!built) build();
        if (depth[u] < depth[v]) swap(u, v);
        
        // 1. まず深さを揃える
        rep(k, 0, log_size) {
            if ((depth[u] - depth[v]) >> k & 1) {
                u = parent[k][u];
            }
        }
        if (u == v) return u;
        
        // 2. ギリギリ共通祖先にならない場所まで同時に遡る
        for (int k = log_size - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    // [独自拡張] 2頂点間の最短距離
    ll dist(ll u, ll v) {
        if (!built) build();
        return depth[u] + depth[v] - 2 * depth[get(u, v)];
    }

    // [独自拡張] 頂点 v から k 個上の祖先を取得 (存在しない場合は -1)
    ll la(ll v, ll k) {
        if (!built) build();
        rep(i, 0, log_size) {
            if (k >> i & 1) v = parent[i][v];
            if (v == -1) break;
        }
        return v;
    }
};


/* 
 * メソッド仕様一覧:
 * (0-indexed)
 * 
 * - LCA lca(n);
 *   概要  : 頂点数 n の木として初期化する。
 * 
 * - lca.add_edge(u, v);
 *   概要  : 頂点 u, v 間に無向辺を追加する。
 * 
 * - lca.build(root = 0);
 *   概要  : root を根として木を構築し、ダブリングのテーブルを作成する。
 *           ※ 実行し忘れても、get() などを呼んだ際に自動で root=0 として構築される。
 *   計算量: O(N log N)
 * 
 * - lca.get(u, v);
 *   概要  : 頂点 u と v の最小共通祖先を返す。
 *   計算量: O(log N)
 * 
 * - lca.dist(u, v);
 *   概要  : [独自拡張] 頂点 u と v の間の最短パスに含まれる「辺の数」を返す。
 *   計算量: O(log N)
 * 
 * - lca.la(v, k);
 *   概要  : [独自拡張] 頂点 v から親方向へ k 回遡った頂点 (Level Ancestor) を返す。
 *           根を通り越してしまう（存在しない）場合は -1 を返す。
 *   計算量: O(log N)
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例:
    // 木の構造:
    //       0
    //     /   \
    //    1     2
    //   / \
    //  3   4
    //       \
    //        5
    // ====================================================
    ll n = 6;
    LCA lca(n);
    lca.add_edge(0, 1);
    lca.add_edge(0, 2);
    lca.add_edge(1, 3);
    lca.add_edge(1, 4);
    lca.add_edge(4, 5);

    lca.build(); // 根を 0 として構築

    cout << "--- 最小共通祖先 (LCA) ---" << '\n';
    cout << "頂点3と5の共通祖先: " << lca.get(3, 5) << '\n'; // 1
    cout << "頂点5と2の共通祖先: " << lca.get(5, 2) << '\n'; // 0

    cout << "\n--- 2頂点間の最短距離 ---" << '\n';
    // パス: 3 -> 1 -> 4 -> 5 (辺は3つ)
    cout << "頂点3と5の距離    : " << lca.dist(3, 5) << '\n'; // 3
    cout << "頂点4と2の距離    : " << lca.dist(4, 2) << '\n'; // 3

    cout << "\n--- K個上の祖先 (Level Ancestor) ---" << '\n';
    cout << "頂点5の2個上の祖先: " << lca.la(5, 2) << '\n'; // 1 (5->4->1)
    cout << "頂点3の3個上の祖先: " << lca.la(3, 3) << '\n'; // -1 (根より上はない)

    return 0;
}