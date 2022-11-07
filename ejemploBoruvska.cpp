#include <iostream>
using namespace std;

struct arista{
    int datoDestino;
    int peso;
    arista *sgteArista;
    int componente=0;
};
typedef arista *parista;

struct vertice{
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
    int componente=0;
    int prev=-1;
};
typedef vertice *pvertice;

class grafo{
    private:
        pvertice pGrafo;
    public:
        grafo();
        ~grafo();
        int nroVertices=0;
        int nroAristas=0;
        int nroComponentes=0;
        void insertarVertice(int);
        void insertarArista(int,int,int);
        pvertice buscarVertice(int);
        bool buscaCamino(int,int);
        bool buscaArista(int,int);
        void imprimirGrafo();
        void restablecerPrev();
        void colocarComponente();
        grafo boruvska();
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
        while(p!=NULL && p->datoOrigen!=x )
            p=p->sgteVertice;
        if(p!=NULL){
            a=new arista;
            a->datoDestino=y;
            a->peso=z;
            a->sgteArista=p->adyacente;
            p->adyacente=a;
            nroAristas++;
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

bool grafo::buscaArista(int v, int w){
     pvertice pv,pw;
     parista a;
     pv=buscarVertice(v);
     pw=buscarVertice(w);
     if(pv==NULL || pw==NULL){
        return false;
     }else{
        a=pv->adyacente;
        while(a!=NULL){
            if(a->datoDestino==w){
                return true;
            }
            a=a->sgteArista;
        }
        return false;
     }
}

void grafo::restablecerPrev(){
    pvertice p;
    p=pGrafo;
    while(p!=NULL){
        p->prev=-1;
        p=p->sgteVertice;
    }
}

bool grafo::buscaCamino(int v, int w){
     pvertice pv,pw,pa;
     parista a;
     pv=buscarVertice(v);
     pv->prev=1;
     pw=buscarVertice(w);
     if(pv==NULL || pw==NULL){
        return false;
     }else{
        if(v==w){
            restablecerPrev();
            return true;
        }else{
            a=pv->adyacente;
            while(a!=NULL){
                pa=buscarVertice(a->datoDestino);
                if(pa->prev==-1){
                    if(buscaCamino(a->datoDestino,w)){
                        //restablecerPrev();
                        return true;
                    }
                }
                a=a->sgteArista;
            }
            return false;
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

void grafo::colocarComponente(){
    pvertice p,pa;
    parista a;
    p=pGrafo;
    int cont=1;
    while(p!=NULL){
        p->componente=0;
        p=p->sgteVertice;
    }
    p=pGrafo;
    p->componente=1;
    while(p!=NULL){
        if(p->componente==0){
            cont++;
            p->componente=cont;
        }
        pa=p->sgteVertice;
        while(pa!=NULL){
            if(buscaCamino(p->datoOrigen,pa->datoOrigen)){
                pa->componente=p->componente;
            }
            restablecerPrev();
            pa=pa->sgteVertice;
        }
        p=p->sgteVertice;
    }
    p=pGrafo;
    while(p!=NULL){
        a=p->adyacente;
        while(a!=NULL){
            a->componente=p->componente;
            a=a->sgteArista;
        }
        p=p->sgteVertice;
    }
}

grafo grafo::boruvska(){
    pvertice p,psmt;
    parista a;
    grafo MST;
    int menor,inicio,fin;
    p=pGrafo;
    while(p!=NULL){
        MST.insertarVertice(p-> datoOrigen);
        p=p->sgteVertice;
    }
    MST.colocarComponente();
    MST.restablecerPrev();
    MST.nroComponentes=MST.nroVertices-(MST.nroAristas)/2;
    while(MST.nroComponentes!=1){
        for(int i=1;i<=MST.nroComponentes;i++){
            menor=2147483647;
            psmt=MST.pGrafo;
            while(psmt!=NULL){
                if(psmt->componente==i){
                    p=buscarVertice(psmt->datoOrigen);
                    a=p->adyacente;
                    while(a!=NULL){
                        if(menor>a->peso && !MST.buscaCamino(p->datoOrigen,a->datoDestino)){
                            menor=a->peso;
                            inicio=p->datoOrigen;
                            fin=a->datoDestino;
                        }
                        MST.restablecerPrev();
                        a=a->sgteArista;
                    }
                    if(!MST.buscaArista(inicio,fin)){
                        MST.insertarArista(inicio,fin,menor);
                        MST.insertarArista(fin,inicio,menor);
                    }
                }
                psmt=psmt->sgteVertice;
            }
        }
        MST.colocarComponente();
        MST.restablecerPrev();
        MST.nroComponentes=MST.nroVertices-(MST.nroAristas)/2;
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
    grafo mst=g.boruvska();
    mst.imprimirGrafo();
}