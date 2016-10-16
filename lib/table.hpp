#pragma once
#include <cstdlib>
#include "rule.hpp"
#include "possibilities.hpp"
#include "pQueue.hpp"

using namespace std;

class table{

	private:
		// Variaveis
		unsigned char mode; // variavel que determina que heuristicas serao utilizadas
		int _D; // dimensoes
		unsigned char *_values; // vetor contendo os valores salvos em cada posição (possivel usar a funcao position para acessa-lo intuitivamente como matriz)
		rule *_rules; // lista de regras do tabuleiro
		int _current; // posicao atual na lista de possibilidades (leia-se profundidade do backtracking)
		possibilities **_possibilities; // lista de jogadas possiveis, incluindo historico de jogadas
		priorityQueue _queue; // fila de prioridade das variaveis (para aplicar o MVR)
		// Funcoes
		bool checkMove(int x, int y, int v); // checa uma 
		int position(int x, int y){ // funcao auxiliar para poder alocar a matriz com um unico malloc
			return ((x * _D) + y);
		}
		bool lookAhead(int, int); // funcao que checa se a proxima jogada e valida
		void printTable();
	public:
		table(int i, unsigned char mode); // construtor
		void addRule(int, int); // adiciona uma nova regra ao tabuleiro
		void solve(); // resolve o tabuleiro usando as heuristicas determinadas na sua criacao e imprime a primeira solucao encontrada na tela
		~table(); // destrutor
};
