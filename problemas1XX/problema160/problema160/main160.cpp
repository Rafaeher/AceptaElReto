// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 160 de Acepta el Reto:
// Matrices triangulares
//
// Coste en tiempo: O(n * n), con n = dimensión de la matriz cuadrada
//
// Coste en espacio adicional: O(k), con k constante
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada160.txt"; // El nombre del fichero de entrada

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
	vector<vector<int>> matriz;

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
			matriz = vector<vector<int>>(n, vector<int>(n));

			for (size_t f = 0; f < n; ++f)
			{
				for (size_t c = 0; c < n; ++c)
				{
					ist >> matriz[f][c];
				}
			}
		}
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	bool es_triangualar;

	void imprimir(ostream& ost = cout) const
	{
		if (es_triangualar)
		{
			ost << "SI";
		}
		else
		{
			ost << "NO";
		}
	}
};

bool comprobarTriangularSuperior(const vector<vector<int>>& matriz)
{
	for (size_t f = 0; f < matriz.size(); ++f)
	{
		for (size_t c = f + 1; c < matriz.size(); ++c)
		{
			if (matriz[f][c] != 0)
			{
				return false;
			}
		}
	}

	return true;
}

bool comprobarTriangularInferior(const vector<vector<int>>& matriz)
{
	for (size_t f = 1; f < matriz.size(); ++f)
	{
		for (size_t c = 0; c < f; ++c)
		{
			if (matriz[f][c] != 0)
			{
				return false;
			}
		}
	}

	return true;
}

// Resolución del problema
Solucion resolver(const Entrada& entrada)
{
	Solucion solucion;
	solucion.es_triangualar = comprobarTriangularSuperior(entrada.matriz);
	solucion.es_triangualar = solucion.es_triangualar || comprobarTriangularInferior(entrada.matriz);

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