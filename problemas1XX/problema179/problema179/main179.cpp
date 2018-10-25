// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 179 de Acepta el Reto:
// Molinos de viento
//
// Coste en tiempo: O(c), con c = número de consultas
//
// Coste en espacio adicional: O(k), con k constante
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada179.txt"; // El nombre del fichero de entrada

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
	DatosPrevios datos;
	vector<size_t> molinos;

	Entrada(DatosPrevios& _datos)
	{

	}

	void escanear(istream& ist = cin)
	{
		size_t numMolinos;
		size_t numConsultas;

		ist >> numMolinos;

		es_caso = numMolinos != 0;

		if (es_caso)
		{
			molinos = vector<size_t>(numMolinos + 1, 0);

			for (size_t i = 1; i < molinos.size(); ++i)
			{
				ist >> molinos[i];
			}
		}
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	vector<size_t> resultados;

	void imprimir(ostream& ost = cout) const
	{
		for (size_t i = 0; i < resultados.size() - 1; ++i)
		{
			ost << resultados[i] << '\n';
		}

		ost << resultados[resultados.size() - 1];
	}
};

void calcularSumasParciales(vector<size_t>& vect)
{
	for (size_t i = 1; i < vect.size(); ++i)
	{
		vect[i] += vect[i - 1];
	}
}

// Resolución del problema
Solucion resolver(Entrada& entrada)
{
	Solucion solucion;
	size_t numConsultas;

	cin >> numConsultas;
	calcularSumasParciales(entrada.molinos);

	for (size_t i = 0; i < numConsultas; ++i)
	{
		size_t ini, fin;
		size_t resultado;

		cin >> ini >> fin;
		resultado = entrada.molinos[fin] - entrada.molinos[ini - 1];
		solucion.resultados.push_back(resultado);
	}

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

	int n;
	cin >> n;
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