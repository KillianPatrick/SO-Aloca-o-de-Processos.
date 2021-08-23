#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

void output(vector<vector<int>> Particoes){
    int i, p;
    i = 0;
    while(Particoes.size() > i){
        p = 0;
        while(Particoes[i].size() > p){
            cout << "Particoes:" << Particoes[i][p] << '\n';
            p++;
        }
        i++;
    }
}

vector<vector<int>> joinParticion(vector<vector<int>> Particoes){
    int i = 0,tamanhoParticoes,newSize;
    while(true){
        tamanhoParticoes = static_cast<int>(Particoes.size() - 1);
        if(i < tamanhoParticoes){
            if(Particoes[i][0] == -1){
                if(Particoes[i + 1][0] == -1){
                    newSize = Particoes[i][1] + Particoes[i + 1][1];
                    Particoes.erase(Particoes.begin() + i);
                    Particoes[i][1] = newSize;
                }else{
                    i++;
                }
            }else{
                i++;
            }
        }else{
            break;
        }
    }
    return Particoes;
}

vector<vector<int> > compactMemory(vector<vector<int>> Particoes) {
    int tamanhoLivre = 0;
    int index = -1, memoriaLivre = 0;
    for(int i = 0; i < Particoes.size(); i++){
        if(Particoes[i][0] == -1){
            if(!tamanhoLivre){
                if(tamanhoLivre < Particoes[i][1]){
                    tamanhoLivre = Particoes[i][1];
                    index = i;
                }
            }else{
                tamanhoLivre += Particoes[i][1];
                index = i;
            }
        }
    }
    vector<int> v = {-1,-1};
    Particoes.insert(Particoes.begin() + index,v);
    int i = 0;
    while(i != Particoes.size()){
        if(Particoes[i][0] == -1){
            if(Particoes[i][1] != -1){
                memoriaLivre += Particoes[i][1];
                Particoes.erase(Particoes.begin() + i);
                i = 0;
            }
        }
        i++;
    }
    for(i = 0; i < Particoes.size(); i++){
        if(Particoes[i][1] == -1){
            Particoes[i][1] = memoriaLivre;
        }
    }
    return Particoes;
}

int checkFreeSpace(vector<vector<int>> Particoes){
    int memoriaLivre = 0;
    for(int i = 0; i < Particoes.size(); i++){
        if(Particoes[i][0] == -1){
            memoriaLivre += Particoes[i][1];
        }
    }
    return memoriaLivre;
}

bool firstFit(vector<vector<int>> *_Particoes, int numeroProcesso, int tamanhoProcesso){
    vector<vector<int>> Particoes = *_Particoes;
    bool flag = true;
    int tamanhoMemoriaLivre = 0;
    for(int i = 0; i < Particoes.size(); i++){
        if(flag){
            if (Particoes[i][0] == -1) {
                if(Particoes[i][1] >= tamanhoProcesso){
                    tamanhoMemoriaLivre = Particoes[i][1] - tamanhoProcesso;
                    Particoes.erase(Particoes.begin() + i);
                    vector<int> v = {numeroProcesso, tamanhoProcesso};
                    Particoes.insert(Particoes.begin() + i, v);
                    if(tamanhoMemoriaLivre > 0){
                        v = {-1, tamanhoMemoriaLivre};
                        Particoes.insert(Particoes.begin() + i + 1,v);
                    }
                    flag = false;
                }
            }
        }
    }
    *_Particoes = Particoes;
    return flag;
}

bool bestFit(vector<vector<int>> *_Particoes, int numeroProcesso, int tamanhoProcesso){
    vector<vector<int>> Particoes = *_Particoes;
    bool flag = true;
    int espacoSobra = 0, espacoMemoria = -1, espacoMemoriaIndex = 0;
    for(int i =0; i < Particoes.size(); i++){
        if(Particoes[i][0] == -1){
            if(Particoes[i][1] >= tamanhoProcesso){
                espacoSobra = Particoes[i][1] - tamanhoProcesso;
                if(espacoMemoria == -1){
                    espacoMemoria = espacoSobra;
                }
                if(espacoMemoria >= espacoSobra){
                    flag = false;
                    espacoMemoria = espacoSobra;
                    espacoMemoriaIndex = i;
                }
            }
        }
    }
    if(!flag){
        if(espacoMemoria == 0){
            Particoes[espacoMemoriaIndex][0] = numeroProcesso;
            Particoes[espacoMemoriaIndex][1] = tamanhoProcesso;
        }else{
            Particoes[espacoMemoriaIndex][0] = numeroProcesso;
            Particoes[espacoMemoriaIndex][1] = tamanhoProcesso;
            vector<int> v = {-1, espacoMemoria};
            Particoes.insert(Particoes.begin() + espacoMemoriaIndex + 1, v);
        }
    }
    *_Particoes = Particoes;
    return flag;
}

bool worstFit(vector<vector<int>> *_Particoes, int numeroProcesso, int tamanhoProcesso){
    vector<vector<int>> Particoes = *_Particoes;
    bool flag = true;
    int espacoSobra = 0, espacoMemoria = -1, espacoMemoriaIndex = 0;
    for(int i =0; i < Particoes.size(); i++){
        if(Particoes[i][0] == -1){
            if(Particoes[i][1] >= tamanhoProcesso){
                espacoSobra = Particoes[i][1] - tamanhoProcesso;
                if(espacoMemoria == -1){
                    espacoMemoria = espacoSobra;
                }
                if(espacoMemoria <= espacoSobra){
                    flag = false;
                    espacoMemoria = espacoSobra;
                    espacoMemoriaIndex = i;
                }
            }
        }
    }
    if(!flag){
        if(espacoMemoria == 0){
            Particoes[espacoMemoriaIndex][0] = numeroProcesso;
            Particoes[espacoMemoriaIndex][1] = tamanhoProcesso;
        }else{
            Particoes[espacoMemoriaIndex][0] = numeroProcesso;
            Particoes[espacoMemoriaIndex][1] = tamanhoProcesso;
            vector<int> v = {-1, espacoMemoria};
            Particoes.insert(Particoes.begin() + espacoMemoriaIndex + 1, v);
        }
    }
    *_Particoes = Particoes;
    return flag;
}

