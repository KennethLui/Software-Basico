#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

//Diretivas a serem encontradas: SECTION, CONST, SPACE, IF, EQU, MACRO, ENDMACRO

vector<string> quebra_tokens(string line){
  char *buffer;
  char *Aux;
  vector<string> quebrado;

  //cout << "\nquebra_tokens recebeu: " << line << endl;
  Aux= new char[line.size() + 1]; //Cria um ponteiro para o line pq o strtok precisa de um ponteiro como argumento
  copy(line.begin(),line.end(),Aux);
  Aux[line.size()]='\0';

  buffer=strtok(Aux,".;: \n"); //Cada palavra agora e um token, ignorando os sinais

  //cout<<"\n\n Elementos de Quebrado:\n";

  while(buffer!=NULL){
      quebrado.push_back(buffer);
      //cout<<"Elemento: "<<buffer<<endl;
      buffer=strtok(NULL," .;: \n");
  }

  return quebrado;
}

void token_linha(string line, vector<string> *tokens){
  char *buffer;
  char *Aux;

  //cout << "\nquebra_tokens recebeu: " << line << endl;
  Aux= new char[line.size() + 1]; //Cria um ponteiro para o line pq o strtok precisa de um ponteiro como argumento
  copy(line.begin(),line.end(),Aux);
  Aux[line.size()]='\0';

  buffer=strtok(Aux,"\n"); //Cada palavra agora e um token, ignorando os sinais

  //cout<<"\n\n Elementos de Quebrado:\n";

  while(buffer!=NULL){
      (*tokens).push_back(buffer);
      //cout<<"Elemento: "<<buffer<<endl;
      buffer=strtok(NULL,"\n");
  }

  return;
}

void DIRETIVAS_EQU_IF(ifstream &myfile,vector<string> *tokens,map<string,int> *DIRETIVAS){
  
  string EQU = "EQU", IF = "IF", AUX;
  int AUX2=0,flag=0;
  vector<string> vector_quebrado;

  if(myfile.is_open()){
    
    int tamanho = (*tokens).size();

    for (int i=0;i<tamanho-1;i++){//cout<<(*tokens)[i];
      vector_quebrado = quebra_tokens((*tokens)[i]);
        int v=vector_quebrado.size();

        for (int b=0;b<v;b++){
          if (vector_quebrado[b]==EQU){cout<<"passou";
            //Insere o token antes no EQU no map com o seu valor atribuido
            AUX=vector_quebrado[b-1];
            AUX2=stoi(vector_quebrado[b+1]);
            (*DIRETIVAS).insert(pair <string,int> (AUX,AUX2));//cout<<"Valor de AUX: "<<AUX<<"\nVetor: "<<vector_quebrado[b]<<"\nPARA b:"<<b<<"\nValores inseridos: "<<AUX<<" E "<<AUX2<<endl;
            cout<<"\ntoken "<<i<<" :"<<(*tokens)[i]<<endl;
            /*if(i==0){cout<<"passou";
              AUX=(*tokens)[i+1];
              (*tokens)[i+1]=(*tokens)[i];
              (*tokens)[i]=AUX;
              (*tokens).erase((*tokens).begin()+(i+1));//chama função de apagar linha
              flag=1;
            }else
            (*tokens).erase((*tokens).begin()+(i+1));//chama função de apagar linha
            break;*/
            /*if(i==0){

            }else*/
            
            //Fiz assim pq usando "(*tokens).erase((*tokens).begin());" dava segmentation fault
            if(i>0){
              if(i==1){
                (*tokens).erase((*tokens).begin());
                (*tokens).erase((*tokens).begin());
              }else{
                (*tokens).erase((*tokens).begin()+i);
                }
                i=i-1;
            }
            //(*tokens).erase((*tokens).begin()+i);
            
          }
          else if (vector_quebrado[b]==IF){
            AUX=vector_quebrado[b+1];//cout<<AUX<<"Valor de AUX"<<endl;
            AUX2=(*DIRETIVAS).at(AUX);
            switch((*DIRETIVAS).at(AUX)){
              case 0:
                (*tokens).erase((*tokens).begin()+i);
                (*tokens).erase((*tokens).begin()+i);
            //chama função para apagar a linha atual e a proxima
              break;

              case 1:
                (*tokens).erase((*tokens).begin()+i);
            //chama função para apagar a linha atual
              break;

              default:
                cout<<"Caiu no default"<<endl;
              break;
            }
        
          }
        }
    //cout<<"Vetor "<<i<<":"<< (*tokens)[i]<<endl;
    }

  }
  
  myfile.close();

  return;
}

void MACROS(ifstream &myfile,vector<string> *tokens,map<string,int> *MNT,map<string,int> *MDT){
//MNT: contem os nomes das macros definidas no programa
//MDT: contem os corpos das macros
  return;
}

int main () {

  map <string,int> Mapeamento_de_linhas;
  map <string,int> DIRETIVAS,MNT,MDT;
  vector<string> tokens, quebrado; //tokens contem cada linha do codigo como 1 elemento. Quebrado quebra a linha em tokens menores

  string line,line_aux;
  ifstream myfile ("Para_Ler.txt");
  if (myfile.is_open())
  {
    myfile.seekg(3,ios::beg);
    while ( getline (myfile,line,';') ) //Pega um token como tudo antes do ;
    {
      //cout << line << "LINHA" << '\n';
      
      token_linha(line,&tokens);
      /*stringstream ss(line);
      while (getline(ss,line)){         //Separa os tokens em tokens menores separados por espaço
        
      cout<<line<<endl;
      //Pegar um linha do codigo como token
        tokens.push_back(line);
        //cout<<"Elemento   "<<line<<endl;
      //Fim do teste

      

      }*/

      getline(myfile,line); //ignora todos os caracteres depois do ;
    }

    DIRETIVAS_EQU_IF(myfile,&tokens,&DIRETIVAS);

    int k=tokens.size();
    cout<<"\n\nTamanho K de Tokens: \n"<<k<<endl;
    for (int i=0;i<k;i++){
      cout << "Tokens " << i << ": " << tokens[i] << endl;
      quebrado = quebra_tokens(tokens[i]);
        int v = quebrado.size();
        //cout << "\nTamanho de V: " << k;
        //for (int i=0;i<v;i++)
          //cout << "\nElementos depois de quebrados: " << quebrado[i]<<endl;
    }

    

    myfile.close();
  }

  else cout << "Unable to open file"; 

    //cout << "Quantidade de elementos do map:" << DIRETIVAS.size() << "\n" << "Elementos da DIRETIVAS" << endl;

    /*map<string,int>::key_compare mycomp = DIRETIVAS.key_comp();
    string highest = DIRETIVAS.rbegin()->first;     // key value of last element

    std::map<string,int>::iterator it = DIRETIVAS.begin();
    do {
      std::cout << it->first << " => " << it->second << '\n';
    } while ( mycomp((*it++).first, highest) );*/

    /*for(map<string, int >::iterator it = DIRETIVAS.begin(); it != DIRETIVAS.end(); ++it){
      std::cout << it->first << " " << it->second.first << " " << it->second.second << "\n";
    }*/

    tokens.erase(tokens.begin(),tokens.end());
    tokens.clear();
    quebrado.erase(quebrado.begin(),quebrado.end());
    quebrado.clear();
    DIRETIVAS.clear();
  return 0;
}