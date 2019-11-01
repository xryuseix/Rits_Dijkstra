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

    //ファイルから入力
    ifstream ifs("pixel.csv");
    string line;
    while (getline(ifs, line)) {
        vector<int> strvec = split(line, ',');
        grid.push_back(strvec);
        cout<<strvec.size()<<endl;
    }

    // CSVのX座標，Y座標をpair形に変換
    set<pair<int, int> > point;
    for(int i = 0; i < grid[0].size(); i++) {
        point.insert(make_pair(grid[0][i], grid[1][i]));
    }

    // pointで選んだ要素の集合を配列で持つ
    vector<set<pair<int, int> > > group;
    while(point.size()>0) {
        pair<int, int> p = *(point.begin());
        point.erase(point.begin());

        set<pair<int, int> > tmp;
        tmp.insert(p);
        
        // 幅優先探索
        queue<pair<int,int> > q;
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
    // for(int i=0;i<group.size();i++){
    //     cout<<endl;
    //     for(int j=0;j<10;j++){
    //         cout<<"----------------------------------"<<endl;
    //     }
    //     cout<<endl;
    //     for(auto it=group[i].begin();it!=group[i].end();it++){
    //         cout<<"("<<(*it).first <<","<<(*it).second<<") ";
    //     }
    //     cout<<endl;
    // }

}