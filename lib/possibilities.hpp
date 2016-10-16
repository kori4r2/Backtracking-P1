#pragma once

#define IMPOSSIBLE 0

// Cada bit da variavel do tipo possibilities armazena a possibilidade daquele valor especifico
// poder ou nao ser aplicado na posicao a qual a variavel foi atribuida.
typedef short unsigned int possibilities;

int getNumber(const possibilities);
bool isValid(const possibilities, const int);
int nextPossibility(const possibilities, const int, const int);
possibilities addPossibility(const possibilities, const int);
possibilities removePossibility(const possibilities, const int);
