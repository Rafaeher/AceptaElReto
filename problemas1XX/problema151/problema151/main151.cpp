// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 151 de Acepta el Reto:
// ¿Es matriz identidad?
//
// Coste en tiempo: O(n * n), con n = dimensión de la matriz cuadrada
//
// Coste en espacio adicional: O(k), con k constante
//

#include <iostream>
#include <fstream>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada151.txt"; // El nombre del fichero de entrada

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
	bool es_identidad;

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
			es_identidad = true;

			for (size_t f = 0; f < n; ++f)
			{
				for (size_t c = 0; c < n; ++c)
				{
					size_t aux;
					ist >> aux;
					if (f == c)
					{
						es_identidad = es_identidad && aux == 1;
					}
					else
					{
						es_identidad = es_identidad && aux == 0;
					}
				}
			}

		}
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	bool es_identidad;

	void imprimir(ostream& ost = cout) const
	{
		if (es_identidad)
		{
			ost << "SI";
		}
		else
		{
			ost << "NO";
		}
	}
};

// Resolución del problema
Solucion resolver(const Entrada& entrada)
{
	Solucion solucion;
	solucion.es_identidad = entrada.es_identidad;

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