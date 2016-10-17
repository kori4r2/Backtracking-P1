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

bool table::checkMove(move *m){
	return true;
}
/*
bool table::lookAhead(move m){ // funcao que checa se a proxima jogada e valida
}
*/

void table::undoMove(){
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
				if(_mode == 3 && _current[position(_rules[i]->xg, _rules[i]->yg)] == IMPOSSIBLE)
					return false;
			}
		}else if(result == 2){
			// Remove todas as possibilidades iguais ou maiores do seu vizinho que deve ser menor
			for(int j = v; i <= _D; i++){
				_current[position(_rules[i]->xl, _rules[i]->yl)] = removePossibility(_current[position(_rules[i]->xl, _rules[i]->yl)], j);
				if(_mode == 3 && _current[position(_rules[i]->xl, _rules[i]->yl)] == IMPOSSIBLE)
					return false;
			}
		}
	}
	return true;
}

move *table::decideNextMove(){
	if(_movesStack[_tracking]->_success){ // Caso o ultimo movimento testado esteja marcado como sucesso
					     // Muda a posicao e comeca a testar novos valores
		if(_mode < 1){ // Se nao houver nenhuma heuristica aplicada, checa a posicao seguinte
			int x = _movesStack[_tracking]->_x;
			int y = _movesStack[_tracking]->_y + 1;
			if(y >= _D){
				y = 0;
				x++;
			}
			// Obtem o primeiro valor a ser testado na proxima posicao
			int v = nextPossibility(_current[position(x, y)], _D, 0);
			return (v > 0)? new move(x, y, v) : NULL; // Se nao houver possibilidades na proxima posicao, retorna NULL para backtracking
		}else{ // Caso haja, usa MVR para escolher a proxima posicao
			return NULL; // Placeholder
		}
	}else{ // Caso o ultimo movimento tenha falhado, deve tentar um novo valor, ou quando nao houver, retorna NULL avisando para fazer backtracking
		int x = _movesStack[_tracking]->_x;
		int y = _movesStack[_tracking]->_y;
		if(int i = nextPossibility(_current[position(x, y)], _D, _movesStack[_tracking]->_value) )
			return new move(x, y, i);
		return NULL;
	}
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
	_possibilities = (possibilities**)malloc(sizeof(possibilities*) * _D * _D);
	for(int i = 0 ; i < (_D * _D); i++){
		_possibilities[i] = (possibilities*)malloc(sizeof(possibilities) * _D * _D);
	}
	// Coloca a possibilidade inicial como tendo todos os movimentos possiveis
	for(int i = 0 ; i < (_D * _D); i++){
		_possibilities[0][i] = 1;
	}
	// Cria a "matriz" de valores
	_values = (unsigned char*)calloc(_D * _D, sizeof(unsigned char));
	// Cria a stack de movimentos feitos
	_movesStack = (move**)malloc(sizeof(move*) * _D * _D);
	_movesStack[0] = new move(0, 0, -1);
	// Atualiza o ponteiro para a situacao atual
	_current = _possibilities[0];
	_queue = new priorityQueue(_D, &_current);
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
			if(_mode == 3 && _current[position(i, y)] == IMPOSSIBLE)
				return false;
		}
		if(i != y){
			_current[position(x, i)] = removePossibility(_current[position(x, i)], v);
			if(_mode == 3 && _current[position(x, i)] == IMPOSSIBLE)
				return false;
		}
	}
	return rulesUpdate(x, y, v);
}

void table::solve(){ // resolve o tabuleiro usando as heuristicas determinadas na sua criacao e imprime a primeira solucao encontrada na tela
	int counter = 0;
	while(_tracking < (_D * _D) && _tracking > -1 && counter < 1000000){
		bool backtrack = true;
		move *m = decideNextMove();
		if(m != NULL){
			backtrack = false;
			_tracking++;
			for(int i = 0; i < (_D *_D); i++) // Copia as possibilidades para a proxima posicao
				_possibilities[_tracking][i] = _possibilities[_tracking-1][i];
			_movesStack[_tracking] = m; // Armazena o movimento
			if(!addNumber(m->_x, m->_y, m->_value) && _mode == 3){ // Coloca o numero na posicao, ajustando as possibilidades
				// Caso o look-ahead acuse erro, avisa que precisa fazer backtracking
				backtrack = false;
				delete(m);
			}
		}
		if(backtrack){
			_tracking--;
			_current = _possibilities[_tracking];
			_movesStack[_tracking]->_success = false;
			if(_mode > 0)
				_queue->backtrack();
		}
	}
}

table::~table(){ // destrutor
}
