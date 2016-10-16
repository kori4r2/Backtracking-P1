#pragma once

#define IMPOSSIBLE 0

// Cada bit da variavel do tipo possibilities armazena a possibilidade daquele valor especifico
// poder ou nao ser aplicado na posicao a qual a variavel foi atribuida.
typedef short unsigned int possibilities;

int nextPossibility(possibilities, int);
possibilities addPossibility(possibilities);
possibilities removePossibility(possibilities);
