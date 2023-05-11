#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <iterator>
#include <vector>
using namespace std;

struct Carta
{
	char nome[30];
	int nivel, dificuldade, uso, popularidade;
};

struct Jogador
{
	char nome[30];
	int pont = 0;
};

template <typename T>
class Pilha
{
private:
	T* array;
	int top;
	int size;

public:

	Pilha(int size);

	void push(T valor);
	T pop();
	T peek();
	bool isFull();
	bool isEmpty();
	void show();
};



const int numeroCartas = 12;



void criador(Carta*, int);
void criador_aleatorio(Carta*, int, const int);
int menu(int, Jogador, Jogador, Pilha<Carta>, Pilha<Carta>);
int comparador(int, Pilha<Carta>, Pilha<Carta>);

int main()
{
	system("chcp 1252> nul");

	random_device rd;
	mt19937 gen(rd());
	int a = numeroCartas / 2;
	Carta cartas[numeroCartas];
	Pilha<Carta> pilha1(numeroCartas / 2);
	Pilha<Carta> pilha2(numeroCartas / 2);
	Jogador J1, J2;
	int k = 0;
	bool fechar = false;


	cout << "Gostaria de jogar super trunfo?" << endl;
	char start; cin >> start;
	start = toupper(start);
	cin.get();



	int vez = 0;
	while (fechar == false)
	{
		switch (start)
		{
		case 'S':

			cout << endl << "Digite o nome do jogador 1: ";
			cin.getline(J1.nome, 30);
			cout << "Digite o nome do jogador 2: ";
			cin.getline(J2.nome, 30);

			cout << endl << "Gostaria de jogar com cartas [1] - prédefinidas ou [2] - geradas aleatóriamente?" << endl;
			cin >> k;

			switch (k)
			{
			case 1:
				criador(cartas, numeroCartas);

				break;
			case 2:
				try //Caso o eu esqueçaa de colocar o .txt no arquivo
				{
					criador_aleatorio(cartas, 0, numeroCartas);

					break;
				}
				catch (int numf)
				{
					return 1;
				}
			}

			//========================================================
			/*embaralhar(cartas);*/
			std::shuffle(&cartas[0], &cartas[numeroCartas], gen);

			/*pilhaCartas(cartas, pilha1, pilha2);*/
			for (int i = 0; i < numeroCartas / 2; i++)
			{
				pilha1.push(cartas[i]);
			}
			for (int i = numeroCartas / 2; i < numeroCartas; i++)
			{
				pilha2.push(cartas[i]);
			}
			//========================================================

			for (int i = 0; i < numeroCartas / 2; i++)
			{
				if (vez == 0)
				{
					vez = 1;
				}
				else if (vez == 1)
				{
					vez = 2;
				}
				else if (vez == 2)
				{
					vez = 1;
				}

				cout << endl << "--------------------------------------------------------------" << endl;

				int categoria = menu(vez, J1, J2, pilha1, pilha2);
				int dist = comparador(categoria, pilha1, pilha2);

				cout << endl << "--------------------------------------------------------------" << endl;
				if (dist == 1)
				{
					J1.pont += 10;
					pilha1.pop(); pilha2.pop();
				}
				else if (dist == -1)
				{
					J2.pont += 10;
					pilha1.pop(); pilha2.pop();
				}
				else if (dist == 0)
				{
					J1.pont += 5; J2.pont += 5;
					pilha1.pop(); pilha2.pop();
				}
				else if (dist == 2)
				{
					i--;
				}
				system("pause");
			}
			system("cls");

			cout << "Fim do jogo" << endl;

			fechar = true;
			cout << ">>> Computando Pontuação <<<" << endl << endl;
			system("pause");

			cout << endl << "O vencedor é: " << endl;

			if (J1.pont > J2.pont)
			{
				cout << J1.nome << endl;
			}
			else if (J1.pont < J2.pont)
			{
				cout << J2.nome << endl;
			}
			else
			{
				cout << "Ninguém, pois houve um empate" << endl;
			}

			cout << "Obrigado por testar" << endl;

			break;
		case 'N':
			cout << endl << "Obrigado por testar até aqui, recomendo jogar da próxima vez" << endl;
			fechar = true;

			break;
		default:
			cout << "Caractere Inválido! Por favor selecione um entre [S]im e [N]ão" << endl;

			cout << "Gostaria de jogar super trunfo?" << endl;
			cin >> start;
			cin.get();

			continue;
		}
	}

	return 0;
}

