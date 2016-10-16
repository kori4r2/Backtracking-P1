#pragma once

class rule{
	public:
		int xl, yl, xg, yg; // coordenadas das posicoes menor (lesser) e maior (greater)
		rule(int x1, int y1, int x2, int y2){ // construtor
		}
		bool checkRule(int x, int y){ // checa se a insercao de um elemento deve ser afetada por essa regra
			return false; // placeholder
		}
};
