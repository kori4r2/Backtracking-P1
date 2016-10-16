#pragma once
#include <cstdlib>

#define left_child(x) ((2*x) + 1)
#define right_child(x) ((2*x) + 2)
#define parent(x) ((x-1)/2)

class priorityQueue{

	private:
		int _maxSize; // tamanho maximo da fila
		int _size; // tamanho atual da fila
		int _stackSize; // tamanho da stack de itens removidos
		unsigned char *_vector; // vetor contendo os elementos da fila em uma minHeap
		unsigned char *_removed; // vetor contendo os elementos removidos, funciona como stack
		int **_ref; // endereco do vetor contendo os valores das variaveis

		void minHeapify(int);
		void moveUp(int);
		void swap(int, int);
	public:
		priorityQueue(int, int **); // construtor
		void enqueue(unsigned char); // insere um novo elemento
		unsigned char dequeue(); // remove o elemento principal, retornando seu valor
		void update(); // atualiza a fila de acordo com os valores atuais
		void backtrack(); // reinsere o ultimo elemento removido na fila e chama update()
		~priorityQueue(); // destrutor
};
