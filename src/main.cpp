#include "table.hpp"
#include <cstdio>

#define HEURISTICA 2 // 0 = apenas backtracking, 1 = utilizando MVR, 2 = utilizando MVR e look-ahead

using namespace std;

int main(int argc, char *argv[]){

	int N, R, D;	// N - numero de testes / R - numero de restricoes / D - Dimensao do Tabuleiro
	int i, j, k;

	int x1,y1,x2,y2;

	unsigned char aux;

	scanf("%d", &N);

	for(i=0;i<N;i++){

		scanf("%d %d", &D, &R);
		table *T = new table(D, HEURISTICA, R);

		for(j=0;j<D;j++){
			for(k=0;k<D;k++){
				scanf("%hhu", &aux);
				T->addNumber(j,k,aux); // Adiciona o valor na tabela
			}
		}

		for(j=0;j<R;j++){
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			T->addRule(x1,y1,x2,y2); // confirmar parametros
		}

		T->solve();

		delete(T);
	}

	return 0;
}
