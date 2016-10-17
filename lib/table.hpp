#pragma once
#include <cstdlib>
#include "rule.hpp"
#include "possibilities.hpp"
#include "pQueue.hpp"

using namespace std;

typedef struct move{
	unsigned char _x;
	unsigned char _y;
	unsigned char _value;
	move(unsigned char x, unsigned char y, unsigned char v){
		_x = x;
		_y = y;
		_value = v;
	}
	move(int x, int y, int v){
		_x = x;
		_y = y;
		_value = v;
	}
} move;

class table{

	private:
		// Variaveis
		unsigned char _mode; // variavel que determina que heuristicas serao utilizadas
		unsigned char *_values; // vetor contendo os valores salvos em cada posição (possivel usar a funcao position para acessa-lo intuitivamente como matriz)
		int _D; // dimensoes
		int _nRules; // numero de regras aplicadas
		int _tracking; // posicao atual na lista de possibilidades (leia-se profundidade do backtracking)
		int _lastValue; // ultimi valor testado na atual iteracao
		int _lastPosition; // ultima posicao a ser alterada na atual iteracao
		rule **_rules; // lista de regras do tabuleiro
		move **_movesStack; // Pilha com movimentos feitos durante o backtracking
		possibilities **_possibilities; // lista de jogadas possiveis, incluindo historico de jogadas
		possibilities *_current; // lista de possibilidades atual
		priorityQueue *_queue; // fila de prioridade das variaveis (para aplicar o MVR)

		// Funcoes
		int position(int, int); // funcao auxiliar para poder alocar a matriz com um unico malloc
		bool checkNewMove(move*); // funcao que checa se a jogada e valida
		void printTable();
		bool rulesUpdate(int, int, int);
	public:
		table(int, unsigned char); // construtor
		void addRule(int, int, int, int); // adiciona uma nova regra ao tabuleiro
		bool addNumber(int, int, int); // adiciona um numero em determinada posicao do tabuleiro
		void solve(); // resolve o tabuleiro usando as heuristicas determinadas na sua criacao e imprime a primeira solucao encontrada na tela
		~table(); // destrutor
};
