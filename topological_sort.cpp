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


struct TopologicalSort {
    ll n;
    vvl G;
    vl in_degree;
    vl order;
    bool is_dag;

    TopologicalSort(ll n) : n(n), G(n), in_degree(n, 0), is_dag(false) {}

    void add_edge(ll u, ll v) {
        G[u].push_back(v);
        in_degree[v]++;
    }

    // 通常のトポロジカルソート O(V + E)
    bool build() {
        order.clear();
        queue<ll> q;
        vl deg = in_degree; // 何度も実行できるようにコピーを使う
        
        rep(i, 0, n) {
            if (deg[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            ll u = q.front(); 
            q.pop();
            order.push_back(u);
            for (ll v : G[u]) {
                if (--deg[v] == 0) q.push(v);
            }
        }
        is_dag = (order.size() == (size_t)n);
        return is_dag;
    }

    // 辞書順最小のトポロジカルソート O(V log V + E)
    bool build_lex() {
        order.clear();
        priority_queue<ll, vl, greater<ll>> pq;
        vl deg = in_degree;
        
        rep(i, 0, n) {
            if (deg[i] == 0) pq.push(i);
        }

        while (!pq.empty()) {
            ll u = pq.top(); 
            pq.pop();
            order.push_back(u);
            for (ll v : G[u]) {
                if (--deg[v] == 0) pq.push(v);
            }
        }
        is_dag = (order.size() == (size_t)n);
        return is_dag;
    }
};


/* 
 * メソッド仕様一覧:
 * (0-indexed)
 * 
 * - TopologicalSort ts(n);
 *   概要  : 頂点数 n で初期化する。
 * 
 * - ts.add_edge(u, v);
 *   概要  : u から v への有向辺（u が v より先）を追加し、v の入次数を増やす。
 * 
 * - bool ok = ts.build();
 *   概要  : トポロジカルソートを実行し、結果を ts.order に格納する。
 *           グラフが DAG（閉路を持たない有向グラフ）であれば true、
 *           閉路が存在してソートしきれなかった場合は false を返す。
 * 
 * - bool ok = ts.build_lex();
 *   概要  : [独自拡張] 条件を満たす順序のうち、辞書順で最小のものを求める。
 *           queue の代わりに priority_queue を使うことで実現。
 * 
 * - ts.order;
 *   概要  : build() または build_lex() 実行後にソート結果が格納される配列。
 */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例1: 通常のソートと閉路(ループ)の検出
    // ====================================================
    ll n1 = 4;
    TopologicalSort ts1(n1);
    
    ts1.add_edge(0, 1);
    ts1.add_edge(1, 2);
    ts1.add_edge(2, 3);
    ts1.add_edge(3, 1); // 1->2->3->1 の閉路を作る

    cout << "--- 閉路検出 ---" << '\n';
    if (ts1.build()) {
        cout << "ソート成功" << '\n';
    } else {
        cout << "閉路が検出されました（矛盾あり）" << '\n';
    }
    // 出力: 閉路が検出されました（矛盾あり）


    // ====================================================
    // 使用例2: 辞書順最小のトポロジカルソート
    // ====================================================
    // 依存関係: 3より先に4、0より先に2を実行する。
    // それ以外の制約がない場合、できるだけ若い番号を先に実行したい。
    ll n2 = 5;
    TopologicalSort ts2(n2);
    
    ts2.add_edge(3, 4);
    ts2.add_edge(0, 2);

    cout << "\n--- 辞書順最小のソート ---" << '\n';
    if (ts2.build_lex()) {
        rep(i, 0, n2) cout << ts2.order[i] << (i == n2 - 1 ? "" : " -> ");
        cout << '\n';
    }
    // 出力: 0 -> 1 -> 2 -> 3 -> 4
    // （0, 1, 3が最初に入次数0となるが、priority_queueにより若い番号から処理される）

    return 0;
}