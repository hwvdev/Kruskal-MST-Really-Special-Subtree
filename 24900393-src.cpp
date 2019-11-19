#include<bits/stdc++.h>
#define sc(x) scanf("%d",&x)
#define pf(x) printf("%d\n",x);
#define N 30009
#define M 600000
using namespace std;
int ST[M], L[M], R[M], version[N], A[N];
map<int, int> MP;
int NEXT_ID=1;

void build(int l, int r, int id){
    if(l==r){ST[id]=0; return;}
    L[id]=NEXT_ID++;
    R[id]=NEXT_ID++;
    int m=(l+r)/2;
    build(l,m,L[id]);
    build(m+1,r,R[id]);
}

int update(int l, int r, int id, int idx, int val){
    int ID=NEXT_ID++;
    if(l==r){
        ST[ID]=val;
        return ID;
    }
    int m=(l+r)/2;
    L[ID]=L[id], R[ID]=R[id];
    if(idx>=l && idx<=m) L[ID]=update(l, m, L[ID], idx, val);
    else R[ID]=update(m+1, r, R[ID], idx, val);
    ST[ID]=ST[L[ID]]+ST[R[ID]];
    return ID;
}
int query(int id, int qs, int qe, int l, int r){
    if(r<l||qs>r||qe<l) return 0;
    if(qs<=l && qe>=r) return ST[id];
    int m=(l+r)/2;
    return query(L[id],qs,qe,l,m)+query(R[id],qs,qe,m+1,r);
}
void check(int l, int r, int id){
    if(l==r){
        cout<<ST[id]<<" "; return;
    }
    int m=(l+r)/2;
    check(l,m,L[id]);
    check(m+1,r,R[id]);
}

int main(){
    int n; sc(n);
    for(int i=0;i<n;i++){sc(A[i]); MP[A[i]]=-10;}

    build(0,n-1,0);    
    memset(version,0,sizeof version);

    for(int i=0;i<n;i++){
        if(MP[A[i]]!=-10){
            version[i+1]=update(0,n-1,version[i],MP[A[i]],0);
            version[i+1]=update(0,n-1,version[i+1],i,1);
            MP[A[i]]=i;
        }
        else{
            MP[A[i]]=i;
            version[i+1]=update(0,n-1,version[i],MP[A[i]],1);
        }
        
     //   check(0,n-1,version[i+1]);
       // cout<<endl;
    }
    
    int q; sc(q);

    while(q--){
        int l, r;
        sc(l); sc(r);
        pf(query(version[r],l-1,r-1,0,n-1));
    }
}