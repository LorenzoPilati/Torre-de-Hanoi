#include <iostream>
#include <vector>

using namespace std;

const int totalDisco = 3;
const int totalHaste = 3;

class Estado{
    public:
        vector<int> disco;
        vector<Estado*> adjacente;

    Estado(vector<int> disco){
        this->disco = disco;
    }
};

Estado *inicial;

bool estaMarcado(Estado *v, vector<Estado*> pilha){
    for(Estado *w: pilha){
        if(w == v)
            return true;
    }
    return false;
}

Estado* aprofundar(Estado *v, vector<Estado*> pilha, vector<int> estadoFinal){
    pilha.push_back(v);
    if(v->disco == estadoFinal){
        return v;
    }
    for(Estado *w: v->adjacente){
        if(!estaMarcado(w, pilha)){
            Estado *a = aprofundar(w, pilha, estadoFinal);
            if(a != NULL)
                return a;
        }
    }
    return NULL;
}

bool menorEmCima(int *P, int i){
    for(int j = 0; j < i; j++){
        if(*(P+j) == *(P+i))
            return true;
    }
    return false;
}

bool verificaSeMenor(int *P, int i, int j){
    for(int k = 0; k < i; k++){
        if(*(P+k) == j)
            return true;
    }
    return false;
}

Estado* criaEstado(vector<int> lista){
    return new Estado(lista);
}

void criaListaDeEstados(Estado* Raiz){
    vector<int> lista;
    vector<Estado*> pilha;
    int *P = Raiz->disco.data();
    for(int i = 0; i < totalDisco; i++){
        if(!menorEmCima(P, i)){
            for(int j = 1; j <= totalHaste; j++){
                if(*(P+i) != j){
                    if(!verificaSeMenor(P, i, j)){
                        lista = Raiz->disco;
                        Estado *E = aprofundar(inicial, pilha, lista);
                        if(E == NULL){
                            *(lista.data()+i) = j;
                            Raiz->adjacente.push_back(criaEstado(lista));    
                        }else{
                            Raiz->adjacente.push_back(E);
                        }
                    }
                }
            }
        }
    }
    for(Estado *E: Raiz->adjacente){
        criaListaDeEstados(E);
    }
}

int main(){
    vector<int> inicio {1,1,1};
    inicial = new Estado(inicio);
    criaListaDeEstados(inicial);
    for(Estado *P: inicial->adjacente){
        for(int x: P->disco){
            cout << x << " ";
        }
        cout << endl;
    }
}