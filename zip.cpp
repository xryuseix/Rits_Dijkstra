#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

vector<int> split(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<int> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(stoi(field));
    }
    return result;
}

int main(void){

    vector<vector<int> > grid;

    // ファイルから入力
    ifstream ifs("pixel.csv");
    string line;
    while (getline(ifs, line)) {
        vector<int> strvec = split(line, ',');
        grid.push_back(strvec);
    }

    // CSVのX座標，Y座標をpair形に変換
    set<pair<int, int> > point;
    for(int i = 0; i < grid[0].size(); i++) {
        point.insert(make_pair(grid[0][i], grid[1][i]));
    }

    // pointで選んだ要素の集合を配列で持つ
    vector<set<pair<int, int> > > group;
    {
        while(!point.empty()) {
            pair<int, int> p = *(point.begin());
            point.erase(point.begin());

            set<pair<int, int> > tmp;
            tmp.insert(p);
            
            // 幅優先探索
            queue<pair<int, int> > q;
            q.push(p);
            while(!q.empty()) {
                pair<int, int> now = q.front();
                q.pop();
                // 移動方向の差分配列
                int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
                int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
                for(int i = 0; i < 8; i++) {
                    auto it = point.find(make_pair(now.first + dx[i], now.second + dy[i]));
                    if(it != point.end()) {
                        q.push(*it);
                        point.erase(it);
                        tmp.insert(*it);
                    }
                }
            }
            group.push_back(tmp);
        }
    }
    {
        // 各グループの中身を表示
        // for(int i = 0; i < group.size(); i++) {
        //     cout << endl;
        //     cout << "----------------------------------" << endl;
        //     cout << endl;
        //     for(auto it = group[i].begin(); it != group[i].end(); it++) {
        //         cout << "(" << (*it).first << "," << (*it).second << ") ";
        //     }
        //     cout << endl;
        // }
    }
    vector<pair<int, int> > vertex(group.size());
    {
        // 各グループの中央の点をvertexに代入
        for(int i = 0; i < group.size(); i++) {
            pair<int, int> center;
            int maxX = 0, maxY = 0, minX = 1e9, minY = 1e9;
            for(auto it = group[i].begin(); it != group[i].end(); it++) {
                maxX = max(maxX, (*it).first);
                maxY = max(maxY, (*it).second);
                minX = min(minX, (*it).first);
                minY = min(minY, (*it).second);
            }
            center.first = (maxX + minX)/2;
            center.second = (maxY + minY)/2;
            vertex[i] = center;
        }
    }
    {
        // vertexの中身 = 頂点の座標 を表示
        for(int i = 0; i < vertex.size(); i++) {
            cout << "(" << vertex[i].first << ", " << vertex[i].second << ")" << endl;
        }
    }
    {
        ofstream outputfile("zip.csv");
        // X座標を出力
        for(int i = 0; i < vertex.size(); i++) {
            if(i != 0) {
                outputfile << ",";
            }
            outputfile << vertex[i].first;
        }
        outputfile << "\n";
        // Y座標を出力
        for(int i = 0; i < vertex.size(); i++) {
            if(i != 0) {
                outputfile << ",";
            }
            outputfile << vertex[i].second;
        }
        outputfile.close();
    }

}