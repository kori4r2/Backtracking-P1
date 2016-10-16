#pragma once
#include <cstdlib>

class priorityQueue{

	private:
		int _maxSize; // tamanho maximo da fila
		unsigned char *_vector; // vetor contendo os elementos da fila em uma minHeap
		unsigned char *_removed; // vetor contendo os elementos removidos, funciona como stack
		int **_ref; // endereco do vetor contendo os valores das variaveis
	public:
		priorityQueue(int, int **); // construtor
		void push(unsigned char); // insere um novo elemento
		unsigned char pop(); // remove o elemento principal, retornando seu valor
		void update(); // atualiza a fila de acordo com os valores atuais
		void backtrack(); // reinsere o ultimo elemento removido na fila e chama update()
		~priorityQueue(); // destrutor
};
