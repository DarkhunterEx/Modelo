#include <bits/stdc++.h>

using namespace std;

class trem{
	public:
		int f=0;
};

class node{
	public:
		trem D;
		node *left;
		node *right;
		static node *montaNode(trem Dat){
			node *P=new node;
			if(P){
				P->D=Dat;
				P->left=0;
				P->right=0;
			}
			return P;
		}
		static trem desmontaNode(node *P){
			trem x;
			if(P){
				x=P->D;
				delete P;
			}
			return x;
		}
};

class BBTree{
    public:
        node *root;
        int n;
        BBTree(){
            root=0;
            n=0;
        }
        void Clear(node **p,int &n){
            if(*p==0)
                return;
            if((*p)->right){
                //cout<<"?";
                Clear(&(*p)->right,n);
            }
            if((*p)->left){
                //cout<<"?";
                Clear(&(*p)->left,n);
            }
            if(*p){
                node::desmontaNode((*p));
                //cout<<"???";
            }
            if(*p==root){
                root=0;
            }
            n=0;
        }
        ~BBTree(){
            Clear(&root,n);
        }
        node *RMin(node *R){
            if(!root){
                //cout<<"A";
                node *x;
                return x;
            }
            if(R->left){
                return RMin(R->left);
            }
            return R;
        }
        node *Min(){
            if(!root){
                //cout<<"B";
                node *x;
                return x;
            }
            return RMin(root);
        }
        node *RMax(node *R){
            if(!root){
                //cout<<"A";
                node *x;
                return x;
            }
            if(R->right){
                return RMin(R->right);
            }
            return R;
        }
        node *Max(){
            if(!root){
                //cout<<"B";
                node *x;
                return x;
            }
            return RMax(root);
        }
        static bool Insert(node *aux,node **p){
            if(!*p){
                *p=aux;
                return true;
            }
            if(((*p)->D).f==(aux->D).f){
                node::desmontaNode(aux);
                return false;
            }
            if((aux->D).f<((*p)->D).f){
                return Insert(aux,&((*p)->left));
            }
            return Insert(aux,&((*p)->right));
        }
        bool Insert(trem x){
            node *B=node::montaNode(x);
            if(!B)
                return false;
            if(BBTree::Insert(B,&root)){
                n++;
                return true;
            }
            return false;
        }
        node *Erase(node **r,int x){
            node *aux;
            if(!(*r))
                return NULL;
            if(x<((*r)->D).f)
                return Erase(&((*r)->left),x);
            if(x>((*r)->D).f)
                return Erase(&((*r)->right),x);
            n--;
            if(!(*r)->left){
                aux=*r;
                *r=(*r)->right;
                return aux;
            }
            if(!(*r)->right){
                aux=*r;
                *r=(*r)->left;
                return aux;
            }
            node *M=BBTree::RMin((*r)->right);
            swap(M->D,(*r)->D);
            return Erase(&((*r)->right),x);
        }
        bool Erase(int x){
            node *aux=Erase(&root,x);
            if(aux!=0){
                return true;
            }
            return false;
        }
        node *Search(node*r,int x){
            if(!r){
                node *p;
                return p;
            }
            if((r->D).f==x)
                return r;
            if(x<(r->D).f)
                return Search(r->left,x);
            return Search(r->right,x);
        }
};

int main(){
    BBTree a;
    char b;
    while(cin>>b){
        if(b=='M'){
            cout<<(a.Max())->D.f<<endl;
        }
        if(b=='m')
            cout<<(a.Min())->D.f<<endl;
        if(b=='i'){
            int c;
            cin>>c;
            trem d;
            d.f=c;
            cout<<a.Insert(d)<<endl;
            cout<<a.n<<endl;
        }
        if(b=='e'){
            int c;
            cin>>c;
            cout<<a.Erase(c)<<endl;
            cout<<a.n<<endl;
        }
        if(b=='c'){
            a.Clear(&a.root,a.n);
            cout<<a.n<<endl;
        }
        if(b=='s'){
            int t;
            cin>>t;
            cout<<a.Search(a.root,t)->D.f<<endl;
        }
    }
}
