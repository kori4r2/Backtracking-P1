#pragma once

class rule{
	public:
		int xl, yl, xg, yg; // coordenadas das posicoes menor (lesser) e maior (greater)
		rule(int x1, int y1, int x2, int y2){ // construtor
			xl = x1;
			yl = y1;
			xg = x2;
			yg = y2;
		}

		int checkRule(int x, int y){ // checa se a insercao de um elemento deve ser afetada por essa regra
			if(xl == x && yl == y)
				return 1;
			if(xg == x && yg == y)
				return 2;
			return 0;
		}
};
