// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 105 de Acepta el Reto:
// Ventas
//
// Coste en tiempo: O(k), con k constante
//
// Coste en espacio adicional: O(t), con t constante
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada105.txt"; // El nombre del fichero de entrada

class Entrada // Tipo de la entrada a leer
{
public: // Los atributos y operaciones son todos públicos por comodidad

	bool es_caso; // Solo se utiliza si la entrada no es por número de casos, para indicar si hay que tratar el caso o no
	vector<double> dia;

	void escanear(istream& ist = cin)
	{
		double ventas;
		ist >> ventas;
		es_caso = ventas != -1;

		if (es_caso)
		{
			dia.push_back(ventas);
			for (size_t i = 1; i < 6; i++)
			{
				ist >> ventas;
				dia.push_back(ventas);
			}
		}
	}
};

string numADia(const size_t& num)
{
	switch (num)
	{
	case 0: return "MARTES";
	case 1: return "MIERCOLES";
	case 2: return "JUEVES";
	case 3: return "VIERNES";
	case 4: return "SABADO";
	case 5: return "DOMINGO";
	}
}

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	size_t diaMinimo, diaMaximo;
	bool domingo_superior_a_media;

	void imprimir(ostream& ost = cout) const
	{
		if (diaMaximo != 6 && diaMinimo != 6)
		{
			ost << numADia(diaMaximo) << ' ' << numADia(diaMinimo) << ' '
				<< (domingo_superior_a_media ? "SI" : "NO");
		}
		else
			ost << "EMPATE";
	}
};

// Lectura de la entrada
inline istream& operator>>(istream& ist, Entrada& entrada)
{
	entrada.escanear(ist);
	return ist;
}

// Escritura de la salida
inline ostream& operator<<(ostream& ost, const Solucion& solucion)
{
	solucion.imprimir(ost);
	return ost;
}

// Resolución del problema
Solucion resolver(const Entrada& entrada)
{
	Solucion solucion;
	double maximasVentas = entrada.dia[0], minimasVentas = entrada.dia[0],
		media = entrada.dia[0];

	solucion.diaMaximo = 0;
	solucion.diaMinimo = 0;
	
	for (size_t i = 1; i < 6; i++)
	{
		if (maximasVentas < entrada.dia[i])
		{
			maximasVentas = entrada.dia[i];
			solucion.diaMaximo = i;
		}
		else if (maximasVentas == entrada.dia[i])
			solucion.diaMaximo = 6;


		if (minimasVentas > entrada.dia[i])
		{
			minimasVentas = entrada.dia[i];
			solucion.diaMinimo = i;
		}
		else if (minimasVentas == entrada.dia[i])
			solucion.diaMinimo = 6;

		media += entrada.dia[i];
	}

	solucion.domingo_superior_a_media = entrada.dia[5] > media / 6;
	
	return solucion;
}

// Resolución de un caso con entrada sin número de casos
bool resuelveCasoSinNumCasos()
{
	// ENTRADA
	Entrada entrada;
	cin >> entrada;
	if (!entrada.es_caso)
		return false;

	// RESOLUCIÓN
	Solucion solucion = resolver(entrada);

	// SALIDA
	cout << solucion << '\n';

	return true;
}

// Resolución de un caso con entrada con número de casos
void resuelveCasoNumCasos()
{
	// ENTRADA
	Entrada entrada;
	cin >> entrada;

	// RESOLUCIÓN
	Solucion solucion = resolver(entrada);

	// SALIDA
	cout << solucion << '\n';
}

void mainReal()
{
	if (ENTRADA_CON_NUMERO_DE_CASOS)
	{
		size_t numCasos;
		cin >> numCasos;
		for (size_t i = 0; i < numCasos; i++)
			resuelveCasoNumCasos();
	}
	else
		while (resuelveCasoSinNumCasos());
}

void testMain()
{
	std::ifstream ifs(FICHERO_ENTRADA);
	auto cinbuf = std::cin.rdbuf(ifs.rdbuf());

	mainReal();

	std::cin.rdbuf(cinbuf);
	system("pause");
}

int main()
{
	if (QUIERO_TESTEAR)
		testMain();
	else
		mainReal();

	return 0;
}