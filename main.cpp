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
        for(int i = 0; i < qtdQuadros; i++){
            //cout << seq[pont] << " " << quadros[i] << endl;
            if(seq[pont] == quadros[i]){
                    estaNoQuadro = true;
                    break;
            }
        }
        if(estaNoQuadro == false){
            quadros[pont2] = seq[pont];
            pags++;
            pont2++;
            pont2 = pont2 % 4;
            //for(int i = 0; i < qtdQuadros; i++){
            //    cout << quadros[i] << " ";
            //}
            //cout << endl;
        }
        estaNoQuadro = false;
        pont++;
    }

    cout << "FIFO " << pags << endl;
}

void otm(){
    int quadros[qtdQuadros] = {0};
    int pags = 0, pont = 0;
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
        if(estaNoQuadro == false){
            for(int i = 0; i < qtdQuadros; i++){
                for(int j = pont; j < tamSeq; j++){ // <<< VERIFICAR PONT OU PONT+1 >>>
                    if(quadros[i] == seq[j]){
                        estaNaLista[i] = true;
                        pos[i] = j;
                        break;
                    }
                }
            }
            for(int i = 0; i < qtdQuadros; i++){
                if(estaNaLista[i] == false){
                    quadros[i] = seq[pont];
                    aux = true;
                    break;
                }
            }
            if(aux == false){
                maisDist = pos[0];
                for(int i = 1; i < qtdQuadros; i++){
                    if(pos[i] > maisDist){
                        maisDist = pos[i];
                    }
                }
                for(int i = 0; i < qtdQuadros; i++){
                    if(pos[i] == maisDist){
                        quadros[i] = seq[pont];
                    }
                }
            }
            pags++;
            //for(int i = 0; i < qtdQuadros; i++){
            //    cout << quadros[i] << " ";
            //}
            //cout << endl;
        }
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
    //int pags;

    //cout << "LRU " << pags << endl;
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
           aux++;
        }else{
            seq.push_back(stoi(linha));
        }
    }

    arq.close();

    tamSeq = seq.size();

    fifo();
    otm();

    return 0;
}
