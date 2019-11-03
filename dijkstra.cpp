#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <queue>
const int INF = 1e9;
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

class DIJKSTRA {
public:
    int V;

    struct edge {
        int to;
        double cost;
    };

    typedef pair<double, int> PI; //firstは最短距離、secondは頂点の番号
    vector<vector<edge> >G;
    vector<double> d; //これ答え。d[i]:=V[i]までの最短距離
    vector<int> prev; //経路復元

    DIJKSTRA(int size) {
        V = size;
        G = vector<vector<edge> >(V);
        prev = vector<int> (V, -1);
    }

    void add(int from, int to, double cost) {
        edge e1 = {to, cost};
        G[from].push_back(e1);
        edge e2 = {from, cost};
        G[to].push_back(e2);
    }

    void dijkstra(int s) {
        //greater<P>を指定することでfirstが小さい順に取り出せるようにする
        priority_queue<PI, vector<PI>, greater<PI> > que;
        d = vector<double> (V, INF);
        d[s] = 0;
        que.push(PI(0, s));

        while(!que.empty()) {
            PI p = que.top();
            que.pop();
            int v = p.second;
            if(d[v] < p.first) continue;
            for(int i = 0; i < G[v].size(); i++) {
                edge e = G[v][i];
                if(d[e.to] > d[v] + e.cost) {
                    d[e.to] = d[v] + e.cost;
                    prev[e.to] = v;
                    que.push(PI(d[e.to], e.to));
                }
            }
        }
    }
    vector<int> get_path(int t) {
        vector<int> path;
        for(;t != -1; t = prev[t]) {
            //tがsになるまでprev[t]をたどっていく
            path.push_back(t);
        }
        //このままだとt->sの順になっているので逆順にする
        reverse(path.begin(),path.end());
        return path;
    }
    void show() {
        for(int i = 0; i < d.size()-1; i ++) {
            cout << d[i] << " ";
        }
        cout << d[d.size()-1] << endl;
    }
};

int main(void){

    vector<vector<int> > tmp1, tmp2;

    // ファイルから入力
    ifstream ifs("zip.csv");
    string line;
    while (getline(ifs, line)) {
        vector<int> strvec = split(line, ',');
        tmp1.push_back(strvec);
    }
    ifstream ifs2("edge.csv");
    while (getline(ifs2, line)) {
        vector<int> strvec = split(line, ',');
        tmp2.push_back(strvec);
    }
    // CSVのX座標，Y座標をpair形に変換
    vector<pair<int, int> > V;
    for(int i = 0; i < tmp1[0].size(); i++) {
        V.push_back(make_pair(tmp1[0][i], tmp1[1][i]));
    }

    // 辺を読み込む
    vector<pair<int, int> > E;
    for(int i = 0; i < tmp2[0].size(); i++) {
        E.push_back(make_pair(tmp2[0][i], tmp2[1][i]));
    }

    DIJKSTRA dj(V.size());

    // 頂点間の距離を求める
    vector<vector<double> > dist(V.size(), vector<double>(V.size()));
    for(int i = 0; i < V.size(); i++) {
        for(int j = 0; j < V.size(); j++) {
            dist[i][j] = sqrt(pow(abs(V[i].first - V[j].first), 2) + pow(abs(V[i].second - V[j].second), 2));
        }
    }

    // 辺を追加する(肉眼で"writeplot.py"で作成した画像を元に辺を張る)
    for(int i = 0; i < E.size(); i++) {
        dj.add(E[i].first, E[i].second, dist[E[i].first][E[i].second]);
    }
    {
        // 出力
        ofstream outputfile("path.csv");

        for(int i = 0; i < V.size(); i++) {
            // pathの初期化
            for(int j = 0; j < dj.prev.size(); j++) {
                dj.prev[j] = -1;
            }
            dj.dijkstra(i);
            for(int j = 0; j < dj.d.size(); j++) {
                vector<int> path = dj.get_path(j);
                for(int k = 0; k < path.size(); k++) {
                    if(k == 0) {
                        outputfile << path[k];
                    } else {
                        outputfile << "," << path[k];
                    }
                }
                outputfile << endl;
            }
        }
        outputfile.close();
    }
}