//Testar
bool nextFit(vector<vector<int>> *_Particoes, int numeroProcesso, int tamanhoProcesso, int *_ponteiro){
    vector<vector<int>> Particoes = *_Particoes;
    bool flag = true;
    int tamanhoMemoriaLivre = 0;
    int ponteiroOriginal;
    ponteiroOriginal = *_ponteiro;
    int ponteiroInicio = ponteiroOriginal;
    int ponteiroAtual = ponteiroInicio + 1;
    while(ponteiroAtual != ponteiroInicio){
        if(ponteiroAtual > Particoes.size() - 1){
            ponteiroAtual = 0;
        }
        if(Particoes[ponteiroAtual][0] == -1){
            if(Particoes[ponteiroAtual][1] >= tamanhoProcesso){
                tamanhoMemoriaLivre = Particoes[ponteiroAtual][1] - tamanhoProcesso;
                Particoes.erase(Particoes.begin() + ponteiroAtual);
                vector<int> v = {numeroProcesso, tamanhoProcesso};
                Particoes.insert(Particoes.begin() + ponteiroAtual, v);
                if(tamanhoMemoriaLivre != 0){
                    v = {-1,tamanhoMemoriaLivre};
                    Particoes.insert(Particoes.begin() + ponteiroAtual + 1,v);
                }
                flag = false;
                break;
            }
        }
        ponteiroAtual++;
    }
    if(flag){
        if(Particoes[ponteiroInicio][0] == -1){
            if(Particoes[ponteiroInicio][1] >= tamanhoProcesso){
                tamanhoMemoriaLivre = Particoes[ponteiroInicio][1] - tamanhoProcesso;
                Particoes.erase(Particoes.begin() + ponteiroInicio);
                vector<int> v = {numeroProcesso, tamanhoProcesso};
                Particoes.insert(Particoes.begin() + ponteiroInicio, v);
                if(tamanhoMemoriaLivre != 0){
                    Particoes.insert(Particoes.begin() + ponteiroInicio + 1, v);
                }
                flag = false;
            }
        }
    }
    if(!flag){
        *_ponteiro = ponteiroAtual;
    }else{
        *_ponteiro = ponteiroOriginal;
    }
    *_Particoes = Particoes;
    return flag;
}

int main() {
    int algoritmo,compactacao,tamanhoParticao,estadoParticao,numeroProcesso,ponteiro,i = 0,p = 0;
    unsigned long long int particoes;
    cout << "Digite o algoritmo:";
    cout << "1-FF, 2-BF, 3-WF, 4-NF";
    cin >> algoritmo;
    cout << "Quantidade inicial de particoes:";
    cin >> particoes;
    //Process, Size
    vector < vector<int> > Particoes(particoes, vector<int>(2));
    cout << "Compatacao automatica:";
    cout << "(0 - Não | 1 - Sim)";
    cin >> compactacao;
    for(i = 0; i < particoes; i++) {
        cout << "Particao:" << i + 1 << '\n';
        cout << "Digite o tamanho para a particao:";
        cin >> tamanhoParticao;
        cout << "Particao esta ocupada";
        cout << "(1 - Ocupada, 0 - Livre)";
        cin >> estadoParticao;
        if (estadoParticao) {
            cout << "Digite o numero do proceso:";
            cin >> numeroProcesso;
            Particoes[i][0] = numeroProcesso;
            Particoes[i][1] = tamanhoParticao;
        } else {
            Particoes[i][0] = -1;
            Particoes[i][1] = tamanhoParticao;
        }
    }
    cout << "Ponteiro para ultima alocacao em qual lacuna: (Entre 1 e " << Particoes.size() << ')';
    cin >> ponteiro;
    ponteiro--;
    //Mostrar situação inicial
    int a;
    a=1000;
    int j;
    while(a!=0){

       cout<<"\n 1 - Alocar processo\n 2 - Finaliza processo\n 3 - Situacao\n 4 - Compactar\n 0 - Sair\n";
       cin>>a;
        if(a == 3){
            //Situação
            //Printa o cabecalho
            cout<<"\n\nTABELA SITUACAO\n-----------------------------------\n";
            cout<<"Particao\tTamanho\t\tNumero\n";
            for (i = 0; i < Particoes.size(); i++){
                //for (j = 0; j < Particoes.size(); j++) {
                    if (i == ponteiro) {
                       cout << i+1 << "|<--\t\t"<<Particoes[i][1] <<"|\t\t" << Particoes[i][0] <<"|\t\t";
                        // printf("%d <<-\t\t %d \t\t %d\n", i, array_tamP[i],array_nP[i]);
                    } else {
                        cout << i+1 << "|\t\t"<<Particoes[i][1] <<"|\t\t" << Particoes[i][0] <<"|\t\t";
                        //printf("%d \t\t %d \t\t %d\n", i, array_tamP[i], array_nP[i]);
                    }
                    cout<<"\n";
                }
            }
        }
    return 0;
}