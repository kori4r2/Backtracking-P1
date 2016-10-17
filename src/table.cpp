#include "table.hpp"
/*
		// Variaveis
		unsigned char _mode; // variavel que determina que heuristicas serao utilizadas
		int _D; // dimensoes
		unsigned char *_values; // vetor contendo os valores salvos em cada posição (possivel usar a funcao position para acessa-lo intuitivamente como matriz)
		rule *_rules; // lista de regras do tabuleiro
		int _tracking; // posicao atual na lista de possibilidades (leia-se profundidade do backtracking)
		possibilities **_possibilities; // lista de jogadas possiveis, incluindo historico de jogadas
		possibilities *_current; // lista de possibilidades atual
		priorityQueue _queue; // fila de prioridade das variaveis (para aplicar o MVR)
*/
// private
int table::position(int x, int y){ // funcao auxiliar para poder alocar a matriz com um unico malloc
	return ((x * _D) + y);
}

void table::printTable(){
}

bool table::rulesUpdate(int x, int y, int v){ // Checa as regras de acordo com os parametros presentes em _current
	for(int i = 0; i < _nRules; i++){
		int result = _rules[i]->checkRule(x, y);
		if(result == 1){
			// Remove todas as possibilidades iguais ou menores do seu vizinho que deve ser maior
			for(int j = v; i > 0; i--){
				_current[position(_rules[i]->xg, _rules[i]->yg)] = removePossibility(_current[position(_rules[i]->xg, _rules[i]->yg)], j);
				if(_mode > 1 && _current[position(_rules[i]->xg, _rules[i]->yg)] == IMPOSSIBLE)
					return false;
			}
		}else if(result == 2){
			// Remove todas as possibilidades iguais ou maiores do seu vizinho que deve ser menor
			for(int j = v; i <= _D; i++){
				_current[position(_rules[i]->xl, _rules[i]->yl)] = removePossibility(_current[position(_rules[i]->xl, _rules[i]->yl)], j);
				if(_mode > 1 && _current[position(_rules[i]->xl, _rules[i]->yl)] == IMPOSSIBLE)
					return false;
			}
		}
	}
	if(_mode > 0)
		_queue->update();
	return true;
}

// bool checkNewMove(move*)
// 	vai alterando o valor do movimento para o proximo valido a cada falha, se chegar no final e o valor for 0, retorna false
bool table::checkNewMove(move *m){

	return false;
}

// public
table::table(int D, unsigned char mode){ // construtor
	_D = D;
	_mode = mode;
	_rules = NULL;
	_tracking = 0;
	_nRules = 0;
	_lastValue = -1;
	_lastPosition = -1;
	// Cria matriz de possibilidades
	_possibilities = (possibilities**)malloc(sizeof(possibilities*) * ( _D * _D + 1));
	for(int i = 0 ; i < (_D * _D); i++){
		_possibilities[i] = (possibilities*)malloc(sizeof(possibilities) * _D * _D);
	}
	// Coloca a possibilidade inicial como tendo todos os movimentos possiveis
	possibilities init = 1;
	for(int i = 1; i < _D; i++){
		init = init << 1;
		init++;
	}
	for(int i = 0 ; i < (_D * _D); i++){
		_possibilities[0][i] = init;
	}
	// Cria a "matriz" de valores
	_values = (unsigned char*)calloc(_D * _D, sizeof(unsigned char));
	// Cria a stack de movimentos feitos
	_movesStack = (move**)calloc((_D * _D + 1), sizeof(move*));
	_movesStack[0] = new move(-1, _D-1, 0);
	// Atualiza o ponteiro para a situacao atual
	_current = _possibilities[0];
	if(_mode > 0){
		_queue = new priorityQueue(_D, &_current);
		for(int i = 0; i < _D * _D; i++){
			_queue->enqueue(i);
		}
	}else
		_queue = NULL;
}

void table::addRule(int x1, int y1, int x2, int y2){ // adiciona uma nova regra ao tabuleiro
	_rules = (rule**)realloc(_rules, sizeof(rule*) * (_nRules+1));
	_rules[_nRules++] = new rule(x1, y1, x2, y2);
}

bool table::addNumber(int x, int y, int v){ // adiciona um numero em determinada posicao do tabuleiro
	_values[position(x, y)] = v;
	_current[position(x, y)] = addPossibility(IMPOSSIBLE, v);
	for(int i = 0; i < _D; i++){
		if(i != x){
			_current[position(i, y)] = removePossibility(_current[position(i, y)], v);
			if(_mode > 1 && _current[position(i, y)] == IMPOSSIBLE)
				return false;
		}
		if(i != y){
			_current[position(x, i)] = removePossibility(_current[position(x, i)], v);
			if(_mode > 1 && _current[position(x, i)] == IMPOSSIBLE)
				return false;
		}
	}
	return rulesUpdate(x, y, v);
}

void table::solve(){ // resolve o tabuleiro usando as heuristicas determinadas na sua criacao e imprime a primeira solucao encontrada na tela
	int counter = 0;
	bool backtracking = false;
	while(_tracking > -1 && _tracking < (_D * _D) && counter < 1000000){
		bool found = false;
		int x, y, i;
		// se sucesso, busca a proxima posicao a ser avaliada
		if(!backtracking){
			if(_mode > 0){ // usa MVR
				unsigned char aux = _queue::dequeue();
				x = aux / _D;
				y = aux % _D;
			}else{ // apenas pega a proxima posicao da matriz
				x = _movesStack[_tracking]->_x;
				y = _movesStack[_tracking]->_y + 1;
				if(y >= _D){
					x++;
					y = 0;
				}
			}
		// busca o proximo valor valido nessa posicao encontrada
			i = nextPossibility(_current[position(x, y)], _D, 0);
			// se houver valor valido, adiciona o valor no tabuleiro e incrementa o tracking, armazenando o movimento feito na stack
			if(i){
				for(int i = 0; i < _D * _D; i++){
					_possibilities[_tracking+1][i] = _possibilities[_tracking][i];
				}
				_current = _possibilities[_tracking + 1];
				if(!addNumber(x, y, i)){
				// se checando o look ahead encontrar erro, cancela e busca o proximo valor valido, tentando adicionar novamente ate encontrar um
					// se durante as repeticoes nao houver mais possibilidades, avisa que deu backtracking e vai pro proximo loop
				// se conseguir adicionar completamente sem erro no look ahead, atualiza a fila de prioridades
				}
				if(!backtracking){
					found = true;
					_tracking++;
					if(_mode > 0)
						_queue::update();
					_movesStack[_tracking] = new move(x, y, i);
				}
			}else{
			// se nao houver valor valido avisa que deu backtracking e vai pra proxima iteracao do loop
				if(_mode > 0)
					_queue::backtrack();
				backtracking = true;
			}
		}else{
		// se backtracking vai na posicao atual de tracking e pega o proximo valor valido dessa posicao
			// se houver valor valido, copia as possibilidades de tracking-1 para tracking e adiciona o numero na posicao novamente, avisando sucesso
				// se checando o look ahead encontrar erro, cancela e busca o proximo valor valido, tentando adicionar novamente ate encontrar um
					// se durante as repeticoes nao houver mais possibilidades, avisa que deu backtracking e vai pro proximo loop
				// se conseguir adicionar completamente sem erro no look ahead, atualiza a fila de prioridades
			// se nao houver valor valido, zera a posicao no tabuleiro, decrementa tracking e avisa que deu backtracking
		}
	}
}

table::~table(){ // destrutor
}
