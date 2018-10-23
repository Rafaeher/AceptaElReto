// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 149 de Acepta el Reto:
// San Fermines
//
// Coste en tiempo: O(n), con n = número de toros
//
// Coste en espacio adicional: O(k), con k constante
//

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada149.txt"; // El nombre del fichero de entrada

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
	size_t velocidad;

	Entrada(DatosPrevios& datos)
	{

	}

	void escanear(istream& ist = cin)
	{
		size_t n;
		ist >> n;

		es_caso = !(!ist);

		if (es_caso)
		{
			velocidad = 0;

			for (size_t i = 0; i < n; ++i)
			{
				size_t siguiente;
				ist >> siguiente;
				velocidad = max(velocidad, siguiente);
			}
		}
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	size_t velocidad;

	void imprimir(ostream& ost = cout) const
	{
		ost << velocidad;
	}
};

// Resolución del problema
Solucion resolver(const Entrada& entrada)
{
	Solucion solucion;
	solucion.velocidad = entrada.velocidad;

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