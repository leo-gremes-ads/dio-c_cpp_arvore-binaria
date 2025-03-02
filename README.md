# DIO

## Desafio de Projeto

### Desenvolvimento de um algoritmo para busca em árvores balanceadas

Neste projeto final é proposta a implementação de uma árvore balanceada para busca binária. Em nossas aulas aprendemos como este tipo de estrutura se comporta, no entanto, não tratamos a questão do balanceamento, que visa garantir sempre o melhor custo de busca neste tipo de estrutura. Este então é nosso desafio para este projeto.

O balanceamento em uma árvore é a forma de ajustar os elementos de forma que nunca aconteça o problema de desbalanceamento. Sendo que o desbalanceamento é a forma de uma árvore com suas “folhas” caídas para um único lado, como pode ser observado na figura abaixo.

O processo para uma árvore de busca balanceada é o mesmo para uma árvore binária convencional, com o adicional de uma função de balanceamento, que deve a todo momento rearranjar a estrutura de dados da árvore. /

### Solução

Foi feita a criação de uma árvore binária em C++, com algumas funções como inserir, imprimir, balancear e buscar. O algorítmo de balanceamente da árvore é feito a partir de rotações dos nós para diminuir a diferença de altura entre os filhos e o algorímto de busca é muito próximo ao de busca binária em um vetor ordenado;
