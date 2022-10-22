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
        void BFS(int);
        void algBusqueda();
        bool existeCircuito();
        bool buscaCircuitoBFS(int,int);
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

void grafo::BFS(int v){
    pvertice p=buscarVertice(v);
    pvertice pa;
    parista a;
    p->prev=cont++;
    a=p->adyacente;
    while(a!=NULL){
        pa=buscarVertice(a->datoDestino);
        if(pa->prev==-1){
            BFS(a->datoDestino);
        }
        a=a->sgteArista;
    }
}

void grafo::algBusqueda(){
    cont=0;
    pvertice p;
    p=pGrafo;
    if(p==NULL){ return ;}
    else{
        while(p!=NULL){
            if(p->prev==-1){
                BFS(p->datoOrigen);
            }
            p=p->sgteVertice;
        }
    }
}

bool grafo::buscaCircuitoBFS(int v, int padrev){
    pvertice p=buscarVertice(v);
    pvertice pa;
    parista a;
    p->prev=1;
    a=p->adyacente;
    while(a!=NULL){
        pa=buscarVertice(a->datoDestino);
        if(pa->prev==-1){
            if(buscaCircuitoBFS(pa->datoOrigen,v)){
                return true;
            }
        }else if(padrev!=pa->datoOrigen){
            return true;
        }
        a=a->sgteArista;
    }
    return false;
}

bool grafo::existeCircuito(){
    pvertice p;
    p=pGrafo;
    if(p==NULL){ return true;}
    else{
        while(p!=NULL){
            if(p->prev==-1){
                if (buscaCircuitoBFS(p->datoOrigen,p->datoOrigen)){
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
    g.insertarVertice(0);
    g.insertarVertice(1);
    g.insertarVertice(4);
    g.insertarVertice(2);
    g.insertarVertice(3);
    g.insertarVertice(5);
    g.insertarArista(0,1);
    g.insertarArista(0,2);
    g.insertarArista(1,4);
    g.insertarArista(1,3);
    g.insertarArista(4,5);
    g.insertarArista(4,3);
    g.insertarArista(1,0);
    g.insertarArista(2,0);
    g.insertarArista(4,1);
    g.insertarArista(3,1);
    g.insertarArista(5,4);
    g.insertarArista(3,4);
    cout<< "Vert||Aristas" <<endl;
    g.imprimirGrafo();
    if(g.existeCircuito()){
        cout<<"Si existe un circuito"<<endl;
    }else{
        cout<<"No existe un circuito"<<endl;
    }
}