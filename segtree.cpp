#include <bits/stdc++.h>
using namespace std;
#define Mid (l + ((r - l) >> 1))
typedef int no;
//Lucas G
no Seg[4*NMax];
int Vet[NMax], n=QTD;

no Modify(no a, no b){
    return a + b;
}

no build(int l = 0, int r = n - 1, int id = 1){
    if (l == r)
        return Seg[id] = Vet[l];
    return Seg[id] = Modify(build(l, Mid, 2 * id), build(Mid + 1, r, 2 * id + 1));
}

no query(int i, int j, int l = 0, int r = n - 1, int id = 1){
    if (i > r || j < l) return 0;
    if (i <= l && j >= r) return Seg[id];
    return Modify(query(i, j, l, Mid, 2 * id), query(i, j, Mid + 1, r, 2 * id + 1));
}

void upd(int i, int x, int l = 0, int r = n - 1, int id = 1){
    if (l > r) return;
    if (l == r){ Seg[id] = x; return; }
    if (i <= Mid) upd(i, x, l, Mid, 2 * id);
    else upd(i, x, Mid + 1, r, 2 * id + 1);
    Seg[id] = Modify(Seg[2 * id], Seg[2 * id + 1]);
}

int main(){
	for(int i=0;i<10;i++){
        cin>>Vet[i];
	}
	build();
	int a,b;
	cin>>a>>b;
	cout<<query(a,b)<<endl;
}
