#include <bits/stdc++.h>

using namespace std;
string s="";
vector<string>M;
class trem{
	public:
		string f="";
		int kill=0;
};

class node{
	public:
		trem D;
		int fb;
		node *left;
		node *right;
		static node *montaNode(trem Dat){
			node *P=new node;
			if(P){
				P->D=Dat;
				P->left=0;
				P->right=0;
				P->fb=0;
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

node *RMin(node *R){
    if(R->left){
        return RMin(R->left);
    }
    return R;
}
node *RMax(node *R){
    //cout<<R->D.f<<endl;
    if(R->right){
        return RMax(R->right);
    }
    return R;
}

class AVLTree{
    public:
        node *root;
        int n;
        AVLTree(){
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
            if(*p==root){
                root=0;
            }
            if(*p){
                node::desmontaNode((*p));
                //cout<<"???";
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
            string o=(*p)->D.f;
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
            M.push_back((*p)->D.f);
        }
        void In(node **p){
            if(*p==0)
                return;
            //cout<<(*p)->D.f<<endl;
            if((*p)->left){
                //cout<<"?";
                In(&(*p)->left);
            }
            string o=(*p)->D.f;
            //reverse(o.begin(),o.end());
            s+=o;
            s+=' ';
            s+=to_string((*p)->D.kill)+'\n';
            if((*p)->right){
                //cout<<"?";
                In(&(*p)->right);
            }
        }
        ~AVLTree(){
            Clear(&root,n);
        }
        node *Search(node*r,string x){
            if(!r){
                return NULL;
            }
            if((*r).D.f==x){
                return r;
            }
            if(x<(r->D).f)
                return Search(r->left,x);
            return Search(r->right,x);
        }
        static void RSD(node **r){
            node *a=*r;
            node *b=a->left;
            a->left=b->right;
            b->right=a;
            *r=b;
            if(b->fb==-1){
                a->fb=b->fb=0;
            }
            else{
                a->fb=-1;
                b->fb=1;
            }
        }
        static void RDD(node **r){
            node *a=*r;
            node *b=a->left;
            node *c=b->right;
            b->right=c->left;
            a->left=c->right;
            c->right=a;
            c->left=b;
            *r=c;
            if(c->fb==0){
                a->fb=b->fb=0;
            }
            else{
                if(c->fb==-1){
                    b->fb=c->fb=0;
                    a->fb=1;
                }
                else{
                    a->fb=c->fb=0;
                    b->fb=-1;
                }
            }
        }
        static void RSE(node **r){
            node *a=*r;
            node *b=a->right;
            a->right=b->left;
            b->left=a;
            *r=b;
            if(b->fb==1){
                a->fb=b->fb=0;
            }
            else{
                a->fb=1;
                b->fb=-1;
            }
        }
        static void RDE(node **r){
            node *a=*r;
            node *b=a->right;
            node *c=b->left;
            b->left=c->right;
            a->right=c->left;
            c->left=a;
            c->right=b;
            *r=c;
            if(c->fb==0){
                a->fb=b->fb=0;
            }
            else{
                if(c->fb==1){
                    b->fb=c->fb=0;
                    a->fb=-1;
                }
                else{
                    a->fb=c->fb=0;
                    b->fb=+1;
                }
            }
        }
        static bool Insert(node **r,node *aux){
            if(!(*r)){
                //cout<<aux<<endl;
                *r=aux;
                aux->fb=0;
                return true;
            }
            if(((*r)->D).f==(aux->D).f){
                node::desmontaNode(aux);
                return false;
            }
            if((aux->D).f<((*r)->D).f){
                if(AVLTree::Insert(&((*r)->left),aux)){
                    if((*r)->fb==0){
                        (*r)->fb=-1;
                        return true;
                    }
                    if((*r)->fb==1){
                        (*r)->fb=0;
                        return false;
                    }
                    if(((*r)->left)->fb==-1){
                        AVLTree::RSD(r);
                        return false;
                    }
                    AVLTree::RDD(r);
                    return false;
                }
                return false;
            }
            if((aux->D).f>((*r)->D).f){
                if(AVLTree::Insert(&((*r)->right),aux)){
                    if((*r)->fb==0){
                        (*r)->fb=1;
                        return true;
                    }
                    if((*r)->fb==-1){
                        (*r)->fb=0;
                        return false;
                    }
                    if(((*r)->right)->fb==1){
                        AVLTree::RSE(r);
                        return false;
                    }
                    AVLTree::RDE(r);
                    return false;
                }
                return false;
            }
        }
        bool Insert(trem x){
            node *B=node::montaNode(x);
            if(!B)
                return false;
            if(AVLTree::Insert(&root,B)){
                n++;
                return true;
            }
            return false;
        }
        static bool Erase(node **r,trem x,node **aux){
            if(!(*r)){
                return false;
            }
            if(x.f<((*r)->D).f){
                if(AVLTree::Erase(&((*r)->left),x,aux)){
                    if((*r)->fb==-1){
                        (*r)->fb=0;
                        return true;
                    }
                    if((*r)->fb==0){
                        (*r)->fb=1;
                        return false;
                    }
                    if(((*r)->right)->fb>=0){
                        AVLTree::RSE(r);
                        return true;
                    }//cout<<"?";
                    AVLTree::RDE(r);
                    return true;
                }
                return false;
            }
            if(x.f>((*r)->D).f){
                if(AVLTree::Erase(&((*r)->right),x,aux)){
                    if((*r)->fb==1){
                        (*r)->fb=0;
                        return true;
                    }
                    if((*r)->fb==0){
                        (*r)->fb=-1;
                        return false;
                    }
                    if(((*r)->left)->fb<=0){
                        AVLTree::RSD(r);
                        return true;
                    }
                    AVLTree::RDD(r);
                    return true;
                }
                return false;
            }
            if(!(*r)->left){
                *aux=*r;
                *r=(*r)->right;
                return true;
            }
            if(!(*r)->right){
                *aux=*r;
                *r=(*r)->left;
                return true;
            }
            node *MM=RMin((*r)->right);
            //cout<<MM->D.kill<<" "<<(*r)->D.kill<<endl;
            swap(MM->D,(*r)->D);
            //cout<<MM->D.kill<<" "<<(*r)->D.kill<<endl;
            if(AVLTree::Erase(&((*r)->right),x,aux)){
                    if((*r)->fb==1){
                        (*r)->fb=0;
                        return true;
                    }
                    if((*r)->fb==0){
                        (*r)->fb=-1;
                        return false;
                    }
                    if(((*r)->left)->fb<=0){
                        AVLTree::RSD(r);
                        return true;
                    }
                    AVLTree::RDD(r);
                    return true;
                }
        }
        bool Erase(trem x){
            if(!root)return false;
            node *aux=0;
            AVLTree::Erase(&root,x,&aux);
            if(aux!=0){
                n--;
                node::desmontaNode(aux);
                return true;
            }
            return false;
        }
};

int main(){
    //freopen("12.txt","r",stdin);
    //freopen("1.txt","w",stdout);
    AVLTree a;
    string b;
    set<string>MM;
    set<string>::iterator it;
    while(cin>>b){
        string c;
        cin>>c;
        node *gg=a.Search(a.root,b);
        if(!gg){
            trem x;
            x.f=b;
            a.Insert(x);
            gg=a.Search(a.root,b);
        }
        gg->D.kill++;
        MM.insert(c);
        //mmm.insert(c);
    }
    //mmm.Pos(&mmm.root);
    for(it=MM.begin();it!=MM.end();it++){
        trem x;
        x.f=*it;
        a.Erase(x);
    }
    cout<<"HALL OF MURDERERS"<<endl;
    a.In(&a.root);
    cout<<s;
}
