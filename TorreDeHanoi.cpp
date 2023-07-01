#include <iostream>
#include <vector>

using namespace std;

const int totalHaste = 3;
int totalDisco;

//Estados
class Estado{
    public:
        vector<int> disco;
        vector<Estado*> adjacente;
        bool marcado = false;
        int heuristica;
        int custo = 0;
        int f; //função F

    //Contrutor calcula heuristica com a formula da somatoria do peso de cada disco vezes o peso de cada haste
    Estado(vector<int> disco){
        int heuristica = 0;
        this->disco = disco;
        for(int i = 0; i < totalDisco; i++){
            heuristica += (i+1) * ((3-disco[i])*2);
        }
        this->heuristica = heuristica;
        this->f = this->custo + this->heuristica;
    }
};

//Fução para a impressão do vector de estados no mode "( x y ... z )"
void showLista(vector<int> lista){
    cout << "( ";
    for(int x: lista){
        cout << x << " ";
    }
    cout << ")";
}

//Função que verifica se existe um menor na haste escolhida sendo i indice do disco verificado e j a haste
bool verificaSeMenor(int *P, int i, int j){
    for(int k = 0; k < i; k++){
        if(P[k] == j)
            return true;
    }
    return false;
}

//Função que verifca se o disco está presente no vetor escolhido
Estado* estaNoVetor(vector<int> *disco, vector<Estado*> *vetor){
    for(Estado *w: *vetor){
        if(w->disco == *disco)
            return w;
    }
    return NULL;
}

//Função que cria os estados adjacentes de um estado escolhido
void criaAdjacencia(Estado *Raiz, vector<Estado*> *criados){

    //Verifica se a adjacencia está vazia
    if(Raiz->adjacente.size() == 0){
        vector<int> vetor;
        Estado *existente;

        //Impressão da Raiz
        cout << "RAIZ:" << Raiz->heuristica << " ( ";
        for(int x: Raiz->disco){
            cout << x << " ";
        }
        cout << ")\n";

        //Percorre o indice dos discos verificado cada disco por vez
        for(int i = 0; i < totalDisco; i++){

            //Verifica se tem um disco menor em cima do disco verificado
            if(!verificaSeMenor(Raiz->disco.data(), i, Raiz->disco[i])){

                //Percorre todas as hastes
                for(int j = 1; j <= totalHaste; j++){

                    //Verifica se a haste é diferente da que o disco já está
                    if(Raiz->disco[i] != j){

                        //Verifica se existe um disco menor na haste sendo verificada
                        if(!verificaSeMenor(Raiz->disco.data(), i, j)){
                            vetor = Raiz->disco;
                            vetor[i] = j;
                            existente = estaNoVetor(&vetor, criados);
                            
                            //Verifica se o estado já existe
                            if(existente == NULL){
                                Estado *a = new Estado(vetor);
                                criados->push_back(a);
                                Raiz->adjacente.push_back(a);

                                cout << "   CRIADO:" << a->heuristica << " ( ";
                                for(int x: a->disco){
                                    cout << x << " ";
                                }
                                cout << ")\n";
                            }else{
                                Raiz->adjacente.push_back(existente);

                                cout << "   ADICIONADO:" << existente->heuristica << " ( ";
                                for(int x: existente->disco){
                                    cout << x << " ";
                                }
                                cout << ")\n";
                            }
                        }
                    }
                }
            }
        }
        cout << endl;
    }
}

//Função que mostra todos os estados, se precisar
void mostrarEstados(Estado *Raiz, vector<Estado*> *visitados){
    if(!estaNoVetor(&Raiz->disco, visitados)){
        visitados->push_back(Raiz);
        cout << "( ";
        for(int x: Raiz->disco){
            cout << x << " ";
        }
        cout << ")\n";
        for(Estado *P: Raiz->adjacente){
            mostrarEstados(P, visitados);
        }
    }
}