int menu(int vez, Jogador J1, Jogador J2, Pilha<Carta> pilha1, Pilha<Carta> pilha2)
{
	int categoria;
	switch (vez)
	{
	case 1:
		cout << "Jogador(a) " << J1.nome << " sua carta é a seguinte: " << endl
			<< "Nome: " << pilha1.peek().nome << endl
			<< "Nível: " << pilha1.peek().nivel << endl
			<< "Dificuldade: " << pilha1.peek().dificuldade << endl
			<< "Uso: " << pilha1.peek().uso << endl
			<< "Popularidade: " << pilha1.peek().popularidade << endl;
		break;
	case 2:
		cout << "Jogador(a) " << J2.nome << " sua carta é a seguinte: " << endl
			<< "Nome: " << pilha2.peek().nome << endl
			<< "Nível: " << pilha2.peek().nivel << endl
			<< "Dificuldade: " << pilha2.peek().dificuldade << endl
			<< "Uso: " << pilha2.peek().uso << endl
			<< "Popularidade: " << pilha2.peek().popularidade << endl;
		break;
	}

	cout << "Qual das categorias você gostaria de comparar com seu oponente?" << endl
		<< "1 - Nível" << endl
		<< "2 - Dificuldade" << endl
		<< "3 - Uso" << endl
		<< "4 - Popularidade" << endl;
	cin >> categoria;

	return categoria;
}

int comparador(int categoria, Pilha<Carta> pilha1, Pilha<Carta> pilha2)
{
	switch (categoria)
	{
	case 1:
		if (!pilha1.isEmpty() || !pilha2.isEmpty())
		{
			if (pilha1.peek().nivel > pilha2.peek().nivel)
			{
				cout << "Numa comparação de nível, a carta " << pilha1.peek().nome << " é superior a carta " << pilha2.peek().nome << endl
					<< "Portanto, o(a) jogador(a) " << 1 << " venceu esta rodada!" << endl;

				return 1;
			}
			else if (pilha1.peek().nivel < pilha2.peek().nivel)
			{
				cout << "Numa comparação de nível, a carta " << pilha2.peek().nome << " é superior a carta " << pilha1.peek().nome << endl
					<< "Portanto, o(a) jogador(a) " << 2 << " venceu esta rodada!" << endl;

				return -1;
			}
			else
			{
				cout << "Numa comparação de n�vel, a carta " << pilha1.peek().nome << " e a carta " << pilha2.peek().nome << " são equivalentes" << endl
					<< "Portanto, houve um empate!" << endl;

				return 0;
			}
		}
	case 2:
		if (!pilha1.isEmpty() || !pilha2.isEmpty())
		{
			if (pilha1.peek().dificuldade < pilha2.peek().dificuldade)
			{
				cout << "Numa comparação de dificuldade, a carta " << pilha1.peek().nome << " é superior a carta " << pilha2.peek().nome << endl
					<< "Portanto, o(a) jogador(a) " << 1 << " venceu esta rodada!" << endl;

				return 1;
			}
			else if (pilha1.peek().dificuldade > pilha2.peek().dificuldade)
			{
				cout << "Numa comparação de dificuldade, a carta " << pilha2.peek().nome << " é superior a carta " << pilha1.peek().nome << endl
					<< "Portanto, o(a) jogador(a) " << 2 << " venceu esta rodada!" << endl;

				return -1;
			}
			else
			{
				cout << "Numa comparação de dificuldade, a carta " << pilha1.peek().nome << " e a carta " << pilha2.peek().nome << " são equivalentes" << endl
					<< "Portanto, houve um empate!" << endl;

				return 0;
			}
		}
	case 3:
		if (!pilha1.isEmpty() || !pilha2.isEmpty())
		{
			if (pilha1.peek().uso > pilha2.peek().uso)
			{
				cout << "Numa comparação de uso, a carta " << pilha1.peek().nome << " é superior a carta " << pilha2.peek().nome << endl
					<< "Portanto, o(a) jogador(a) " << 1 << " venceu esta rodada!" << endl;
				return 1;
			}
			else if (pilha1.peek().uso < pilha2.peek().uso)
			{
				cout << "Numa comparação de uso, a carta " << pilha2.peek().nome << " é superior a carta " << pilha1.peek().nome << endl
					<< "Portanto, o(a) jogador(a) " << 2 << " venceu esta rodada!" << endl;

				return -1;
			}
			else
			{
				cout << "Numa comparação de uso, a carta " << pilha1.peek().nome << " e a carta " << pilha2.peek().nome << " são equivalentes" << endl
					<< "Portanto, houve um empate!" << endl;

				return 0;
			}
		}
	case 4:
		if (!pilha1.isEmpty() || !pilha2.isEmpty())
		{
			if (pilha1.peek().popularidade > pilha2.peek().popularidade)
			{
				cout << "Numa comparação de popularidade, a carta " << pilha1.peek().nome << " é superior a carta " << pilha2.peek().nome << endl
					<< "Portanto, o(a) jogador(a) " << 1 << " venceu esta rodada!" << endl;
				return 1;
			}
			else if (pilha1.peek().popularidade < pilha2.peek().popularidade)
			{
				cout << "Numa comparação de popularidade, a carta " << pilha2.peek().nome << " é superior a carta " << pilha1.peek().nome << endl
					<< "Portanto, o(a) jogador(a) " << 2 << " venceu esta rodada!" << endl;

				return -1;
			}
			else
			{
				cout << "Numa comparação de popularidade, a carta " << pilha1.peek().nome << " e a carta " << pilha2.peek().nome << " são equivalentes" << endl
					<< "Portanto, houve um empate!" << endl;

				return 0;
			}
		}
	default:
		cout << "Categoria inválida!";
		return 2;
	}
}

