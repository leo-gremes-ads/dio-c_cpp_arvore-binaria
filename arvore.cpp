#include <iostream>

using namespace std;

// Nós da árvore
class No
{
	public:
	int valor;
	No* esq;
	No* dir;
	
	No(int numero)
	{
		valor = numero;
		esq = NULL;
		dir = NULL;
	}
};

class Arvore
{
	private:
	// Representação da árvore em uma linha (contendo atributos como altura e fator de desbalanceamento)
	void imprimir_no(No* no)
	{
		if (no != NULL) {
			cout << " " << no->valor << "(" << calcular_altura(no) << "," << fator_desbalanceamento(no) << ") [";
			imprimir_no(no->esq);
			cout << " , ";
			imprimir_no(no->dir);
			cout << " ]";
		}
	}

	// Calcular altura do nó
	int calcular_altura(No* no)
	{
		if (no == NULL)
			return 0;
		else
			return max(calcular_altura(no->esq), calcular_altura(no->dir)) + 1;
	}

	// Calcular fator de desbalanceamento, ou seja, diferença de altura entre os filhos
	// Caso seja entre -1 e 1, a árvore é considerada balanceada
	int fator_desbalanceamento(No* no)
	{
		return calcular_altura(no->esq) - calcular_altura(no->dir);
	}

	// Rotações de nós para balancear a árvore
	void res(No* &raiz)	// Rotação para esquerda simples
	{
		No* sub_dir = raiz->dir;
		No* tmp = sub_dir->esq;
		
		sub_dir->esq = raiz;
		raiz->dir = tmp;
		raiz = sub_dir;
	}

	void rds(No* &no)	// Rotação para direita simples
	{
		No* sub_esq;
		No* tmp;

		sub_esq = no->esq;
		tmp = sub_esq->dir;
		sub_esq->dir = no;
		no->esq = tmp;
		no = sub_esq;
	}

	void red(No* &no)	// Rotação para a esquerda dupla
	{
		rds(no->dir);
		res(no);
	}

	void rdd(No* &no)	// Rotação para a direita dupla
	{
		res(no->esq);
		rds(no);
	}

	// Algorítmo para balancear a árvore recursivo, começando a partir da raíz
	// Se o fator de desbalanceamento for negativo, o lado direito está maior, portanto deve ser feita rotação a esquerda
	// a rotação pode ser simples ou dupla, dependendo do fator de desbalanceamento do filho
	// filhos com o mesmo sinal, rotação simples, caso contrário, rotação dupla
	void balancear_subarvore(No* &no)
	{
		int fb, fb_filho;

		fb = fator_desbalanceamento(no);
		if (fb >= 2) {
			fb_filho = fator_desbalanceamento(no->esq);
			if (fb_filho >= 0)
				rds(no);
			else
				rdd(no);
		} else if (fb <= -2) {
			fb_filho = fator_desbalanceamento(no->dir);
			if (fb_filho <= 0) {
				res(no);
			} else
				red(no);
		}
		if (no->esq != NULL)
			balancear_subarvore(no->esq);
		if (no->dir != NULL)
			balancear_subarvore(no->dir);
	}

	// OBJETIVO DO DESAFIO
	// Busca na árvore recursiva começando da raíz
	// Se o valor for igual ao procurado, exibe-se a mensagem de valor encontrado
	// Caso o valor seja menor que o valor da raíz da árvore, a busca continua na sub-árvore da esquerda
	// Caso contrário, da direita
	// Quando chegamos a um nó nulo, significa que o valor não está presente na árvore
	//
	// Função exibe mensagem, mas poderia retornar no nó ou o valor caso haja necessidade de fazer alguma tratativa
	void buscar_valor(No* raiz, int valor, int nivel)
	{
		if (raiz == nullptr)
			cout << "Valor " << valor << " não encontrado!" << endl;
		else {
			if (raiz->valor == valor)
				cout << "Valor " << valor << " encontrado no nível " << nivel << endl;
			else if (raiz->valor > valor)
				buscar_valor(raiz->esq, valor, ++nivel);
			else
				buscar_valor(raiz->dir, valor, ++nivel);
		}
	}

	public:
	No* raiz;

	// Construtores
	Arvore()
	{
		raiz = NULL;
	}

	Arvore(int valor)
	{
		raiz = new No(valor);
	}

	// Inserir um valor na árvore
	// Caso a árvore esteja vazia o valor será a raíz
	// Caso contrário, se o valor for menor, fará parte da sub-árvore da esquerda e se for maior a direita
	// E assim subsequentemente até encontrar a posição onde o valor se encaixe
	void inserir(int valor)
	{
		if(raiz == NULL)
			raiz = new No(valor);
		else {
			No* atual = raiz;
			while(true) {
				if (atual->valor > valor) {
					if (atual->esq == NULL) {
						atual->esq = new No(valor);
						break;
					} else
						atual = atual->esq;
				} else if (atual->valor < valor) {
					if (atual->dir == NULL) {
						atual->dir = new No(valor);
						break;
					} else
						atual = atual->dir;
				} else {
					cout << "Número já existe na árvore" << endl;
					break;
				}
			}
		}
	}
	
	void buscar(int valor)
	{
		buscar_valor(raiz, valor, 0);
	}
	
	void balancear()
	{
		balancear_subarvore(raiz);
	}

	void imprimir()
	{
		imprimir_no(raiz);
		cout << endl;
	}
};

// Criação de uma árvore e realização das operações de inserção, busca, impressão e balanceamento
int main(void)
{
	Arvore arvore;
	arvore.inserir(50);
	arvore.inserir(30);
	arvore.inserir(56);
	arvore.inserir(32);
	arvore.inserir(70);
	arvore.inserir(85);
	arvore.inserir(80);
	arvore.buscar(80);
	arvore.buscar(56);
	arvore.buscar(55);
	arvore.inserir(32);
	arvore.imprimir();
	arvore.balancear();
	arvore.imprimir();
	arvore.buscar(80);
	arvore.buscar(56);
	arvore.buscar(55);
	return 0;
}