//Busca em Largura
Estado* buscaEmLargura(Estado *Raiz, vector<int> *estadoFinal, vector<Estado*> *criados, int *cont){
    vector<Estado*> F;
    Estado *v;

    F.push_back(Raiz);
    criados->push_back(Raiz);

    while(F.size() > 0){
        v = F.front();
        criaAdjacencia(v, criados);

        for(Estado *w: v->adjacente){

            if(!w->marcado){
                w->marcado = true;
                *cont = *cont+1;

                if(w->disco == *estadoFinal){
                    return w;
                }
                F.push_back(w);
            }
        }
        F.erase(F.begin());
    }
    return NULL;
}

//Busca em Profundidade
Estado* buscaEmProfundidade(Estado *v, vector<int> *estadoFinal, vector<Estado*> *criados, vector<Estado*> *visitados, vector<Estado*> *caminho, int *cont){
    Estado *adjacente;
    visitados->push_back(v);
    caminho->push_back(v);
    *cont = *cont+1;

    if(v->disco == *estadoFinal){
        caminho->pop_back();
        return v;
    }

    criaAdjacencia(v, criados);

    for(Estado *w: v->adjacente){
        adjacente = estaNoVetor(&w->disco, visitados);
        if(adjacente == NULL){
            Estado *a = buscaEmProfundidade(w, estadoFinal, criados, visitados, caminho, cont);
            if(a != NULL)
                return a;
        }
    }

    caminho->pop_back();
    return NULL;
}

//Função que procura o Estado com menor Heuristica *não visitado* (GAMBIARRA) do vetor
Estado* procuraMenor(vector<Estado*> *estados){
    int valor = 999;
    Estado *menor = NULL;
    for(Estado *e: *estados){
        if(e->f < valor && !e->marcado/*GAMBIARRA*/){
            valor = e->f;
            menor = e;
        }
    }
    return menor;
}

//Função procura e retorna o indice do Estado no vetor
int procuraEstado(vector<int> *discos, vector<Estado*> *Estados){
    int i = 0;
    for(Estado *e: *Estados){
        if(e->disco == *discos){
            return i;
        }
        i++;
    }
    return 0;
}

//Busca A*, alterado
Estado* buscaAEstrela(Estado *Raiz, vector<int> *estadoFinal, vector<Estado*> *criados, int *cont){
    vector<Estado*> V, E;

    V.push_back(Raiz);

    while(V.size() > 0){
        Estado *t = procuraMenor(&V);

        if(t->disco == *estadoFinal){
            return t;
        }
        criaAdjacencia(t, criados);

        for(Estado *u: t->adjacente){
            int Uc = t->custo + 1;

            //Verifica se U não esta em V mas etá em E e se o custo de U é menor igual ao custo calculado Uc
            if(!estaNoVetor(&u->disco, &V) && estaNoVetor(&u->disco, &E) && u->custo <= Uc){
                int i = procuraEstado(&u->disco, &E);
                E.erase(E.begin()+i);
            }
            V.push_back(u);
            u->custo = Uc;
        }
        *cont += 1;
        t->marcado = true;
        E.push_back(t);
    }
    return NULL;
}

int main(){
    int busca, cont = 0;
    vector<int> inicio, fim;
    vector<Estado*> criados, visitados, caminho;
    Estado *inicial, *final;

    cout << "Escolha o numero de discos: " << endl;
    cin >> totalDisco;

    for(int i = 0; i < totalDisco; i++){
        inicio.push_back(1);
        fim.push_back(3);
    }

    inicial = new Estado(inicio);

    cout << "Tipo de Busca:\nEm Largura(1), Em Profundidade(2), A*(3)\n";
    cin >> busca;
    switch(busca){
        case 1:
            final = buscaEmLargura(inicial, &fim, &criados, &cont);
            showLista(final->disco);
            cout << "\nEstados Visitados:" << cont << endl;
        break;
        case 2:
            final = buscaEmProfundidade(inicial, &fim, &criados, &visitados,&caminho,&cont);

            //Imprime o acminho realizado pelo Profundidade
            for(Estado *e: caminho){
                showLista(e->disco);
                cout << " -> ";
            }
            showLista(final->disco);
            cout << "\nEstados Visitados:" << cont << endl;
        break;
        case 3:
            final = buscaAEstrela(inicial, &fim, &criados, &cont);
            showLista(final->disco);
            cout << "\nEstados Visitados:" << cont << endl;
        break;
        default:
            cout << "Opcao invalida\n";
    }
}