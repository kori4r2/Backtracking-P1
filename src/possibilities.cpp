#include "possibilities.hpp"
#include <climits>

int nextPossibility(const possibilities p, const int D, const int current){
	// A variavel test armazena a possibilidade sendo testada
	possibilities test = 1 << current;
	// Percorre todas as demais possibilidades do vetor
	for(int i = current+1; i < D; i++){
		// Caso encontre uma possibilidade valida, ela sera o retorno
		if((test & p) != IMPOSSIBLE)
			return i;
		test = test << 1;
	}
	// Se nao houver mais valores possiveis, retorna 0
	return 0;
}

possibilities addPossibility(possibilities p, int v){
	possibilities v2 = v;
	v2 = 1 << (v2-1);
	return (p | v2);
}

possibilities removePossibility(possibilities p, int v){
	possibilities v2 = v;
	v2 = 1 << (v2-1);
	v2 = v2 ^ USHRT_MAX;
	return (p & v2);
}