void criador(Carta* carta, int numeroCartas)
{
	ifstream fin;
	fin.open("Cartas.txt", ios_base::in);

	int numf = 0;
	for (int i = 0; i < numeroCartas; i++)
	{
		fin >> carta[i].nome >> carta[i].nivel >> carta[i].dificuldade >> carta[i].uso >> carta[i].popularidade;

		while ((carta[i].nivel + carta[i].dificuldade + carta[i].uso + carta[i].popularidade) > 40 || (carta[i].nivel + carta[i].dificuldade + carta[i].uso + carta[i].popularidade) < 10)
		{
			mt19937 rng(random_device{}());
			uniform_int_distribution<int> dist(1, 10);

			int decrease = dist(rng);

			switch (decrease)
			{
			case 1:
				carta[i].nivel = dist(rng);
			case 2:
				carta[i].dificuldade = dist(rng);
			case 3:
				carta[i].uso = dist(rng);
			case 4:
				carta[i].popularidade = dist(rng);
			}
		}
		numf = i;
	}

	if (numf != (numeroCartas - 1))
	{
		criador_aleatorio(carta, numf, numeroCartas);
	}

	fin.close();
}

void criador_aleatorio(Carta* carta, int numf, int numeroCartas)
{
	ifstream fin;
	fin.open("Cartas_alt.txt");

	if (!fin.is_open())
	{
		throw(numf);
	}

	for (int i = numf; i < numeroCartas; i++)
	{
		fin >> carta[i].nome;

		mt19937 rng(random_device{}());
		uniform_int_distribution<int> dist(1, 10);

		carta[i].nivel = dist(rng);
		carta[i].dificuldade = dist(rng);
		carta[i].uso = dist(rng);
		carta[i].popularidade = dist(rng);
	}

	fin.close();
}


//CONSTRUTOR:

template <typename T>
Pilha<T> ::Pilha(int s)
{
	top = -1;
	size = s;
	array = new T[size];
}


//METODOS:

template <typename T>
void Pilha<T> ::push(T valor)
{
	top = top + 1;
	array[top] = valor;
}


template <typename T>
T Pilha<T> ::pop()
{
	T retorno;

	retorno = (T)array[top];
	top = top - 1;

	return retorno;
}


template <typename T>
T Pilha<T> ::peek()	// retorna o elemento no topo
{
	T retorno;

	retorno = (T)array[top];

	return retorno;
}


template <typename T>
bool Pilha<T> ::isFull()
{
	if (top == size - 1) {
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
bool Pilha<T> ::isEmpty()
{
	if (top == -1) {
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
void Pilha<T> ::show()
{
	for (int i = 0; i <= top; i++) {
		cout << "posicao " << i << " = " << array[i] << "\n";
	}
	cout << "topo index = " << top << "\n";
}
