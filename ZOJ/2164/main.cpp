#include <iostream>
using namespace std;

#define MAX_NUM 55

struct pokerList{
    int num;
    pokerList* next;
    pokerList* pre;
};

int list[MAX_NUM];

int n,r;

int main() {
    int pp,cc;
    cin>>n>>r;
    while (n!=0 || r!=0){
        pokerList* Head = new pokerList;
        pokerList* p = Head;
        pokerList* q = Head;

        for (int i=1;i<=n;i++){
            p->num = i;
            p->next = i==n ? NULL : new pokerList;
            p->pre = i==1 ? NULL : q;

            p = p->next;
            q = i==1 ? q : q->next;
        }

        for (int i = 1;i <= r;i++){
            cin>>pp>>cc;
            pokerList* tail = Head;
            pokerList* b;
            pokerList* t;

            while(tail->next != NULL)
                tail = tail->next;

            b = tail;
            for (int j = 1;j <= pp - 1; j++)
                b = b->pre;//last bottom
            if (b == tail) continue;

            t = b;
            for (int j = 1;j<= cc - 1;j++)
                t = t->pre;//last cut

            if (t->pre == NULL){
                tail->next = t;
                t->pre = tail;

                b->next->pre = NULL;
                b->next = NULL;
            }
            else{
                tail->next = t;
                t->pre->next = b->next;
                b->next->pre = t->pre;
                t->pre = tail;
                b->next = NULL;
            }
            while (Head->pre!=NULL) Head = Head->pre;
        }
        while (Head->next!=NULL) Head = Head->next;
        cout<<Head->num<<endl;

        while (Head->pre!=NULL){
            p = Head;
            Head = Head->pre;
            delete p;
        }
        cin>>n>>r;
    }
    return 0;
}