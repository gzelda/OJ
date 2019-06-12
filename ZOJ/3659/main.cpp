#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

#define MAX_NUM 200005

struct edge{
    int start;
    int end;
    long long weight;
}e[MAX_NUM];

int n;
int pre[MAX_NUM];
int num[MAX_NUM];
long long s[MAX_NUM];


bool cmp(edge a,edge b){
    return a.weight>b.weight;
}

int find(int x){
    if (pre[x] == x)
        return x;
    return pre[x] = find(pre[x]);
}

int main() {
    while (cin>>n){
        int a,b,c;

        for (int i = 1; i<= n ; i++){
            pre[i] = i;
            s[i] = 0;
            num[i] = 1;
        }
        for (int i = 0;i < n-1; i++){
            cin>>a>>b>>c;
            e[i].start = a;
            e[i].end = b;
            e[i].weight = c;
        }
        sort(e,e+n-1,cmp);

        int start,end;
        for (int i = 0;i< n-1; i++){
            start = e[i].start;
            end = e[i].end;
            int fs = find(start);
            int fe = find(end);
            if (s[fs] + e[i].weight * num[fe] >
                s[fe] + e[i].weight * num[fs]){
                pre[fe] = fs;
                s[fs] += num[fe] * e[i].weight;
                num[fs] += num[fe];
            }
            else{
                pre[fs] = fe;
                s[fe] += num[fs] * e[i].weight;
                num[fe] += num[fs];
            }
        }
        cout<<s[find(e[0].start)]<<endl;


    }

    return 0;
}