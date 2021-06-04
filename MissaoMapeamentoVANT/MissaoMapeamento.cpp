#include "MissaoMapeamento.h"

MissaoMapeamento::MissaoMapeamento(Poligono mapa, int modo)
{
	this->areaMapeada = mapa;
	this->modoDeMapeamento = modo;

	if (modo == 1) {
		gerarRota();
	}
	else {
		identificarParametros();
	}

}

void MissaoMapeamento::mostrarRota()
{
	cout << "A rota sera composta pelos seguites pontos: " << endl;
	for (Point iterator : this->rota) {
		cout << "(" << iterator.get_x() << " , "
			<< iterator.get_y() << ") -> ";
	}
}

double MissaoMapeamento::acharYMaximo()
{
	vector<Point> vertices = areaMapeada.getVertices();

	double maximo = -DBL_MAX;

	for (Point iterator : vertices) {
		if (iterator.get_y() > maximo) {
			maximo = iterator.get_y();
		}
	}

	return maximo;
}


void MissaoMapeamento::gerarRota()
{
	double deltaX = 0.25, deltaY = 1.0, xMinimo = 0, xMaximo = 0;
	int contDireita = 0, contEsquerda = 0, sentido = 1;

	vector<Point> vertices = areaMapeada.getVertices();
	vector<Aresta> arestas = areaMapeada.getArestas();

	int quantidadeVertices = vertices.size() - 1;

	double coordenadaY = vertices[0].get_y() + deltaY;
	double yFinal = this->acharYMaximo();

	Point verticeEsquerdo = vertices[quantidadeVertices];
	Point verticeDireito = vertices[1];

	Aresta arestaLimitadoraEsquerda = arestas[quantidadeVertices];
	Aresta arestaLimitadoraDireita = arestas[0];

	while (coordenadaY < yFinal) {
		while (verticeDireito.get_y() < coordenadaY) {
			contDireita++;
			verticeDireito = vertices[contDireita];
			arestaLimitadoraDireita = arestas[contDireita - 1];
		}
		while (verticeEsquerdo.get_y() < coordenadaY) {
			contEsquerda++;
			verticeEsquerdo = vertices[quantidadeVertices - contEsquerda];
			arestaLimitadoraEsquerda = arestas[quantidadeVertices - contEsquerda];
		}

		xMinimo = (coordenadaY - arestaLimitadoraEsquerda.getCoefLinear()) / arestaLimitadoraEsquerda.getCoefAngular();
		xMaximo = (coordenadaY - arestaLimitadoraDireita.getCoefLinear()) / arestaLimitadoraDireita.getCoefAngular();

		if (arestaLimitadoraEsquerda.getCoefAngular() == DBL_MAX) {
			xMinimo = arestaLimitadoraEsquerda.getCoefLinear();
		}
		if (arestaLimitadoraDireita.getCoefAngular() == DBL_MAX) {
			xMaximo = arestaLimitadoraDireita.getCoefLinear();
		}

		if (sentido == 1) {
			xMinimo += deltaX;
			while (xMinimo < xMaximo) {
				Point ponto = Point(NULL, NULL, 15);
				ponto.set_x(xMinimo);
				ponto.set_y(coordenadaY);
				this->rota.push_back(ponto);

				xMinimo += deltaX;
			}
			sentido = -1;
		}
		else {
			xMaximo -= deltaX;
			while (xMaximo > xMinimo) {
				Point ponto = Point(NULL, NULL, 15);
				ponto.set_x(xMaximo);
				ponto.set_y(coordenadaY);
				this->rota.push_back(ponto);

				xMaximo -= deltaX;
			}
			sentido = 1;
		}

		coordenadaY += deltaY;
	}
}

void MissaoMapeamento::identificarParametros()
{
	int numeroVertice = 0;
	cout << "Digite o numero do vertice onde o mapeamento iniciara: ";
	cin >> numeroVertice;

	vector<Aresta> arestas = this->areaMapeada.getArestas();
	Aresta arestaGeradora = arestas[numeroVertice -1];

	if (arestaGeradora.getCoefAngular() == 0) {
		mapeamentoHorizontal(numeroVertice);
	}
	else if (arestaGeradora.getCoefAngular() == DBL_MAX) {
		mapeamentoVertical(numeroVertice);
	}
	else {
		mapeamentoInclinado(numeroVertice);
	}
}

void MissaoMapeamento::mapeamentoHorizontal(int verticeInicial)
{
}

void MissaoMapeamento::mapeamentoVertical(int verticeInicial)
{
}

void MissaoMapeamento::mapeamentoInclinado(int verticeInicial)
{
}
