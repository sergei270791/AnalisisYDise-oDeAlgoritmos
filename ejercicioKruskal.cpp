#include <iostream>
using namespace std;

void intercambiar(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}

void ordQuick(int vector[], int inicio, int fin) {
	int i,j,central; //indices
	int pivote;
	central=(inicio+fin)/2;
	pivote=vector[central];
	i=inicio;
	j=fin;
	while(i<=j)
	{
		while(vector[i]<pivote) i++;
		while(vector[j]>pivote) j--;
		if (i<=j)
		{
			intercambiar(vector[i],vector[j]);
			i++;
			j--;
		}
	}
	if (inicio<j)
		ordQuick(vector,inicio,j);
	if (i<fin)
		ordQuick(vector,i,fin);
}

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
        void insertarVertice(int);
        void insertarArista(int,int,int);
        void imprimirGrafo();
        void restablecerPrev();
        pvertice buscarVertice(int);
        bool buscaCamino(int,int);
        grafo kruskal();
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
            nroAristas++;
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

grafo grafo::kruskal(){
    pvertice p;
    parista a;
    grafo MST;
    p=pGrafo;
    int i=0;
    int* D=new int[nroAristas];
    while(p!=NULL){
        a=p->adyacente;
        while(a!=NULL){
            D[i]=a->peso;
            i++;
            a=a->sgteArista;
        }
        MST.insertarVertice(p->datoOrigen);
        p=p->sgteVertice;
    }
    ordQuick(D,0,nroAristas-1);
    i=0;
    while(i<nroAristas){
        p=pGrafo;
        int cont=0;
        while(p!=NULL){
            a=p->adyacente;
            while(a!=NULL){
                if(a->peso==D[i]){ // aca faltaraia ponerle que no forme ciclo
                    if(!MST.buscaCamino(p->datoOrigen,a->datoDestino)){
                        MST.restablecerPrev();
                        MST.insertarArista(p->datoOrigen,a->datoDestino,a->peso);
                        MST.insertarArista(a->datoDestino,p->datoOrigen,a->peso);
                    }
                    cont++;
                }
                a=a->sgteArista;
            }
            p=p->sgteVertice;
        }
        i+=cont;
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
    grafo mst=g.kruskal();
    mst.imprimirGrafo();
}