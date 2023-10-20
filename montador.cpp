#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

/*Alunos
Nome: Erick Rodrigues Fraga 
Matricula: 190086815
Nome: Arthur Barreiros de Oliveira Mota
Matriculas: 190102829
*/

/* Como Compilar
g++ -Wall -o montador montador.cpp
C++20
*/

using namespace std;

vector<int> line_error;
vector<string> type_error; // Lexico, Sintatico, Semantico
vector<string> sec_data; // Vetor que armazena a secao data 
vector<string> sec_text; // Vetor que armazena a secao text

vector<string> tabela_instrucoes {"add", "sub", "mul", "div", "jmp", "jmpn", "jmpp", "jmpz", "copy", "load", "store","input", "output", "stop"};
vector<int> opcode {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14};
vector<int> tamanho {2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2 ,1};
vector<string> tabela_diretivas = {"space", "const"};

string fileName(string input)
{
	size_t pos = input.find_last_of(".");
	input = input.substr(0, pos);
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
	int value = 0;
	int pos;
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
	fstream file(argv[1], ios::in);
	string file_name = fileName(argv[1]);
	vector<string> program; // Vetor que armazena o programa
	vector<int> data; // Vetor que armazena o programa convertido para opcodes

	regex var("^[_a-z][_a-z0-9]+");

	int posCount = 0, labelInst = 0;	
	
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

	
	// Copiar secao text para o vetor programa
	if (find(program.begin(), program.end(), "secao text")!= program.end())
	{
		// Copiar secao text para o vetor sec_text
		int i = find(program.begin(), program.end(), "secao text") - program.begin();
		for (unsigned int j = i + 1; j < program.size(); j++)
		{
			if (program[j] == "secao data")
			{
				break;
			}
			else
			{
				sec_text.push_back(program[j]);
			}
		}
	}
	else
	{
		// Nao existe secao text
		addError("Erro Sintatico", 0);
		return 1;
		// print erros e sair do programa
	}

	// Copiar secao data para o vetor sec_data
	for (unsigned int j = 0; j < program.size(); j++)
	{
		if (program[j] == "secao text")
		{
			break;
		}
		else if (program[j] == "secao data")
		{
			continue;
		}
		else
		{
			sec_data.push_back(program[j]);
		}
	}

	program.clear();
	program = sec_text;
	program.insert(program.end(), sec_data.begin(), sec_data.end()); // Ordena o vetor program com a secao text e data

	struct label l;

// Primeira passagem => adicao de labels na tabela de simbolos
	for (unsigned int i = 0; i < program.size(); i++)
	{
		if (program[i].find_first_of(":") != string::npos)
		{
			if (labelInst == 1)
			{
				// Labels seguidas
				addError("Erro Semantico", i+1);
			}
			else
			{
				string aux = program[i].substr(0, program[i].find_first_of(":"));
				boost::trim(aux);
				int correct_label;
				if (aux.size() == 1){
					regex x("[_a-z]");
					correct_label = regex_match(aux.begin(), aux.end(), x);
				}
				else
				{
					correct_label = regex_match(aux.begin(), aux.end(), var);
				}
				if (correct_label == 1 && aux.size() <= 30 && find(tabela_instrucoes.begin(), tabela_instrucoes.end(), aux) == tabela_instrucoes.end())
				{
					string sub = program[i].substr(program[i].find_first_of(":") + 1, program[i].length());
					vector<string> inst;

					if (find_if(tabela_simbolos.begin(), tabela_simbolos.end(), [aux](label const& l) {return l.name == aux;}) != tabela_simbolos.end())
					{
						// Label ja existe
						addError("Erro Semantico", i+1);
					}
					else
					{	
						// Label nao existe
						if (sub.size() == 0)
						{
							// Instrucao prox linha
							labelInst = 1;
							l.name = aux;
							continue;
						}
						
						else
						{
							// Possui instrucao
							boost::trim(sub);
							boost::split(inst, sub, boost::is_any_of(" "));
							if (inst.size() > 2 || inst.size() < 2) {
								// Vetor com mais de 2 argumentos ou menos de 2 argumentos diferente de stop e space
								boost::trim(inst[0]);
								if (inst[0] != "stop" && inst[0] != "space")
								{
									addError("Erro Sintatico", i+1);
									continue;
								}
							}
							if (find(tabela_instrucoes.begin(), tabela_instrucoes.end(), inst[0]) != tabela_instrucoes.end())
							{
								l.name = aux;
								l.value = 0;
								l.pos = posCount;
								tabela_simbolos.push_back(l);
								posCount += tamanho[find(tabela_instrucoes.begin(), tabela_instrucoes.end(), inst[0]) - tabela_instrucoes.begin()];
							}
							else
							{
								if (inst[0] == "const")
								{	
									boost::trim(inst[1]);
									l.name = aux;
									l.value = stoi(inst[1]);
									l.pos = posCount;
									tabela_simbolos.push_back(l);
									posCount++;
								}
								else if (inst[0] == "space")
								{
									if (inst.size() == 2)
									{
										boost::trim(inst[1]);
										l.name = aux;
										l.value = stoi(inst[1]);
										l.pos = posCount;
										posCount += stoi(inst[1]);
										tabela_simbolos.push_back(l);
									}
									else
									{
										l.name = aux;
										l.value = 0;
										l.pos = posCount;
										tabela_simbolos.push_back(l);
										posCount++;
									}
									
								}
								else
								{
									// Instrucao e diretiva nao existem
									addError("Erro Lexico", i+1);
								}
								
							}
						}
					}
				}
			}
		}
		// Nao ha label na linha
		else
		{
			vector <string> inst;
			boost::split(inst, program[i], boost::is_any_of(" "));
			if (inst.size() > 2 || inst.size() < 2) {
				// Vetor com mais de 2 argumentos ou menos de 2 argumentos diferente de stop e space
				boost::trim(inst[0]);
				if (inst[0] != "stop" && inst[0] != "space")
				{
					addError("Erro Sintatico", i+1);
					continue;
				}
			}
			if (find(tabela_instrucoes.begin(), tabela_instrucoes.end(), inst[0]) != tabela_instrucoes.end())
			{
				if (labelInst == 1)
				{
					l.value = 0;
					l.pos = posCount;
					tabela_simbolos.push_back(l);
					labelInst = 0;
				}
				posCount += tamanho[find(tabela_instrucoes.begin(), tabela_instrucoes.end(), inst[0]) - tabela_instrucoes.begin()];
			}
			else
			{	
				if (inst[0] == "space")
				{
					if (inst.size() == 2)
					{
						boost::trim(inst[1]);
						if (labelInst == 1)
						{
							l.value = stoi(inst[1]);
							l.pos = posCount;
							tabela_simbolos.push_back(l);
							labelInst = 0;
						}
						posCount += stoi(inst[1]);
					}
					else
					{
						if (labelInst == 1)
						{
							l.value = 0;
							l.pos = posCount;
							tabela_simbolos.push_back(l);
							labelInst = 0;
						}
						posCount++;
					}
					
				}
				else if (inst[0] == "const")
				{
					if (labelInst == 1)
					{
						l.value = stoi(inst[1]);
						l.pos = posCount;
						tabela_simbolos.push_back(l);
						labelInst = 0;
					}
					posCount++;
				}
				else
				{
					// Instrucao e diretiva nao existem
					addError("Erro Lexico", i+1);
				}
			}
		}
	}

	// Segunda passagem => Verificacao de erros dos operandos e geracao do codigo objeto
	for(unsigned int i = 0; i < program.size(); i++)
	{
		vector<string> inst;
		if (program[i].find_first_of(":") != string::npos)
		{
			// Achou label, remover label da string
			string aux = program[i].substr(program[i].find_first_of(":") +1 , program[i].length());
			boost::trim(aux);
			boost::split(inst, aux, boost::is_any_of(" "));
			if (inst.size() < 2)
			{
				// Vetor com mais de 2 argumentos ou menos de 2 argumentos diferente de stop e space
				boost::trim(inst[0]);
				if (inst[0] != "stop" && inst[0] != "space" && find(line_error.begin(), line_error.end(), i+1) == line_error.end())
				{
					// Testa se a linha ja foi marcada como erro caso nao seja stop ou space
					addError("Erro Sintatico", i+1);
					continue;
				}
			}
			if (find(tabela_instrucoes.begin(), tabela_instrucoes.end(), inst[0]) != tabela_instrucoes.end())
			{
				if (inst.size() == 1)
				{
					if (inst[0] == "stop")
					{
						data.push_back(14);
					}
					else
					{
						if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
						{
							addError("Erro Lexico", i+1);
						}						
						// Instrucao nao existe ou nao tem argumentos
					}
				}
				else
				{
					boost::trim(inst[1]);
					vector<string> args;
					// Testar se existe + no argumento
						// Se sim, verificar se o valor somado esta no range
						// Se nao, erro
					if (inst[0] == "copy")
					{
						boost::split(args, inst[1], boost::is_any_of(",+"));
						auto ferreira = find_if(tabela_simbolos.begin(), tabela_simbolos.end(), [args](label const& l) {return l.name == args[0];});
						if (ferreira != tabela_simbolos.end())
						{
							// abc: se primeira label tem +
							int abc = inst[1].find_first_of("+") < inst[1].find_first_of(",") ? 2 : 1;
							auto jorge = find_if(tabela_simbolos.begin(), tabela_simbolos.end(), [args,abc](label const& l) {return l.name == args[abc];});
							if (jorge != tabela_simbolos.end())
								{
									//push copy, posicao da label 1 + argumento+ (se existe), posicao da label 2 + argumento+ (se existe)  
									data.push_back(9);
									data.push_back(ferreira -> pos + (inst[1].find_first_of("+") < inst[1].find_first_of(",") ? stoi(args[1]) : 0));
									data.push_back(jorge -> pos  + (inst[1].find_last_of("+") > inst[1].find_first_of(",") && (inst[1].find_last_of("+") != string::npos) ? stoi(args[abc + 1]) : 0));
								}
							else
							{
								if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
								{
									addError("Erro Semantico", i+1);
								}
							}
						}
						else
						{
							if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
							{
								addError("Erro Semantico", i+1);
							}
						}	
					}
					else
					{
						boost::split(args, inst[1], boost::is_any_of("+"));
						auto ferreira = find_if(tabela_simbolos.begin(), tabela_simbolos.end(), [inst](label const& l) {return l.name == inst[1];});						
						if (ferreira != tabela_simbolos.end())
						{
							data.push_back(find(tabela_instrucoes.begin(), tabela_instrucoes.end(), inst[0]) - tabela_instrucoes.begin() + 1);
							data.push_back(ferreira -> pos + (inst[1].find_first_of("+") != string::npos ? stoi(args[1]) : 0));
						}
						else
						{
							if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
							{
								addError("Erro Semantico", i+1);
							}
						}
					}						
				}
			}
			else
			{
				if (inst[0] == "const")
				{
					boost::trim(inst[1]);
					if (inst[1].find_first_not_of("0123456789") == string::npos)
					{
						data.push_back(stoi(inst[1]));
					}
					else
					{
						if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
						{
							addError("Erro Sintatico", i+1);
						}
					}
				}
				else if (inst[0] == "space")
				{
					if (inst.size() == 1)
					{
						data.push_back(0);
					}
					else if (inst[1].find_first_not_of("0123456789") == string::npos)
					{
						for (int i; i < stoi(inst[1]); i++)
						{
							data.push_back(0);
						}
					}
					else
					{
						if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
						{
							addError("Erro Sintatico", i+1);
						}
					}		
				}
				else
				{
					if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
					{
						addError("Erro Lexico", i+1);
					}
				}
			}
			// Nao eh instrucao, testar const e space
		}
		else
		// Nao tem label
		{
			// Testar se eh instrucao
			boost::split(inst, program[i], boost::is_any_of(" "));
			if (inst.size() < 2)
			{
				// Vetor com mais de 2 argumentos ou menos de 2 argumentos diferente de stop e space
				boost::trim(inst[0]);
				if (inst[0] != "stop" && inst[0] != "space" && find(line_error.begin(), line_error.end(), i+1) == line_error.end())
				{
					// Testa se a linha ja foi marcada como erro caso nao seja stop ou space
					addError("Erro Sintatico", i+1);
					continue;
				}
			}
			if (find(tabela_instrucoes.begin(), tabela_instrucoes.end(), inst[0]) != tabela_instrucoes.end())
			{
				
				if (inst.size() == 1)
				{
					if (inst[0] == "stop")
					{
						data.push_back(14);
					}
					else
					{
						if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
						{
							addError("Erro Lexico", i+1);
						}						
						// Instrucao nao existe ou nao tem argumentos
					}
				}
				else
				{
					boost::trim(inst[1]);
					vector<string> args;
					// Testar se existe + no argumento
						// Se sim, verificar se o valor somado esta no range
						// Se nao, erro
					if (inst[0] == "copy")
					{
						boost::split(args, inst[1], boost::is_any_of(",+"));
						auto ferreira = find_if(tabela_simbolos.begin(), tabela_simbolos.end(), [args](label const& l) {return l.name == args[0];});
						if (ferreira != tabela_simbolos.end())
						{
							// abc: se primeira label tem +
							int abc = inst[1].find_first_of("+") < inst[1].find_first_of(",") ? 2 : 1;
							auto jorge = find_if(tabela_simbolos.begin(), tabela_simbolos.end(), [args,abc](label const& l) {return l.name == args[abc];});
							if (jorge != tabela_simbolos.end())
								{
									//push copy, posicao da label 1 + argumento+ (se existe), posicao da label 2 + argumento+ (se existe)  
									data.push_back(9);
									data.push_back(ferreira -> pos + (inst[1].find_first_of("+") < inst[1].find_first_of(",") ? stoi(args[1]) : 0));
									data.push_back(jorge -> pos  + (inst[1].find_last_of("+") > inst[1].find_first_of(",") && (inst[1].find_last_of("+") != string::npos) ? stoi(args[abc + 1]) : 0));
								}
							else
							{
								if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
								{
									addError("Erro Semantico", i+1);
								}
							}
						}
						else
						{
							if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
							{
								addError("Erro Semantico", i+1);
							}
						}	
					}
					else
					{
						boost::split(args, inst[1], boost::is_any_of("+"));
						auto ferreira = find_if(tabela_simbolos.begin(), tabela_simbolos.end(), [inst](label const& l) {return l.name == inst[1];});						
						if (ferreira != tabela_simbolos.end())
						{
							data.push_back(find(tabela_instrucoes.begin(), tabela_instrucoes.end(), inst[0]) - tabela_instrucoes.begin() + 1);
							data.push_back(ferreira -> pos + (inst[1].find_first_of("+") != string::npos ? stoi(args[1]) : 0));
						}
						else
						{
							if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
							{
								addError("Erro Semantico", i+1);
							}
						}
					}						
				}
			}
			else
			{
				if (find(line_error.begin(), line_error.end(), i+1) == line_error.end())
				{
					addError("Erro Semântico", i+1);
				}
			}
		}
			
	}

	// transformacao vetor -> string
	stringstream ss;
	for (auto j = data.begin(); j != data.end(); j++)
	{
		ss << *j << " ";
	}

	// Escrita em arquivo se nao ha erro
	if (type_error.size() == 0)
	{
		fstream fileOut(file_name + ".obj", ios::out);
		fileOut << ss.str();
		fileOut.close();
	}
	else
	{
		for (unsigned int i = 0; i < type_error.size(); i++)
		{
			cout << "Linha:" << line_error[i] << " Tipo: " << type_error[i] << endl;
		}
	}
	
	return 0;
}
