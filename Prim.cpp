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
    cout<<"Cuantos vertices desea agregar: ";
    cin>>cant;
    for(int i=cant;i>0;i--){
        int aux;
        cout<<"Ingrese el vertice: ";
        cin>>aux;
        g.insertarVertice(aux);
    }
    cout<<"Cuantas aristas desea agregar: ";
    cin>>cant;
    for(int i=cant;i>0;i--){
        int aux1,aux2,peso;
        cout<<"Ingrese el primer vertice: ";
        cin>>aux1;
        cout<<"Ingrese el segundo vertice: ";
        cin>>aux2;
        cout<<"Ingrese el peso de la arista: ";
        cin>>peso;
        g.insertarArista(aux1,aux2,peso);
        g.insertarArista(aux2,aux1,peso);
    }
    cout<<"Grafo original"<<endl;
    cout<< "Vert||Aristas" <<endl;
    g.imprimirGrafo();
    cout<<"Arbol MST"<<endl;
    cout<< "Vert||Aristas" <<endl;
    grafo mst=g.prim();
    mst.imprimirGrafo();
}