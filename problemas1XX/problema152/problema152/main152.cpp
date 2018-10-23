// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 152 de Acepta el Reto:
// Va de modas...
//
// Coste en tiempo: O(n * n), con n = número de elementos
// Nota: se puede conseguir con coste en tiempo O(n) empleando un mapa no ordenado
//
// Coste en espacio adicional: O(n), con n = número de elementos
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada152.txt"; // El nombre del fichero de entrada

class DatosPrevios // Información previa a la entrada del problema
{
public: // Los atributos y operaciones son todos públicos por comodidad

	void escanear(istream& ist = cin)
	{

	}
};

class Entrada // Tipo de la entrada a leer
{
public: // Los atributos y operaciones son todos públicos por comodidad

	bool es_caso; // Solo se utiliza si la entrada no es por número de casos, para indicar si hay que tratar el caso o no
	vector<int> numeros;

	Entrada(DatosPrevios& datos)
	{
	
	}

	void escanear(istream& ist = cin)
	{
		size_t n;
		ist >> n;

		es_caso = n != 0;

		if (es_caso)
		{
			numeros = vector<int>(n);

			for (size_t i = 0; i < n; ++i)
			{
				ist >> numeros[i];
			}
		}
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	int moda;

	void imprimir(ostream& ost = cout) const
	{
		ost << moda;
	}
};

// Resolución del problema
Solucion resolver(const Entrada& entrada)
{
	vector<pair<int, int>> repeticiones;

	for (size_t i = 0; i < entrada.numeros.size(); ++i)
	{
		bool insertado = false;

		for (size_t j = 0; j < repeticiones.size(); ++j)
		{
			if (repeticiones[j].first == entrada.numeros[i])
			{
				insertado = true;
				++repeticiones[j].second;
			}
		}

		if (!insertado)
		{
			repeticiones.push_back({ entrada.numeros[i], 1 });
		}
	}

	pair<int, int> moda = { repeticiones[0].first, repeticiones[0].second };

	for (size_t i = 0; i < repeticiones.size(); ++i)
	{
		if (repeticiones[i].second > moda.second)
		{
			moda = { repeticiones[i].first, repeticiones[i].second };
		}
	}

	Solucion solucion;
	solucion.moda = moda.first;

	return solucion;
}

// Lectura de datos previos al resto de la entrada
inline istream& operator>>(istream& ist, DatosPrevios& datos)
{
	datos.escanear(ist);
	return ist;
}

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

// Resolución de un caso con entrada sin número de casos
bool resuelveCasoSinNumCasos(DatosPrevios& datos)
{
	// ENTRADA
	Entrada entrada(datos);
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
void resuelveCasoNumCasos(DatosPrevios& datos)
{
	// ENTRADA
	Entrada entrada(datos);
	cin >> entrada;

	// RESOLUCIÓN
	Solucion solucion = resolver(entrada);

	// SALIDA
	cout << solucion << '\n';
}

void mainReal()
{
	DatosPrevios datos;
	cin >> datos;

	if (ENTRADA_CON_NUMERO_DE_CASOS)
	{
		size_t numCasos;
		cin >> numCasos;
		for (size_t i = 0; i < numCasos; i++)
			resuelveCasoNumCasos(datos);
	}
	else
		while (resuelveCasoSinNumCasos(datos));
}

void testMain()
{
	ifstream ifs(FICHERO_ENTRADA);
	auto cinbuf = cin.rdbuf(ifs.rdbuf());

	mainReal();

	cin.rdbuf(cinbuf);
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