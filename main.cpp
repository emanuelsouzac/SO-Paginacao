#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> seq;

int qtdQuadros, tamSeq;

void fifo(){

    int quadros[qtdQuadros] = {0};
    int pags = 0, pont = 0, pont2 = 0;
    bool estaNoQuadro = false;

    while(pont < tamSeq){
        // Checa se o número em questão da sequência já está no quadro varrendo todo o array
        for(int i = 0; i < qtdQuadros; i++){
            if(seq[pont] == quadros[i]){
                    estaNoQuadro = true; // Caso o número seja encontrado, a variável de controle estaNoQuadro vira verdadeiro
                    break;
            }
        }
        // Do contrário, o número é inserido no quadro (array) de maneira circular
        if(estaNoQuadro == false){
            quadros[pont2] = seq[pont];
            pags++;
            pont2++;
            pont2 = pont2 % qtdQuadros; // Algoritmo para tornar a lista circular, fazendo o ponteiro retornar para o início
        }
        estaNoQuadro = false;
        pont++;
    }

    cout << "FIFO " << pags << endl;

}

void otm(){

    int quadros[qtdQuadros] = {0};
    int pags = 0, pont = 0, pont2 = 0;
    bool estaNoQuadro = false;
    bool estaNaLista[qtdQuadros] = {false};
    int pos[qtdQuadros] = {0};
    bool aux = false;
    int maisDist = 0;

    while(pont < tamSeq){
        for(int i = 0; i < qtdQuadros; i++){
            if(seq[pont] == quadros[i]){
                    estaNoQuadro = true;
                    break;
            }
        }
        // Primeiro preenche todo o array dos quadros
        if(estaNoQuadro == false && pont2 < qtdQuadros){
            quadros[pont2] = seq[pont];
            pags++;
            pont2++;
            continue;
        }
        // Após cheio, será feita a verificação OTM
        if(estaNoQuadro == false && pont2 >= qtdQuadros){
            // Varre toda a sequência a partir do número atual
            for(int i = 0; i < qtdQuadros; i++){
                for(int j = pont; j < tamSeq; j++){
                    if(quadros[i] == seq[j]){
                        estaNaLista[i] = true; // A variável estaNaLista informa se a página do quadro se encontra na sequência
                        pos[i] = j; // Guarda a posição dessa página na sequência
                        break;
                    }
                }
            }
            for(int i = 0; i < qtdQuadros; i++){
                // Caso uma determinada página presente no quadro não esteja na sequência, ela sairá para dar lugar a página da vez
                if(estaNaLista[i] == false){
                    quadros[i] = seq[pont];
                    aux = true; // A variável aux será útil para informar se a substituição já foi realizada
                    break;
                }
            }
            // Caso a substituição não tenha sido realizada, será necessário descobrir qual página está mais distante da página da vez
            if(aux == false){
                maisDist = pos[0];
                for(int i = 1; i < qtdQuadros; i++){
                    if(pos[i] > maisDist){
                        maisDist = pos[i];
                    }
                }
                for(int i = 0; i < qtdQuadros; i++){
                    // A página no quadro que está mais distante na sequência sai e dá lugar à página da vez
                    if(pos[i] == maisDist){
                        quadros[i] = seq[pont];
                    }
                }
            }
            pags++;
        }
        // Variáveis de controle retornam ao padrão
        for(int i = 0; i < qtdQuadros; i++){
            estaNaLista[i] = false;
        }
        estaNoQuadro = false;
        aux = false;
        maisDist = 0;
        pont++;
    }

    cout << "OTM " << pags << endl;

}

void lru(){

    // LRU é similar ao OTM
    // A diferença é que o OTM olha a sequência a partir do pont
    // O LRU irá olhar antes do pont, salvar as posições e usar a menor

    int quadros[qtdQuadros] = {0};
    int pags = 0, pont = 0, pont2 = 0;
    bool estaNoQuadro = false;
    int pos[qtdQuadros] = {0};
    int maisDist = 0;

    while(pont < tamSeq){
        for(int i = 0; i < qtdQuadros; i++){
            if(seq[pont] == quadros[i]){
                    estaNoQuadro = true;
                    break;
            }
        }
        if(estaNoQuadro == false && pont2 < qtdQuadros){
            quadros[pont2] = seq[pont];
            pags++;
            pont2++;
            continue;
        }
        if(estaNoQuadro == false && pont2 >= qtdQuadros){
            for(int i = 0; i < qtdQuadros; i++){
                for(int j = pont; j >= 0; j--){
                    if(quadros[i] == seq[j]){
                        // Só é necessário salvar a posição
                        // Uma vez no quadro, é certo que ele já esteve alguma vez na sequência
                        pos[i] = j;
                        break;
                    }
                }
            }
            maisDist = pos[0];
            for(int i = 1; i < qtdQuadros; i++){
                if(pos[i] < maisDist){
                    maisDist = pos[i];
                }
            }
            for(int i = 0; i < qtdQuadros; i++){
                if(pos[i] == maisDist){
                    quadros[i] = seq[pont];
                }
            }
            pags++;
        }

        estaNoQuadro = false;
        maisDist = 0;
        pont++;
    }

    cout << "LRU " << pags << endl;

}

int main()
{
    ifstream arq;
    string linha;
    int aux = 0;

    arq.open("sequencia.txt");

    while(getline(arq, linha))
    {
        if(aux == 0){
           qtdQuadros = stoi(linha);
           if (qtdQuadros == 0){
                cout << "Quantidade de quadros invalida" << endl;
                return 0;
           }
           aux++;
        }else{
            seq.push_back(stoi(linha));
        }
    }

    arq.close();

    tamSeq = seq.size();

    fifo();
    otm();
    lru();

    return 0;
}
