#include "pQueue.hpp"
/*
	private:
		int _maxSize; // tamanho maximo da fila
		int _size; // tamanho atual da fila
		unsigned char *_vector; // vetor contendo os elementos da fila em uma minHeap
		unsigned char *_removed; // vetor contendo os elementos removidos, funciona como stack
		possibilities **_ref; // endereco do vetor contendo os valores das variaveis
*/
void priorityQueue::minHeapify(int pos){
	int minPos, minValue, i = pos;
	bool swapped = true;
	while(swapped && i < _size){
		swapped = false;
		minPos = i;
		minValue = getNumber( (*_ref)[_vector[i]] );
		if(left_child(i) < _size && getNumber( (*_ref)[_vector[left_child(i)]] ) < minValue){
			minPos = left_child(i);
			minValue = getNumber( (*_ref)[_vector[left_child(i)]] );
		}
		if(right_child(i) < _size && getNumber( (*_ref)[_vector[right_child(i)]] ) < minValue){
			minPos = right_child(i);
			minValue = getNumber( (*_ref)[_vector[right_child(i)]] );
		}
		if(minPos != i){
			swap(i, minPos);
			swapped = true;
			i = minPos;
		}
	}
}

void priorityQueue::moveUp(int pos){
	while( parent(pos) > 0 && (getNumber( (*_ref)[pos] ) < getNumber( (*_ref)[parent(pos)] )) ){
		swap(pos, parent(pos));
		pos = parent(pos);
	}
}

void priorityQueue::swap(int i, int j){
	unsigned char aux = _vector[i];
	_vector[i] = _vector[j];
	_vector[j] = aux;
}

priorityQueue::priorityQueue(int D, possibilities **ref){ // construtor
	_maxSize = D * D;
	_ref = ref;
	_vector = (unsigned char*)malloc(sizeof(unsigned char) * this->_maxSize);
	_removed = (unsigned char*)malloc(sizeof(unsigned char) * this->_maxSize);
	_size = 0;
	_stackSize = 0;
}

void priorityQueue::enqueue(unsigned char newElement){ // insere um novo elemento
	_vector[_size] = newElement;
	moveUp(_size++);
}

unsigned char priorityQueue::dequeue(){ // remove o elemento principal, retornando seu valor
	swap(0, _size-1);
	_removed[_stackSize++] = _vector[_size-1];
	_size--;
	minHeapify(0);
	return _removed[_stackSize-1];
}

void priorityQueue::update(){ // atualiza a fila de acordo com os valores atuais
	for(int i = parent(_size-1); i >= 0; i--){
		minHeapify(i);
	}
}

void priorityQueue::backtrack(){ // reinsere o ultimo elemento removido na fila e o move a sua posicao correta
	_vector[_size++] = _removed[_stackSize - 1];
	_stackSize--;
//	update();
	moveUp(_size-1); // Nao leva em consideracao que _ref foi alterado, sempre que
		 	 // _ref for alterado, deve-se chamar update() antes de alterar a queue
}

priorityQueue::~priorityQueue(){ // destrutor
	_ref = NULL;
	free(_vector);
	free(_removed);
}
