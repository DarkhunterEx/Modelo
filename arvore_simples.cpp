#include <bits/stdc++.h>

using namespace std;
string s="";
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
        void Pre(node **p){
            if(*p==0)
                return;
            if((*p)->right){
                //cout<<"?";
                Pre(&(*p)->right);
            }
            if((*p)->left){
                //cout<<"?";
                Pre(&(*p)->left);
            }
            string o=to_string((*p)->D.f);
            reverse(o.begin(),o.end());
            s+=o;
            s+=' ';
            //cout<<(*p)->D.f<<endl;
        }
        void Pos(node **p){
            if(*p==0){
                return;
            }
            if((*p)->left){
                //cout<<(*p)->D.f<<endl;
                Pos(&(*p)->left);
            }
            if((*p)->right){
                //cout<<(*p)->D.f<<endl;
                Pos(&(*p)->right);
            }
            string o=to_string((*p)->D.f);
            //reverse(o.begin(),o.end());
            s+=o;
            s+=' ';
            //cout<<(*p)->D.f<<endl;
        }
        void In(node **p){
            if(*p==0)
                return;
            //cout<<(*p)->D.f<<endl;
            if((*p)->left){
                //cout<<"?";
                In(&(*p)->left);
            }
            string o=to_string((*p)->D.f);
            //reverse(o.begin(),o.end());
            s+=o;
            s+=' ';
            if((*p)->right){
                //cout<<"?";
                In(&(*p)->right);
            }
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
            //cout<<R->D.f<<endl;
            if(!root){
                node *x;
                return x;
            }
            if(R->right){
                return RMax(R->right);
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
            if(!(*r)->right){
                //cout<<"?";
                aux=*r;
                *r=(*r)->left;
                return aux;
            }
            if(!(*r)->left){//cout<<"??";
                aux=*r;
                *r=(*r)->right;
                return aux;
            }
            node *M=BBTree::RMax((*r)->left);
            //cout<<M->D.f<<endl;
            swap(M->D,(*r)->D);
            return Erase(&((*r)->left),x);
        }
        bool Erase(int x){
            //cout<<n<<endl;
            node *aux=Erase(&root,x);
            //cout<<n<<endl;
            if(aux!=0){
                return true;
            }
            return false;
        }
        bool Search(node*r,int x){
            if(!r){
                node *p;
                return false;
            }
            if((r->D).f==x)
                return true;
            if(x<(r->D).f)
                return Search(r->left,x);
            return Search(r->right,x);
        }
};

int main(){
    //freopen("12.txt","w",stdout);
    string b;
    BBTree a;
    while(cin>>b){
        if(b=="I"){
            int g;
            cin>>g;
            trem c;
            c.f=g;
            a.Insert(c);
        }
        if(b=="INFIXA"){
            s="";
            a.In(&a.root);
            s.pop_back();
            //reverse(s.begin(),s.end());
            cout<<s<<endl;
        }
        if(b=="PREFIXA"){
            s="";
            a.Pre(&a.root);
            s.pop_back();
            reverse(s.begin(),s.end());
            cout<<s<<endl;
        }
        if(b=="POSFIXA"){
            s="";
            a.Pos(&a.root);
            s.pop_back();cout<<s<<endl;
        }
        if(b=="P"){
            int h;
            cin>>h;
            if(a.Search(a.root,h))
                cout<<h<<" existe"<<endl;
            else{
                cout<<h<<" nao existe"<<endl;
            }
        }
        if(b=="R"){
            int h;
            cin>>h;
            a.Erase(h);
        }
    }
}
