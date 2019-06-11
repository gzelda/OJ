#include <iostream>
#include <vector>

#define MAX_NUM 100005

using namespace std;

vector<int> vex[MAX_NUM*2];
bool visited[MAX_NUM];
int path[MAX_NUM],sen[MAX_NUM],N,M,K,L,c_visited,c_sen;

void dfs(int node){
    for (int i = 0;i < vex[node].size();i++){
        int n_node = vex[node][i];
        if (!visited[n_node]){
            visited[n_node] = true;
            c_visited++;
            if (sen[n_node]){
                sen[n_node] = 0;
                c_sen++;
            }
            else dfs(n_node);
        }
    }
}

int main(){
    int T, a, b;
    cin>>T;
    while(T--){
        cin>>N>>M>>K;
        for (int i = 0; i <= N; i++) { //initialize
            sen[i] = 0;
            visited[i] = false;
        }
        for (int i = 0; i <= N; i++){
            vex[i].clear();
        }
        for (int i = 1;i<= K;i++) {
            cin >> a;
            sen[a] = 1;
        }
        for (int i = 1;i<= M;i++) {
            cin>>a>>b;
            vex[a].push_back(b);
            vex[b].push_back(a);
        }
        cin>>L;
        for (int i = 1; i <= L; i++) cin>>path[i];
        if (L == K){
            int origin = path[1];
            sen[origin] = 0;
            visited[origin] = true;
            c_visited = c_sen = 1;
            for (int i = 1;i <= L; i++){
                if (sen[path[i]])
                    break;
                dfs(path[i]);
            }
        }
        if (L == K && c_visited == N && c_sen == L)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    return 0;
}