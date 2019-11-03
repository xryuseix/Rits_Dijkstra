#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <queue>
const int INF = 1e9;
typedef long double ld;
using namespace std;

vector<int> split(string& input, char delimiter) {
    istringstream stream(input);
    string field;
    vector<int> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(stoi(field));
    }
    return result;
}

class WAR_FLY {
public:
    vector<vector<ld> > d; //辺の数
    int V; //頂点の数
    
    WAR_FLY(int n) {
        V = n;
        d = vector<vector<ld> > (n,vector<ld>(n));
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                if(i == j) {
                    d[i][j] = 0;
                }
                else {
                    d[i][j] = INF;
                }
            }
        }
    }

    void warshall_floyd() {
        for(int k = 0; k < V; k++) {
            for(int i = 0; i < V; i++) {
                for(int j = 0; j < V; j++) {
                    d[i][j] = min((ld)d[i][j], (ld)d[i][k] + (ld)d[k][j]);
                }
            }
        }
    }

    void add(int from, int to, ld cost) {
        d[from][to] = cost;
        d[to][from] = cost;
    }

    void show() {
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                cout << d[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main(void){

    vector<vector<int> > grid;

    // ファイルから入力
    ifstream ifs("zip.csv");
    string line;
    while (getline(ifs, line)) {
        vector<int> strvec = split(line, ',');
        grid.push_back(strvec);
    }
    // CSVのX座標，Y座標をpair形に変換
    vector<pair<int, int> > V;
    for(int i = 0; i < grid[0].size(); i++) {
        V.push_back(make_pair(grid[0][i], grid[1][i]));
    }
    
    WAR_FLY wa(V.size());

    // 頂点間の距離を求める
    vector<vector<double> > dist(V.size(), vector<double>(V.size()));
    for(int i = 0; i < V.size(); i++) {
        for(int j = 0; j < V.size(); j++) {
            dist[i][j] = sqrt(pow(abs(V[i].first - V[j].first), 2) + pow(abs(V[i].second - V[j].second), 2));
        }
    }
    
    // 辺を追加する(肉眼で"writeplot.py"で作成した画像を元に辺を張る)
    vector<pair<int, int> > E;
    E.push_back(make_pair(0,1));
    E.push_back(make_pair(1,2));
    E.push_back(make_pair(1,4));
    E.push_back(make_pair(1,5));
    E.push_back(make_pair(2,1));
    E.push_back(make_pair(2,3));
    E.push_back(make_pair(2,4));
    E.push_back(make_pair(2,5));
    E.push_back(make_pair(2,6));
    E.push_back(make_pair(3,2));
    E.push_back(make_pair(3,5));
    E.push_back(make_pair(3,6));
    E.push_back(make_pair(4,1));
    E.push_back(make_pair(4,2));
    E.push_back(make_pair(4,5));
    E.push_back(make_pair(4,8));
    E.push_back(make_pair(5,2));
    E.push_back(make_pair(5,1));
    E.push_back(make_pair(5,3));
    E.push_back(make_pair(5,6));
    E.push_back(make_pair(5,9));
    E.push_back(make_pair(6,10));
    E.push_back(make_pair(6,3));
    E.push_back(make_pair(6,5));
    E.push_back(make_pair(6,9));
    E.push_back(make_pair(6,2));
    E.push_back(make_pair(7,8));
    E.push_back(make_pair(8,7));
    E.push_back(make_pair(8,9));
    E.push_back(make_pair(8,4));
    E.push_back(make_pair(8,12));
    E.push_back(make_pair(9,8));
    E.push_back(make_pair(9,5));
    E.push_back(make_pair(9,6));
    E.push_back(make_pair(9,10));
    E.push_back(make_pair(10,9));
    E.push_back(make_pair(10,6));
    E.push_back(make_pair(10,13));
    E.push_back(make_pair(11,12));
    E.push_back(make_pair(12,11));
    E.push_back(make_pair(12,13));
    E.push_back(make_pair(12,8));
    E.push_back(make_pair(12,15));
    E.push_back(make_pair(13,12));
    E.push_back(make_pair(13,10));
    E.push_back(make_pair(14,15));
    E.push_back(make_pair(15,14));
    E.push_back(make_pair(15,12));
    E.push_back(make_pair(15,16));
    E.push_back(make_pair(16,15));

    for(int i = 0; i < E.size(); i++) {
        wa.add(E[i].first, E[i].second, dist[E[i].first][E[i].second]);
    }
    wa.warshall_floyd();
    wa.show();
    cout<<E.size()<<endl;
}
