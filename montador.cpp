#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

/* Como Compilar
g++ -Wall -o montador montador.cpp
C++20
*/

using namespace std;

vector<int> line_error;
vector<string> type_error; // Lexico, Sintatico, Semantico

vector<string> tabela_instrucoes {"add", "sub", "mul", "div", "jmp", "jmpn", "jmpp", "jmpz", "copy", "load", "store","input", "output", "stop"};
vector<int> opcode {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14};
vector<int> tamanho {2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2 ,1};
vector<string> tabela_diretivas = {"space", "const"};

string fileExt(string input)
{
	size_t pos = input.find_last_of(".");
	input = input.substr(pos+1);
	return input;
}

string clearString(string input)
{
	regex reg(R"(\s+)");

	input = input.substr(0, input.find(";", 0)); // Remove comentarios
	boost::algorithm::to_lower(input); // Converte string para minuscula
	boost::algorithm::replace_all(input, "\t", " "); // Converte todos os tabs para espaco
	input = regex_replace(input, reg, " "); // Converte espacos consecutivos para 1 espaco
	boost::trim(input); // Remove espacos no inicio e no final

	return input;
}

bool isNullString(string input)
{
	// Encontra o primeiro caractere que nao seja espaco
	if (input.find_first_not_of(' ') != string::npos)
		return 0;

	return 1;
}

struct label
{
	string name;
	int defined; // 0 - nao definido, 1 - definido
	int value = 0;
};

void addError(string type, int line)
{
	line_error.push_back(line);
	type_error.push_back(type);
}

vector<label> tabela_simbolos;

int main(int argc, char *argv[])
{

	// Verifica se apenas um arquivo foi passado como argumento
	if(argc > 2)
	{
		cout << "Erro no input de arquivo." << endl;
		return 1;
	}

	string line;
	ifstream file(argv[1]);
	string extension = fileExt(argv[1]);
	vector<string> program; // Vetor que armazena o programa

	regex var("[a-z_][a-z0-9]*");

	int sectionData = 0, sectionText = 0, labelInst = 0;	
	// int posCount = 0;
	
	if(file.is_open())
	{
		// Leitura do arquivo e armazenamento no vetor program
		while (getline(file, line))
		{
			line = clearString(line);
			if(isNullString(line) == 0)
			{
				program.push_back(line);
			}
		}
		file.close();
	}
	else
	{
		cout << "Erro na abertura de arquivo";
		return 1;
	}

	struct label l;

	if (find(program.begin(), program.end(), "secao text") != program.end())
	{
		// Primeira passagem apenas se existe secao de texto
		for (int i = 0; i < program.size(); i++)
		{
			if (program[i].find_first_of(":") != string::npos)
			{
				string aux = program[i].substr(0, program[i].find_first_of(":"));
				if (regex_match(aux.begin(), aux.end(), var) == 1)
				{
					string sub = program[i].substr(program[i].find_first_of(":") + 1, program[i].length());
					vector<string> inst;

					if (find(tabela_simbolos.begin(), tabela_simbolos.end(), aux) != tabela_simbolos.end())
					{
						// Label ja existe
						addError("Erro Semantico", i);
					}
					else
					{	
						// Label nao existe
						// Verificar se a linha possui alguma instrucao ou diretiva
						// Caso nao possua, verificar se a proxima linha possui instrucao ou diretiva
						// Adicionar label na tabela de simbolos
						if (sub.size() == 0)
						{
							continue;
							// pegar prox linha
						}
						else
						{
							// Possui instrucao
							boost::split(inst, sub, boost::is_any_of(" "));
							boost::trim(inst[0]);
							if (find(tabela_instrucoes.begin(), tabela_instrucoes.end(), inst[0]) != tabela_instrucoes.end())
							{
								continue;
								// posCount += tamanho[find(tabela_instrucoes.begin(), tabela_instrucoes.end(), inst[0]) - tabela_instrucoes.begin()];
							}
							else
							{
								if (inst[0] == "const")
								{
									// posCount += 1;
									boost::trim(inst[1]);
									l.name = aux;
									l.defined = 1;
									l.value = stoi(inst[1]);
									tabela_simbolos.push_back(l);
								}
								else if (inst[0] == "space")
								{
									boost::trim(inst[1]);
									// posCount += stoi(inst[1]);
									l.name = aux;
									l.defined = 1;
									l.value = stoi(inst[1]);
									tabela_simbolos.push_back(l);
								}
								else
								{
									// Instrucao e diretiva nao existem
									addError("Erro Sintatico", i);
								}
							}
						}
					}
				}
				else
				{
					// Label nao eh valida
					addError("Erro Lexico", i);
				}
			}
			// Verifica se a linha tem label
				// se ha label, verificar se tem instrucao
					// se ha label e instrucao, adicionar label na tabela de simbolos
					// se ha label e nao ha instrucao, pegar prox elemento e verificar se eh instrucao
				// se nao ha label, verificar se tem instrucao
			// Verifica se a linha possui alguma instrucao

		}
	}
	else
	{
		addError("Erro Sintatico", 0);;
	}

	if (find(program.begin(), program.end(), "secao data") != program.end())
	{
		sectionData = 1;
	}

	// for (auto i : program)
	// {
	// 	cout << i << endl;
	// }
	return 0;
}
