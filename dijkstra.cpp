#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
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
        int cost;
    };

    typedef pair<int, int> PI; //firstは最短距離、secondは頂点の番号
    vector<vector<edge> >G;
    vector<int> d; //これ答え。d[i]:=V[i]までの最短距離
    vector<int> prev; //経路復元

    DIJKSTRA(int size) {
        V = size;
        G = vector<vector<edge> >(V);
        prev = vector<int> (V, -1);
    }

    void add(int from, int to, int cost) {
        edge e = {to, cost};
        G[from].push_back(e);
    }

    void dijkstra(int s) {
        //greater<P>を指定することでfirstが小さい順に取り出せるようにする
        priority_queue<PI, vector<PI>, greater<PI> > que;
        d = vector<int> (V, INF);
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

    

}