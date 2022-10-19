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
};
typedef vertice *pvertice;

class grafo{
    private:
        pvertice pGrafo;
    public:
        grafo();
        ~grafo();
        void insertarVertice(int);
        void insertarArista(int,int);
        void imprimirGrafo();
        bool buscaCamino(int, int);
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

bool grafo::buscaCamino(int v, int w){
    pvertice p;
    parista a;
    p=pGrafo;
    if(p==NULL){ return false;}
    else{
        while(p->datoOrigen!=v && p!=NULL)
            p=p->sgteVertice;
        if(p!=NULL){
            if(v==w){
                return true;
            }else{
                a=p->adyacente;
                while(a!=NULL){
                    if(buscaCamino(a->datoDestino,w) || buscaCamino(w,a->datoDestino)){
                        return true;
                    }
                    a=a->sgteArista;
                }
            }
        }
        else{
            return false;
        }
    }
}

int main(){
    grafo g;
    int x,y;
    g.insertarVertice(0);
    g.insertarVertice(1);
    g.insertarVertice(2);
    g.insertarVertice(3);
    g.insertarVertice(4);
    g.insertarVertice(5);
    g.insertarVertice(6);
    g.insertarArista(0,2);
    g.insertarArista(0,1);
    g.insertarArista(0,5);
    g.insertarArista(0,6);
    g.insertarArista(1,2);
    g.insertarArista(3,4);
    g.insertarArista(3,5);
    g.insertarArista(4,5);
    g.insertarArista(4,6);
    cout<< "Vert||Aristas" <<endl;
    g.imprimirGrafo();
    int v=0,w=3;
    cout<<"¿Hay un camino entre los vertices "<<v<<" y "<<w<<" ?: ";
    if(g.buscaCamino(v,w)){
        cout<<" Si hay un camino entre esos 2 vertices";
    }else{
        cout<<" No hay un camino entre esos 2 vertices";
    }
}