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
// Coste en tiempo: O(m · c), con m = número de molinos y c = número de consultas
//
// Coste en espacio adicional: O(n), con m = número de molinos
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	//ifstream ifs("entrada179.txt");
	//auto cinbuf = cin.rdbuf(ifs.rdbuf());

	size_t n;
	cin >> n;

	while (n != 0)
	{
		vector<size_t> molinos(n);

		for (int i = 0; i < n; i++)
		{
			cin >> molinos[i];
		}

		size_t numConsultas;
		cin >> numConsultas;

		size_t ini, fin;

		for (size_t j = 0; j < numConsultas; ++j)
		{
			cin >> ini >> fin;
			size_t suma = 0;
			for (size_t i = ini - 1; i <= fin - 1; ++i)
			{
				suma += molinos[i];
			}

			cout << suma << '\n';
		}

		cin >> n;
	}

	//cin.rdbuf(cinbuf);
	//system("pause");

	return 0;
}

/*
const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = true; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada179.txt"; // El nombre del fichero de entrada

class DatosPrevios // Información previa a la entrada del problema
{
public: // Los atributos y operaciones son todos públicos por comodidad

	vector<int> molinos;

	void escanear(istream& ist = cin)
	{
		int numMolinos;
		cin >> numMolinos;
		molinos.resize(numMolinos);

		for (int i = 0; i < numMolinos; ++i)
		{
			cin >> molinos[i];
		}
	}
};

class Entrada // Tipo de la entrada a leer
{
public: // Los atributos y operaciones son todos públicos por comodidad

	bool es_caso; // Solo se utiliza si la entrada no es por número de casos, para indicar si hay que tratar el caso o no
	DatosPrevios datos;
	size_t ini;
	size_t fin;

	Entrada(DatosPrevios& _datos)
	{
		datos = _datos;
	}

	void escanear(istream& ist = cin)
	{
		cin >> ini >> fin;
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	int resultado;

	void imprimir(ostream& ost = cout) const
	{
		cout << resultado;
	}
};

// Resolución del problema
Solucion resolver(const Entrada& entrada)
{
	Solucion solucion;
	solucion.resultado = 0;

	for (size_t i = entrada.ini - 1; i <= entrada.fin - 1; ++i)
	{
		solucion.resultado += entrada.datos.molinos[i];
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
*/