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
#define rep(i, s, n) for (ll i = (s); i < (ll)(n); i++)
template <class T> bool chmin(T& a, T b){ if(a > b){ a = b; return 1; } return 0; }
template <class T> bool chmax(T& a, T b){ if(a < b){ a = b; return 1; } return 0; }
const ll INF = 1LL << 60;
const ll MOD = 998244353;



struct PolarComp {
    inline int area(ll x, ll y) const {
        if (x == 0 && y == 0) return 0;
        if (y > 0 || (y == 0 && x > 0)) return 1;
        return 2;
    }
    bool operator()(const pair<ll, ll>& a, const pair<ll, ll>& b) const {
        auto [xa, ya] = a;
        auto [xb, yb] = b;
        int area_a = area(xa, ya);
        int area_b = area(xb, yb);
        if (area_a != area_b) return area_a < area_b;
        ll cross = xa * yb - ya * xb;
        if (cross != 0) return cross > 0;
        return (xa * xa + ya * ya) < (xb * xb + yb * yb);
    }
};



/* 
 * メソッド仕様一覧:
 * 
 * - struct PolarComp
 *   概要  : 座標(x, y)のペアを、X軸の正の方向(0度)から反時計回りにソートするための比較関数オブジェクト。
 *           std::sort の第3引数に渡して使用する。浮動小数点数(atan2など)を使わず、外積のみで判定するため
 *           精度誤差が一切発生しない。
 * 
 *   仕様詳細:
 *     1. 原点 (0, 0) は全ての点より手前(先頭)に来るように処理される。
 *     2. 偏角が完全に一致する(一直線上にある)複数点は、原点からの距離が近い順にソートされる。
 *     3. 座標の値は 10^9 程度まで許容 (内部で最大 2*10^18 の計算を行うため、ll型でオーバーフローしない設計)。
 */



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ====================================================
    // 使用例: 座標の偏角ソート
    // ====================================================
    vector<pl> points = {
        {-1, -1}, {0, 1}, {1, 0}, {0, 0}, {-1, 1}
    };

    // sortの第3引数に PolarComp() を渡すだけでOK
    sort(all(points), PolarComp());

    cout << "--- 偏角ソート結果 ---\n";
    for (auto [x, y] : points) {
        cout << "(" << x << ", " << y << ")\n";
    }
    // 出力順:
    // (0, 0)   -> 原点
    // (1, 0)   -> 0度
    // (0, 1)   -> 90度
    // (-1, 1)  -> 135度
    // (-1, -1) -> 225度

    return 0;
}