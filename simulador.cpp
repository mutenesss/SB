#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

using namespace std;

int main(int argc, char *argv[])
{
	// Verifica se apenas um arquivo foi passado como argumento
	if(argc != 1)
	{
		cout << "Erro no input de arquivo." << endl;
		return 1;
	}

	string line;
	fstream file(argv[1], ios::in);
	vector<int> program;
	int num;
	
	if(file.is_open())
	{
		// Leitura do arquivo e armazenamento no vetor program
		while (getline(file, line))
		{
			stringstream iss (line);
			while (iss >> num)
			{
				program.push_back(num);
			}
		}
		file.close();
	}
	for(auto i : program)
	{
		cout << i << endl;
	}
}