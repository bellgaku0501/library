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



struct ZeroOneBFS {
    ll n;
    vector<vector<pl>> G;
    vl dist, prev;
    ZeroOneBFS(ll n) : n(n), G(n) {}
    void add_edge(ll u, ll v, ll cost) { G[u].push_back({v, cost}); }
    void build(ll start) {
        dist.assign(n, INF);
        prev.assign(n, -1);
        deque<ll> dq;
        dist[start] = 0;
        dq.push_back(start);
        while (!dq.empty()) {
            ll u = dq.front();
            dq.pop_front();
            for (auto& [v, cost] : G[u]) {
                if (dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    prev[v] = u;
                    if (cost == 0) dq.push_front(v);
                    else dq.push_back(v);
                }
            }
        }
    }
    vl get_path(ll goal) {
        vl path;
        if (dist[goal] == INF) return path;
        for (ll cur = goal; cur != -1; cur = prev[cur]) path.push_back(cur);
        reverse(all(path));
        return path;
    }
};



/* 
 * メソッド仕様一覧:
 * (0-indexed)
 * 
 * - ZeroOneBFS bfs(n);
 *   概要  : 頂点数 n で初期化する。
 *   計算量: O(n)
 * 
 * - bfs.add_edge(u, v, cost);
 *   概要  : 頂点 u から v へコスト cost (0 または 1 のみ) の有向辺を追加する。
 *           ※ 無向グラフの場合は u->v と v->u の両方を手動で追加する。
 *   計算量: O(1)
 * 
 * - bfs.build(s);
 *   概要  : s を始点として、全頂点への最短距離 (dist) と経路復元用配列 (prev) を構築する。
 *   計算量: O(V + E) (ダイクストラより高速)
 * 
 * - bfs.dist[v];
 *   概要  : s->v の最短距離
 *   計算量: O(1)
 * 
 * - vl path = bfs.get_path(goal);
 *   概要  : build() 実行後、始点から goal までの最短経路上の頂点列を取得する。到達不可時は空配列。
 *   計算量: O(V)
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例:
    // 頂点数 5、辺のコストが 0 または 1 のみの無向グラフ
    // ====================================================

    ll n = 5;
    ZeroOneBFS bfs(n);

    // 0-1 (cost 1)
    bfs.add_edge(0, 1, 1); bfs.add_edge(1, 0, 1);
    // 0-2 (cost 0)
    bfs.add_edge(0, 2, 0); bfs.add_edge(2, 0, 0);
    // 1-3 (cost 1)
    bfs.add_edge(1, 3, 1); bfs.add_edge(3, 1, 1);
    // 2-3 (cost 1)
    bfs.add_edge(2, 3, 1); bfs.add_edge(3, 2, 1);
    // 3-4 (cost 0)
    bfs.add_edge(3, 4, 0); bfs.add_edge(4, 3, 0);
    
    bfs.build(0);

    cout << "--- 頂点0からの最短距離 ---" << '\n';
    rep(i, 0, n) {
        if (bfs.dist[i] == INF) cout << "0 -> " << i << " : INF\n";
        else cout << "0 -> " << i << " : " << bfs.dist[i] << '\n';
    }
    // 出力:
    // 0 -> 0 : 0
    // 0 -> 1 : 1
    // 0 -> 2 : 0
    // 0 -> 3 : 1
    // 0 -> 4 : 1

    cout << "\n--- 頂点0から4への最短経路 ---" << '\n';
    vl path = bfs.get_path(4);

    rep(i, 0, path.size()) {
        cout << path[i] << (i == (int)path.size() - 1 ? "" : " -> ");
    }
    cout << '\n';
    // 出力:
    // 0 -> 2 -> 3 -> 4
    
}