#include <iostream>
using namespace std;

struct arista{
    int datoDestino;
    int peso;
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
        void insertarArista(int,int,int);
        void imprimirGrafo();
        int sumaPesos();
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

void grafo::insertarArista(int x, int y, int z){
    pvertice p;
    parista a;
    p=pGrafo;
    if(p!=NULL){
        while(p->datoOrigen!=x && p!=NULL)
            p=p->sgteVertice;
        if(p!=NULL){
            a=new arista;
            a->datoDestino=y;
            a->peso=z;
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

int grafo::sumaPesos(){
    int suma=0;
    pvertice p;
    parista a;
    p=pGrafo;
    if(p!=NULL){
        while(p!=NULL){
            a=p->adyacente;
            while(a!=NULL){
                suma+=a->peso;
                a=a->sgteArista;
            }
            p=p->sgteVertice;
        }
    }
    return suma;
}

int main(){
    grafo g;
    int x,y;
    g.insertarVertice(4);
    g.insertarVertice(6);
    g.insertarVertice(3);
    g.insertarArista(4,6,5);
    g.insertarArista(3,6,4);
    g.insertarArista(3,4,7);
    cout<< "Vert||Aristas" <<endl;
    g.imprimirGrafo();
    cout<< "La suma de los pesos de las aristas del grafo es: "<< g.sumaPesos()<<endl;
}