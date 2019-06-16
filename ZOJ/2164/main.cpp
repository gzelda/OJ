#include <iostream>
using namespace std;

#define MAX_NUM 55
struct pokerList{
    int num;
    pokerList* next;
};

int list[MAX_NUM];

int n,r;

int main() {
    int p,c;
    cin>>n>>r;
    while (n!=0 || r!=0){
        pokerList* HeadNode = new pokerList;
        pokerList* p = HeadNode;
        for (int i=1;i<n;i++){
            p->num = i;
            p->next = new pokerList;
            p = p->next;
        }
        
        for (int i=0;i<n;i++){
            cin>>p>>c;

        }
        cin>>n>>r;
    }

    return 0;
}