// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 230 de Acepta el Reto:
// Desórdenes temporales
//
// Coste en tiempo: O(n * log(n)), n = número de habitantes
//
// Coste en espacio adicional: O(k), k = constante
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const bool QUIERO_TESTEAR = true; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada230.txt"; // El nombre del fichero de entrada

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
	vector<size_t> habitantes;

	Entrada(DatosPrevios& datos)
	{

	}

	void escanear(istream& ist = cin)
	{
		size_t n;
		ist >> n;

		es_caso = n != 0;

		if (es_caso) {
			habitantes = vector<size_t>(n);

			for (size_t i = 0; i < n; ++i) {
				ist >> habitantes[i];
			}
		}
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	size_t desorden;

	void imprimir(ostream& ost = cout) const
	{
		ost << desorden;
	}
};

size_t mergeContando(vector<size_t>& habitantes, size_t contIzq, size_t contDer) {

	size_t contSwaps = 0;

	while (contIzq < contDer && contDer < habitantes.size() - 1) {
		
		if (habitantes[contIzq] <= habitantes[contDer]) {
			size_t aux = habitantes[contIzq];
			habitantes[contIzq] = habitantes[contDer];
			habitantes[contDer] = aux;
			++contSwaps;
			++contDer;
		}
		++contIzq;
	}

}

size_t mergeSortContando(vector<size_t>& habitantes, const size_t ini,
	const size_t fin) {

	if (ini == fin) {
		return 0;
	} else {
		size_t mitad = (ini + fin) / 2,
			izq = mergeSortContando(habitantes, ini, mitad),
			der = mergeSortContando(habitantes, mitad + 1, fin);

		return izq + der + mergeContando(habitantes, ini, mitad + 1);
	}
}

// Resolución del problema
Solucion resolver(Entrada& entrada)
{
	Solucion solucion;
	solucion.desorden =
		mergeSortContando(entrada.habitantes, 0, entrada.habitantes.size() - 1);
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