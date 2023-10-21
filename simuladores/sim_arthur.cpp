#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
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

	map<int, int>Opcode;

	//Adding the elements
	Opcode[1] = 2;
	Opcode[2] = 2;
	Opcode[3] = 2;
	Opcode[4] = 2;
	Opcode[5] = 2;
	Opcode[6] = 2;
	Opcode[7] = 2;
	Opcode[8] = 2;
	Opcode[9] = 3;
	Opcode[10] = 2;
	Opcode[11] = 2;
	Opcode[12] = 2;
	Opcode[13] = 2;
	Opcode[14] = 1;

	string f_type = ".obj";

	if(argc != 2){
		cout << "Erro no input de arquivo." << endl;
		return -1;
	}

	string f_name = argv[1];

    if (f_name.find(f_type) == string::npos) {
		cout << "Erro de extenção de arquivo." << endl;
		return -1;
	}

	ifstream f_obj;
  	f_obj.open (f_name, ios::in);
	vector<int> v_data;

	if (f_obj) {        
		int value; 
		while ( f_obj >> value ) {
			v_data.push_back(value);
		}
	}

	f_obj.close();
	//int pc = 0;
	int e_data = int(v_data.size());

	for(int j = 0; j < int(v_data.size()); j++){
		for (auto op :Opcode){
			if (op.first == v_data[j]) {
				for (int i = 0; i < op.second - 1; i++) {
					j++;
					if((v_data[j] < e_data)&&((op.first > 8)||(op.first <5))&&(v_data[j] > 0)) e_data = v_data[j];
				}
			}
		}
	}

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
				pc = v_data[v_data[pc]];
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				if (e_data >= pc){
					cout<<"SEGMENTATION FAULT"<<endl;
					return -1;
				}
				break;
			case 6:
				cout<<"JMPN"<<endl;
				pc += 1;
				if(acc < 0) pc = v_data[v_data[pc]];
				else pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				if (e_data >= pc){
					cout<<"SEGMENTATION FAULT"<<endl;
					return -1;
				}
				break;
			case 7:
				cout<<"JMPP"<<endl;
				pc += 1;
				if(acc > 0) pc = v_data[v_data[pc]];
				else pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				if (e_data >= pc){
					cout<<"SEGMENTATION FAULT"<<endl;
					return -1;
				}
				break;
			case 8:
				cout<<"JMPZ"<<endl;
				pc += 1;
				if(acc == 0) pc = v_data[v_data[pc]];
				else pc += 1;
				cout<<"PC <- "<<pc<<" ACC <- "<<acc<<endl;
				if (e_data >= pc){
					cout<<"SEGMENTATION FAULT"<<endl;
					return -1;
				}
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