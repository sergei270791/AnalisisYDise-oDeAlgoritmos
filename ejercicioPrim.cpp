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
        int nroVertices=0;
        void insertarVertice(int);
        void insertarArista(int,int,int);
        pvertice buscarVertice(int);
        void imprimirGrafo();
        grafo prim();
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
    nroVertices++;
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

grafo grafo::prim(){
    pvertice p,pMST,paux;
    parista a;
    grafo MST;
    int menor,inicio,fin;
    p=pGrafo;
    MST.insertarVertice(p->datoOrigen);
    while(MST.nroVertices!=nroVertices){
        pMST=MST.pGrafo;
        menor=2147483647;
        while(pMST!=NULL){
            p=buscarVertice(pMST->datoOrigen);
            a=p->adyacente;
            while(a!=NULL){
                paux=MST.buscarVertice(a->datoDestino);
                if(menor > a->peso && paux==NULL){
                    menor=a->peso;
                    inicio=p->datoOrigen;
                    fin=a->datoDestino;
                }
                a=a->sgteArista;
            }
            pMST=pMST->sgteVertice;
        }
        MST.insertarVertice(fin);
        MST.insertarArista(inicio,fin,menor);
        MST.insertarArista(fin,inicio,menor);
    }
    return MST;
}

int main(){
    grafo g;
    int cant;
    g.insertarVertice(0);
    g.insertarVertice(1);
    g.insertarVertice(2);
    g.insertarVertice(3);
    g.insertarVertice(4);
    g.insertarVertice(5);
    g.insertarVertice(6);
    g.insertarVertice(7);
    g.insertarArista(0,6,53);
    g.insertarArista(6,0,53);
    g.insertarArista(0,1,32);
    g.insertarArista(1,0,32);
    g.insertarArista(0,2,29);
    g.insertarArista(2,0,29);
    g.insertarArista(4,3,34);
    g.insertarArista(3,4,34);
    g.insertarArista(3,5,18);
    g.insertarArista(5,3,18);
    g.insertarArista(4,7,46);
    g.insertarArista(7,4,46);
    g.insertarArista(4,5,40);
    g.insertarArista(5,4,40);
    g.insertarArista(0,5,60);
    g.insertarArista(5,0,60);
    g.insertarArista(4,6,51);
    g.insertarArista(6,4,51);
    g.insertarArista(0,7,31);
    g.insertarArista(7,0,31);
    g.insertarArista(7,6,25);
    g.insertarArista(6,7,25);
    g.insertarArista(7,1,21);
    g.insertarArista(1,7,21);
    cout<<"Grafo original"<<endl;
    cout<< "Vert||Aristas" <<endl;
    g.imprimirGrafo();
    cout<<"Arbol MST"<<endl;
    cout<< "Vert||Aristas" <<endl;
    grafo mst=g.prim();
    mst.imprimirGrafo();
}