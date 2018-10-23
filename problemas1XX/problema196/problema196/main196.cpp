// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 196 de Acepta el Reto:
// Sudokus vacíos
//
// Coste en tiempo: O(n * n), con n = dimensión de la matriz
// Nota: dado que un sudoku siempre es 9 x 9, se puede considerar
// que el coste en tiempo es O(t), con t constante
//
// Coste en espacio adicional: O(k), con k constante
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = true; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada196.txt"; // El nombre del fichero de entrada

const size_t DIM_SUDOKU = 9;
const size_t NUM_BUENOS_DIGITOS = 32;

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
	vector<vector<bool>> sudoku;

	Entrada(DatosPrevios& datos)
	{

	}

	void escanear(istream& ist = cin)
	{
		sudoku = vector<vector<bool>>(9, vector<bool>(9));
		
		for (size_t f = 0; f < DIM_SUDOKU; ++f)
		{
			for (size_t c = 0; c < DIM_SUDOKU; ++c)
			{
				char ch;
				ist >> ch;

				sudoku[f][c] = ch != '-';
			}
		}
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	bool es_buen_sudoku;

	void imprimir(ostream& ost = cout) const
	{
		if (es_buen_sudoku)
		{
			ost << "SI";
		}
		else
		{
			ost << "NO";
		}
	}
};

bool celdaRellena(const int celda)
{
	return celda != 0;
}

// Resolución del problema
Solucion resolver(const Entrada& entrada)
{
	size_t rellenas = 0;
	Solucion solucion;
	solucion.es_buen_sudoku = true;

	for (size_t f = 0; f < DIM_SUDOKU; ++f)
	{
		for(size_t c = 0; c < DIM_SUDOKU; ++c)
		{
			if (entrada.sudoku[f][c])
			{
				++rellenas;
			}
		}
	}

	solucion.es_buen_sudoku = rellenas <= NUM_BUENOS_DIGITOS;

	if (!solucion.es_buen_sudoku)
	{
		return solucion;
	}
	
	for (size_t f = 0; f <= DIM_SUDOKU / 2; ++f)
	{
		for (size_t c = 0; c < DIM_SUDOKU; ++c)
		{
			solucion.es_buen_sudoku = entrada.sudoku[f][c] == entrada.sudoku[DIM_SUDOKU - 1 - f][DIM_SUDOKU - 1 - c];

			if (!solucion.es_buen_sudoku)
			{
				return solucion;
			}
		}
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