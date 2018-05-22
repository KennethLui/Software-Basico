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

void MACROS(ifstream &myfile,vector<string> *tokens,map<string,int> *MNT,multimap<string,vector<string>> *MDT){
//MNT: contem os nomes das macros definidas no programa
//MDT: contem os corpos das macros
  vector<string> vector_quebrado,MACRO;
  int tamanho=0, tamanho_vector=0, contador=0, aux=0, aux2=0, v=0, marcador=0, i=0;
  int *p;
  tamanho = (*tokens).size();
  p=&tamanho;
  //while(((*tokens)[i])!=(*tokens).end()){
  //for(vector<string>:: iterator percorre = (*tokens).begin();percorre!=(*tokens).end();++percorre)
  for(int i=0;i<*p;i++){
    tamanho = (*tokens).size();
    vector_quebrado = quebra_tokens((*tokens)[i]);
    contador=0;

    cout<<"\nVector quebrado: \n";
    for(v=0;v<vector_quebrado.size();v++)
      cout<<vector_quebrado[v]<<endl;

    aux=vector_quebrado.size();
    aux2=0;
    while(aux2!=aux){
      if(vector_quebrado[aux2]=="MACRO"){ cout<<"\n Aux2: "<<aux2<<endl;
      marcador = i;
      //MNT informa o numero de argumentos e o local da MDT onde esta seu corpo. Como estamos usando MAP nao precisamos saber a linha
      
        contador=vector_quebrado.size()-aux2-1;
        cout<<"\nNumero de argumentos: "<<contador;
        /*v = aux2+1;
        while(v<vector_quebrado.size()){ //Conta quantos parametros a MACRO tem -> contador
        cout<<"Entrou"<<endl;
        contador++;
        }*/
        //Passa primeiro elemento como nome do vetor e tamanho_vector como numero de argumentos
        
        (*MNT).insert(pair <string,int> (vector_quebrado[aux2-1],contador));
        i++;
        /*do{cout<<"Entrou"<<endl;
          MACRO.push_back((*tokens)[i]);
          i++;
        }while((*tokens)[i]!="ENDMACRO");*/
        v=0;
        while((*tokens)[i]!="ENDMACRO"){
          cout<<"Entrou"<<endl;
          MACRO.push_back((*tokens)[i]);
          i++;
          v++;
        }

        (*MDT).insert(pair <string,vector<string>> (vector_quebrado[aux2-1],MACRO));
        
        int tam_macro = MACRO.size() + 2;
        MACRO.clear();

        //APAGA A MACRO DO ARQUIVO
        for (contador = 0; contador<tam_macro; contador++){
        cout<<"\nApagou\n"<<endl;
        (*tokens).erase((*tokens).begin() + marcador);
        }
        i=i-tam_macro;
      }
      aux2++;
      /*if((vector_quebrado[aux2]=="SECTION")&&(vector_quebrado[aux2+1]=="DATA")){
        cout<<"Chegou no SECTION DATA\n";
        i=tamanho;
      }*/
    }
  }
  //i++;
  //}
  tamanho_vector=MACRO.size();
  cout<<"\n\nMACRO: "<<endl;
  //Se quiser printar macro precisa tirar o MACRO.clear da linha 170 depois do MDT insert
  /*for(aux=0;aux<tamanho_vector;aux++){
    cout<<MACRO[aux]<<endl;
  }*/
  MACRO.clear();
  vector_quebrado.clear();

  string nome_macro;
  int tam = 0, j = 0;
  //Substituindo as MACROS no vetor tokens
  for(multimap<string,vector<string>>:: iterator it_MDT = (*MDT).begin(); it_MDT!=(*MDT).end();it_MDT++){
      nome_macro = it_MDT->first;

      /*tam = (*tokens).size();
      for(int cont = 0; cont < tam; cont++){
        if((*tokens)[cont] == nome_macro){
          j = cont
          (*tokens).insert((*tokens).begin() + cont, it_MDT->second.begin(), it_MDT->second.end());
          cont = j+it_MDT->second.size();
          (*tokens).erase((*tokens).begin() + cont);
        }
      }*/
    
    for(vector<string>:: iterator it_tokens = (*tokens).begin(); it_tokens != (*tokens).end(); ++it_tokens){
      if(*it_tokens == nome_macro){
        //it_tokens++;
        int j = it_tokens-(*tokens).begin();
        (*tokens).insert(it_tokens, it_MDT->second.begin(), it_MDT->second.end());
        it_tokens = (*tokens).begin()+j+it_MDT->second.size();
        j = it_tokens - (*tokens).begin();

        /*if((it_tokens)==(*tokens).end()){cout<<"\n\nENTROU END\n\n";
          (*tokens).pop_back();}
          else cout<<"\nENTROU ELSE\n";*/
        it_tokens=(*tokens).erase(it_tokens);cout<<"\n\nAPAGOU\n\n";
        
        /*if((it_tokens) == (*tokens).end()){cout<<"\nEntrou"<<endl;
          (*tokens).end()=it_tokens-1;
          (*tokens).erase((*tokens).begin() + j);
        }else
        (*tokens).erase((*tokens).begin() + j);*/
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

    MACROS(myfile,&tokens,&MNT,&MDT);
    //Printar MNT
    cout<<"\nPrintando MAP MNT: "<<endl;
    /*for(map<string,int>::const_iterator it_MNT = MNT.begin(); it_MNT != MNT.end(); ++it_MNT){
      std::cout << it_MNT->first << " " << it_MNT->second.first << " " << it_MNT->second.second << "\n";
    }*/

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
    for(vector<string>:: iterator it_vec = tokens.begin();it_vec!=tokens.end();++it_vec)
      cout<<*it_vec<<endl;

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