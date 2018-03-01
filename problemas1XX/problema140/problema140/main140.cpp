// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 140 de Acepta el Reto:
// Suma de dígitos
//
// Coste en tiempo: O(n), con n el número de dígitos
//
// Coste en espacio adicional: O(n), con n el número de dígitos
// Nota: el coste en espacio adicional se puede mejorar a O(k),
// con k constante
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada140.txt"; // El nombre del fichero de entrada

class Entrada // Tipo de la entrada a leer
{
public: // Los atributos y operaciones son todos públicos por comodidad

	bool es_caso; // Solo se utiliza si la entrada no es por número de casos, para indicar si hay que tratar el caso o no
	string numero;

	void escanear(istream& ist = cin)
	{
		ist >> numero;
		es_caso = numero[0] != '-';
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	vector<int> numeros;
	int total;

	void imprimir(ostream& ost = cout) const
	{
		ost << numeros[0];
		for (size_t i = 1; i < numeros.size(); i++)
			ost << " + " << numeros[i];

		ost << " = " << total;
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
	solucion.total = 0;

	for (size_t i = 0; i < entrada.numero.size(); i++)
	{
		solucion.numeros.push_back(entrada.numero[i] - '0');
		solucion.total += solucion.numeros[i];
	}

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