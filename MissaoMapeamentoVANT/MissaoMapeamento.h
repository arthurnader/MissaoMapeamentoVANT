#ifndef MISSAOMAPEAMETO_H_INCLUDED
#define MISSAOMAPEAMENTO_H_INCLUDED

#pragma once
#include "Poligono.h"

class MissaoMapeamento
{
private:
	Poligono areaMapeada;
	vector<Point> rota;
	int numeroDePontosDaRota;
	int modoDeMapeamento;

public:
	//MissaoMapeamento() {};
	MissaoMapeamento(Poligono mapa, int modo);
	void mostrarRota();

	//funcoes do modoDeMapeamento 1:
	double acharYMaximo();
	void gerarRota();

	//funcoes do modoDeMapeamento 2:
	void identificarParametros();
	void mapeamentoHorizontal(int verticeInicial);
	void mapeamentoVertical(int verticeInicial);
	void mapeamentoInclinado(int verticeInicial);

};

#endif //MISSAOMAPEAMENTO_H_INCLUDED