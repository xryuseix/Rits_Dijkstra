#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
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
    vector<pair<int, int> > point(grid[0].size());
    for(int i = 0; i < grid[0].size(); i++) {
        point[i] = make_pair(grid[0][i], grid[1][i]);
    }
    sort(point.begin(), point.end());

    // pointの集合を配列で持つ
    vector<set<int> > group;
    

}