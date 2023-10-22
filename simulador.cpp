#include <bits/stdc++.h>

using namespace std;

/*Alunos
Nome: Erick Rodrigues Fraga 
Matricula: 190086815
Nome: Arthur Barreiros de Oliveira Mota
Matriculas: 190102829
*/

/* Como Compilar
g++ -Wall -o simulador simulador.cpp
C++
*/

int main(int argc, char *argv[]) {

	string f_type = ".obj";

	//Verifica se o arquivo foi adicionado no argumento
	if(argc != 2){
		cout << "Erro no input de arquivo." << endl;
		return -1;
	}

	//Transforma o nome do arquivo em uma string
	string f_name = argv[1];

	//Verifica se o arquivo é .obj
    if (f_name.find(f_type) == string::npos) {
		cout << "Erro de extenção de arquivo." << endl;
		return -1;
	}

	//Abre o arquivo
	ifstream f_obj;
  	f_obj.open (f_name, ios::in);
	vector<int> v_data;

	//Armazena o texto do arquivo em um vetor
	if (f_obj) {        
		int value; 
		while ( f_obj >> value ) {
			v_data.push_back(value);
		}
	}

	//Fecha o arquivo
	f_obj.close();

	int e_data = int(v_data.size());
	int j = 0;
	vector<int> op = {-1,2,2,2,2,2,2,2,2,3,2,2,2,2,1};

	//Loop usado para descobrir o menor endereço de dados que foram chamados no programa
	//O programa não identifica um endereço caso o mnemonico que chamou o endereçor for um jump
	while(j < int(v_data.size())){
		int aux_1 = v_data[j];

		for (int i = 0; i < op[aux_1] - 1; i++) {
			j += 1;
			if((v_data[j] < e_data)&&((aux_1 > 8)||(aux_1 <5))&&(v_data[j] > 0)) {
				e_data = v_data[j];
			}
			}
		j += 1;
	}

	//Parte principal do program, que identificaos comandos e mostra o que foi pedido
	int acc = 0;
	for(int pc = 0; pc < int(v_data.size()); pc += 0){
		switch (v_data[pc]) {
			case 1:
				cout<<"ADD"<<endl;
				pc += 1;
				acc += v_data[v_data[pc]];
				pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				break;
			case 2:
				cout<<"SUB"<<endl;
				pc += 1;
				acc -= v_data[v_data[pc]];
				pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				break;
			case 3:
				cout<<"MULT"<<endl;
				pc += 1;
				acc = acc * v_data[v_data[pc]];
				pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				break;
			case 4:
				cout<<"DIV"<<endl;
				pc += 1;
				acc = acc/v_data[v_data[pc]];
				pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
					break;
			case 5:
				cout<<"JMP"<<endl;
				pc += 1;
				pc = v_data[pc];
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				//Este if é usado para identificar se o jump vai para a região de memoria de dados
				if (e_data <= pc){
					cout<<"SEGMENTATION FAULT"<<endl;
					return -1;
				}
				//getchar();
				break;
			case 6:
				cout<<"JMPN"<<endl;
				pc += 1;
				if(acc < 0) pc = v_data[pc];
				else pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				//Este if é usado para identificar se o jump vai para a região de memoria de dados
				if (e_data <= pc){
					cout<<"SEGMENTATION FAULT"<<endl;
					return -1;
				}
				//getchar();
				break;
			case 7:
				cout<<"JMPP"<<endl;
				pc += 1;
				if(acc > 0) pc = v_data[pc];
				else pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				//Este if é usado para identificar se o jump vai para a região de memoria de dados
				if (e_data <= pc){
					cout<<"SEGMENTATION FAULT"<<endl;
					return -1;
				}
				//getchar();
				break;
			case 8:
				cout<<"JMPZ"<<endl;
				pc += 1;
				if(acc == 0) pc = v_data[pc];
				else pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				//Este if é usado para identificar se o jump vai para a região de memoria de dados
				if (e_data <= pc){
					cout<<"SEGMENTATION FAULT"<<endl;
					return -1;
				}
				//getchar();
				break;
			case 9:
				cout<<"COPY"<<endl;
				pc += 1;
				v_data[v_data[pc+1]] = v_data[v_data[pc]];
				pc += 2;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				break;
			case 10:
				cout<<"LOAD"<<endl;
				pc += 1;
				acc = v_data[v_data[pc]];
				pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				break;
			case 11:
				cout<<"STORE"<<endl;
				pc += 1;
				v_data[v_data[pc]] = acc;
				pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				break;
			case 12:
				cout<<"INPUT"<<endl;
				int entrada;
				pc += 2;
				cin >> entrada;
				v_data[v_data[pc-1]] = entrada;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				break;
			case 13:
				cout<<"OUTPUT"<<endl;
				pc += 1;
				int saida = v_data[v_data[pc]];
				pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<" SAIDA <- "<<saida<<endl;
				break;
		}
		if (v_data[pc] == 14){
			pc+=1;
			cout<<"STOP"<<endl;
			cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
			break;
		}
	}

	return 0;
}