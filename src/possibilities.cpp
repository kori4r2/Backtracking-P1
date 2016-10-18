#include "possibilities.hpp"
#include <climits>
#include <cstdio>

int getNumber(const possibilities p){
	possibilities test = 1;
	int counter = 0;
	for(int i = 0; i < 9; i++){
		if((test & p) != IMPOSSIBLE)
			counter++;
		test = test << 1;
	}
	return counter;
}

bool isValid(const possibilities p, const int test){
	possibilities t = 1 << (test-1);
	return((t & p) != IMPOSSIBLE);
}

int nextPossibility(const possibilities p, const int D, const int current){
	// A variavel test armazena a possibilidade sendo testada
	possibilities test = 1 << current;
	// Percorre todas as demais possibilidades do vetor
	for(int i = current+1; i < D; i++){
		// Caso encontre uma possibilidade valida, ela sera o retorno
		if((test & p) != IMPOSSIBLE)
			return (i + 1);
		test = test << 1;
	}
	// Se nao houver mais valores possiveis, retorna 0
	return 0;
}

possibilities addPossibility(const possibilities p, const int v){
	possibilities v2 = (possibilities)v;
	v2 = 1 << (v2-1);
	return (p | v2);
}

possibilities removePossibility(const possibilities p, const int v){
	possibilities v2 = v;
	v2 = 1 << (v2-1);
	v2 = v2 ^ USHRT_MAX;
	return (p & v2);
}
