#include <iostream>
using namespace std;

struct arista{
    int datoDestino;
    arista *sgteArista;
};
typedef arista *parista;

struct vertice{
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
    int prev=-1;
    int color=-1;
};
typedef vertice *pvertice;

class grafo{
    private:
        pvertice pGrafo;
        int cont=0;
    public:
        grafo();
        ~grafo();
        void insertarVertice(int);
        void insertarArista(int,int);
        void imprimirGrafo();
        pvertice buscarVertice(int);
        bool EsBicolorable();
        bool DFSColor(int,int);
};

grafo::grafo(){
    pGrafo=NULL;
}

grafo::~grafo(){
    pvertice p,rp;
    parista r,ra;
    p=pGrafo;
    while(p!=NULL){
        r=p->adyacente;
        while(r!=NULL){
            ra=r;
            r=r->sgteArista;
            delete ra;
        }
        rp=p;
        p=p->sgteVertice;
        delete rp;
    }
}

void grafo::insertarVertice(int x){
    pvertice p;
    p=new vertice;
    p->datoOrigen=x;
    p->adyacente=NULL;
    p->sgteVertice=pGrafo;
    pGrafo=p;
}

void grafo::insertarArista(int x, int y){
    pvertice p;
    parista a;
    p=pGrafo;
    if(p!=NULL){
        while(p->datoOrigen!=x && p!=NULL)
            p=p->sgteVertice;
        if(p!=NULL){
            a=new arista;
            a->datoDestino=y;
            a->sgteArista=p->adyacente;
            p->adyacente=a;
        }
    }
}

pvertice grafo::buscarVertice(int v){
    pvertice p;
    parista a;
    p=pGrafo;
    if(p==NULL){ return NULL;}
    else{
        while(p!=NULL && p->datoOrigen!=v)
            p=p->sgteVertice;
        return p;
    }
}

void grafo::imprimirGrafo(){
    pvertice p;
    parista a;
    p=pGrafo;
    if(p==NULL) cout<<"Grafo vacio"<<endl;
    else
        while(p!=NULL){
            cout<<p-> datoOrigen<<" ||  ";
            a=p->adyacente;
            while(a!=NULL){
                cout<<a->datoDestino<<" ";
                a=a->sgteArista;
            }
            cout<<endl;
            p=p->sgteVertice;
        }
}


bool grafo::DFSColor(int v, int padrev){
    pvertice p=buscarVertice(v);
    pvertice padre=buscarVertice(padrev);
    pvertice pa;
    parista a;
    p->prev=1;
    if(padre->color==1){
        p->color=0;
    }else{
        p->color=1;
    }
    a=p->adyacente;
    while(a!=NULL){
        pa=buscarVertice(a->datoDestino);
        if(pa->prev==-1){
            if(!DFSColor(pa->datoOrigen,v)){
                return false;
            }
        }else if(padre!=p && padre->color!=pa->color){
            return false;
        }
        a=a->sgteArista;
    }
    return true;
}

bool grafo::EsBicolorable(){
    pvertice p;
    p=pGrafo;
    if(p==NULL){ return true;}
    else{
        while(p!=NULL){
            if(p->prev==-1){
                if (!DFSColor(p->datoOrigen,p->datoOrigen)){
                    return false;
                }   
            }
            p=p->sgteVertice;
        }
        return true;
    }
}

int main(){
    grafo g;
    g.insertarVertice(8);
    g.insertarVertice(7);
    g.insertarVertice(6);
    g.insertarVertice(5);
    g.insertarVertice(4);
    g.insertarVertice(3);
    g.insertarVertice(2);
    g.insertarVertice(1);
    g.insertarVertice(0);
    g.insertarArista(0,1);
    g.insertarArista(1,2);
    g.insertarArista(1,7);
    g.insertarArista(1,3);
    g.insertarArista(2,3);
    g.insertarArista(3,5);
    g.insertarArista(4,6);
    g.insertarArista(4,8);
    g.insertarArista(7,8);
    g.insertarArista(1,0);
    g.insertarArista(2,1);
    g.insertarArista(7,1);
    g.insertarArista(3,1);
    g.insertarArista(3,2);
    g.insertarArista(5,3);
    g.insertarArista(6,4);
    g.insertarArista(8,4);
    g.insertarArista(8,7);
    cout<< "Vert||Aristas" <<endl;
    g.imprimirGrafo();
    if(g.EsBicolorable()){
        cout<<"El grafo es Bicolorable"<<endl;
    }else{
        cout<<"El grafo no es Bicolorable"<<endl;
    }
}
