#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

//Diretivas a serem encontradas: SECTION, CONST, SPACE, IF, EQU, MACRO, ENDMACRO

vector<string> quebra_tokens(string line){
  char *buffer;
  char *Aux;
  vector<string> quebrado;

  Aux= new char[line.size() + 1]; //Cria um ponteiro para o line pq o strtok precisa de um ponteiro como argumento
  copy(line.begin(),line.end(),Aux);
  Aux[line.size()]='\0';

  buffer=strtok(Aux,".,;: \n"); //Cada palavra agora e um token, ignorando os sinais

  while(buffer!=NULL){
      quebrado.push_back(buffer);
      buffer=strtok(NULL," .,;: \n");
  }

  return quebrado;
}

void token_linha(string line, vector<string> *tokens){
  char *buffer;
  char *Aux;

  transform(line.begin(), line.end(),line.begin(), ::toupper);

  Aux= new char[line.size() + 1]; //Cria um ponteiro para o line pq o strtok precisa de um ponteiro como argumento
  copy(line.begin(),line.end(),Aux);
  Aux[line.size()]='\0';

  buffer=strtok(Aux,"\n"); //Cada palavra agora e um token, ignorando os sinais


  while(buffer!=NULL){
      (*tokens).push_back(buffer);
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

    for (int i=0;i<tamanho-1;i++){
      vector_quebrado = quebra_tokens((*tokens)[i]);
        int v=vector_quebrado.size();

        for (int b=0;b<v;b++){
          if (vector_quebrado[b]==EQU){
            //Insere o token antes no EQU no map com o seu valor atribuido
            AUX=vector_quebrado[b-1];
            AUX2=stoi(vector_quebrado[b+1]);
            (*DIRETIVAS).insert(pair <string,int> (AUX,AUX2));
            //DESCOMENTA SE QUISER VER TODAS AS LINHAS COM EQU
            //cout<<"\ntoken "<<i<<" :"<<(*tokens)[i]<<endl;
            
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
            
          }
          else if (vector_quebrado[b]==IF){
            AUX=vector_quebrado[b+1];
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

    }

  }
  
  myfile.close();

  return;
}

void MACROS(ifstream &myfile,vector<string> *tokens,map<string,int> *MNT,multimap<string,vector<string>> *MDT){
//MNT: contem os nomes das macros definidas no programa
//MDT: contem os corpos das macros
  vector<string> vector_quebrado,MACRO;
  int tamanho=0, tamanho_vector=0, contador=0, aux=0, aux2=0, v=0, marcador=0, i=0;
  int *p;
  tamanho = (*tokens).size();
  p=&tamanho;

  for(int i=0;i<*p;i++){
    tamanho = (*tokens).size();
    vector_quebrado = quebra_tokens((*tokens)[i]);
    contador=0;

    //Descomenta se quiser ver o quais foram os tokens quebrados por quebra_tokens
    /*cout<<"\nVector quebrado: \n";
    for(v=0;v<vector_quebrado.size();v++)
      cout<<vector_quebrado[v]<<endl;*/

    aux=vector_quebrado.size();
    aux2=0;
    while(aux2!=aux){
      if(vector_quebrado[aux2]=="MACRO"){ 
      //DESCOMENTA SE QUISER VER A POSICAO DA PALAVRA MACRO NA LINHA
      //cout<<"\n Aux2: "<<aux2<<endl;
      marcador = i;
      //MNT informa o numero de argumentos e o local da MDT onde esta seu corpo. Como estamos usando MAP nao precisamos saber a linha
      
        contador=vector_quebrado.size()-aux2-1;

        //IDENTIFICA SE O NUMERO DE ARGUMENTOS REQUERIDOS PELA MACRO PASSA DE 4 E MOSTRA ERRO SE FOR MAIOR
        if(contador>4)
          cout<<"\nERRO:" << "\tNUMERO DE ARGUMENTOS MAIOR QUE 4 PARA A MACRO: " << vector_quebrado[aux2-1] << "\n\tNUMERO DE ARGUMENTOS USADOS: " << contador << endl;
        //Descomenta se quiser ver o numero de argumentos de cada MACRO
        //cout<<"\nNumero de argumentos: "<<contador;

        //Passa primeiro elemento como nome do vetor e contador como numero de argumentos
        
        (*MNT).insert(pair <string,int> (vector_quebrado[aux2-1],contador));
        i++;
        v=0;
        while((*tokens)[i]!="ENDMACRO"){
          MACRO.push_back((*tokens)[i]);
          i++;
          v++;
        }

        (*MDT).insert(pair <string,vector<string>> (vector_quebrado[aux2-1],MACRO));
        
        int tam_macro = MACRO.size() + 2;
        MACRO.clear();

        //APAGA A MACRO DO ARQUIVO
        for (contador = 0; contador<tam_macro; contador++){
        (*tokens).erase((*tokens).begin() + marcador);
        }
        i=i-tam_macro;
      }
      aux2++;
    }
  }

  tamanho_vector=MACRO.size();
  //cout<<"\n\nMACRO: "<<endl;
  //Se quiser printar macro precisa tirar o MACRO.clear da linha 170 depois do MDT insert
  /*for(aux=0;aux<tamanho_vector;aux++){
    cout<<MACRO[aux]<<endl;
  }*/
  MACRO.clear();
  vector_quebrado.clear();

  //PARA MOSTRAR COMO FICOU O CODIGO DEPOIS DE APAGAR DECLARACOES DE MACRO
  /*cout<<"\nComo ficou o codigo depois de apagar MACROS\n";
  for(vector<string>:: iterator it_vec = (*tokens).begin();it_vec!=(*tokens).end();++it_vec)
      cout<<*it_vec<<endl;
  */

  string nome_macro;
  vector<string> copia;
  int tam = 0, j = 0, token_quebrado = 0; i = 0;
  //Substituindo as MACROS no vetor tokens
  for(multimap<string,vector<string>>:: iterator it_MDT = (*MDT).begin(); it_MDT!=(*MDT).end();it_MDT++){
      nome_macro = it_MDT->first;
      
    for(vector<string>:: iterator it_tokens = (*tokens).begin(); it_tokens != (*tokens).end(); ++it_tokens){
      copia = quebra_tokens(*it_tokens);
      aux=copia.size();
      for (i=0;i<aux;i++){

        if(copia[i] == nome_macro){

          //IDENTIFICA SE O NUMERO DE ARGUMENTOS PASSADOS ESTA DE ACORDO COM O NUMERO DE ARGUMENTOS REQUERIDOS E MOSTRA ERRO SE NAO ESTIVER
          if ((aux-i-1)!=((*MNT).find(copia[i]) -> second))
            cout << "\nERRO:" << "\tNUMERO DE ARGUMENTOS INVALIDO PARA MACRO: " << copia[i] << "\n\tNUMERO DE ARGUMENTOS PASSADOS: " << (aux-i-1) << "\n\tNUMERO DE ARGUMENTOS REQUERIDO: " << (*MNT).find(copia[i]) -> second << endl;

          int j = it_tokens-(*tokens).begin();
          (*tokens).insert(it_tokens, it_MDT->second.begin(), it_MDT->second.end());
          it_tokens = (*tokens).begin()+j+it_MDT->second.size();
          j = it_tokens - (*tokens).begin();

          it_tokens=(*tokens).erase(it_tokens);
          
          i=aux;
        }
      }
    }

  }

  return;
}

int main () {

  map <string,int> Mapeamento_de_linhas, DIRETIVAS, MNT;
  multimap <string,vector<string>> MDT;
  vector<string> tokens, quebrado; //tokens contem cada linha do codigo como 1 elemento. Quebrado quebra a linha em tokens menores

  string line,line_aux;
  ifstream myfile ("Arquivo_original.txt");
  if (myfile.is_open())
  {
    myfile.seekg(3,ios::beg);
    while ( getline (myfile,line,';') ) //Pega um token como tudo antes do ;
    {
      
      token_linha(line,&tokens);

      getline(myfile,line); //ignora todos os caracteres depois do ;
    }

    DIRETIVAS_EQU_IF(myfile,&tokens,&DIRETIVAS);

    //DESCOMENTA SE QUISER VER COMO FICA O VECTOR TOKENS INICIALMENTE COM TODOS OS ELEMENTOS DO ARQUIVO ORIGINAL (ANTES DE SER MODIFICADA)
    /*int k=tokens.size();
    cout<<"\n\nTamanho K de Tokens: \n"<<k<<endl;
    for (int i=0;i<k;i++){
      cout << "Tokens " << i << ": " << tokens[i] << endl;
      quebrado = quebra_tokens(tokens[i]);
        int v = quebrado.size();
    }*/

    

    myfile.close();
  }

  else cout << "Unable to open file"; 

    cout << "Quantidade de elementos do map DIRETIVAS: " << DIRETIVAS.size() << "\n" << "Elementos da DIRETIVAS:" << endl;

    for(map<string, int >::iterator it = DIRETIVAS.begin(); it != DIRETIVAS.end(); ++it){
      std::cout << it->first << " " << it->second << "\n";
    }

    MACROS(myfile,&tokens,&MNT,&MDT);
    //Printar MNT
    cout<<"\nPrintando MAP MNT: "<<endl;

    for(map<string,int>::const_iterator it_MNT = MNT.begin(); it_MNT != MNT.end(); ++it_MNT){
      std::cout << it_MNT->first << " " << it_MNT->second << "\n";
    }

    //Printar MDT
    cout<<"\nPrintando MAP MDT:"<<endl;

    multimap <string, vector<string> >::const_iterator it;

    for (it = MDT.begin(); it != MDT.end(); ++it)
    {
        cout << it->first << "\t" ;

        vector<string>::const_iterator itVec;
        for (itVec = it->second.begin(); itVec != it->second.end(); ++itVec)
        {
            cout << *itVec <<" ";
        }
    cout<<endl;
    }

    cout<<endl;

    cout<<"\nCOMO FICOU O ARQUIVO FINAL:\n\n";
    for(vector<string>:: iterator it_vec = tokens.begin();it_vec!=tokens.end();++it_vec)
      cout<<*it_vec<<endl;

    ofstream arquivo_novo("Arquivo_modificado.txt");

    if (arquivo_novo.is_open()){
      for(vector<string>:: iterator it = tokens.begin(); it!= tokens.end(); ++it)
        arquivo_novo<<*it<<endl;
      arquivo_novo.close();
    }else cout<<"\nNao e possivel abrir arquivo"<<endl;

    tokens.erase(tokens.begin(),tokens.end());
    tokens.clear();
    quebrado.erase(quebrado.begin(),quebrado.end());
    quebrado.clear();
    DIRETIVAS.clear();
    MDT.clear();
    MNT.clear();
    Mapeamento_de_linhas.clear();
    MNT.clear();
    MDT.clear();
  return 0;
}