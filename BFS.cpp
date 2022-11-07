#include <iostream>
#include <queue> 
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
    int padre=-1;
};
typedef vertice *pvertice;

class grafo{
    private:
        pvertice pGrafo;
        queue<int> cola;
        int cont=0;
    public:
        grafo();
        ~grafo();
        void insertarVertice(int);
        void insertarArista(int,int);
        void imprimirGrafo();
        pvertice buscarVertice(int);
        void BFS(int);
        bool existeCircuito();
        bool buscaCircuitoBFS(int);
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

void grafo::BFS(int r){
    int v;
    cola.push(r);
    while(!cola.empty()){
        v=cola.front();
        cola.pop();
        pvertice pv=buscarVertice(v);
        pvertice pa;
        parista a;
        if(pv->prev==-1){
            pv->prev=cont++;
            a=pv->adyacente;
            while(a!=NULL){
                pa=buscarVertice(a->datoDestino);
                if(pa->prev==-1){
                    cout<<"("<<pv->datoOrigen<<"->"<<pa->datoOrigen<<")"<<endl;
                    cola.push(pa->datoOrigen);
                }
                a=a->sgteArista;
            }
        }
    }
}


bool grafo::buscaCircuitoBFS(int v){
    cola.push(v);
    pvertice pv=buscarVertice(v);
    pvertice pa;
    parista a;
    pv->padre=v;
    while(!cola.empty()){
        v=cola.front();
        pv=buscarVertice(v);
        cola.pop();
        a=pv->adyacente;
        while(a!=NULL){
            pa=buscarVertice(a->datoDestino);
            if(pa->padre==-1){
                cola.push(pa->datoOrigen);
                pa->padre=v;
            }
            else if(pv->padre!=pa->datoOrigen){
                return true;
            }
            a=a->sgteArista;
        }
    }
    return false;
}

bool grafo::existeCircuito(){
    pvertice p;
    p=pGrafo;
    if(p==NULL){ return true;}
    else{
        while(p!=NULL){
            if(p->padre==-1){
                if (buscaCircuitoBFS(p->datoOrigen)){
                    return true;
                }   
            }
            p=p->sgteVertice;
        }
        return false;
    }
}

int main(){
    grafo g;
    g.insertarVertice(4);
    g.insertarVertice(1);
    g.insertarVertice(6);
    g.insertarVertice(3);
    g.insertarVertice(5);
    g.insertarVertice(7);
    g.insertarVertice(2);
    g.insertarVertice(0);
    g.insertarArista(0,4);
    g.insertarArista(4,0);
    g.insertarArista(0,1);
    g.insertarArista(1,0);
    g.insertarArista(1,5);
    g.insertarArista(5,1);
    g.insertarArista(2,3);
    g.insertarArista(3,2);
    g.insertarArista(3,6);
    g.insertarArista(6,3);
    g.insertarArista(4,5);
    g.insertarArista(5,4);
    g.insertarArista(6,5);
    g.insertarArista(5,6);
    cout<< "Vert||Aristas" <<endl;
    g.imprimirGrafo();
    g.BFS(0);
}