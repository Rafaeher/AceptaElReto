// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 101 de Acepta el Reto:
// Cuadrados diabólicos y esotéricos
//
// Coste en tiempo: O(n * n), con n = dimensión de la matriz cuadrada
//
// Coste en espacio adicional: O(2 * n * n), con n = dimensión de la matriz cuadrada
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada101.txt"; // El nombre del fichero de entrada

typedef enum{NINGUNO, DIABOLICO, ESOTERICO}TipoCuadrado;

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
	vector<vector<size_t>> matriz;

	Entrada(DatosPrevios& datos)
	{

	}

	void escanear(istream& ist = cin)
	{
		int n;
		ist >> n;

		es_caso = n != 0;

		if (es_caso)
		{
			matriz = vector<vector<size_t>>(n, vector<size_t>(n));

			for (int f = 0; f < n; ++f)
			{
				for (int c = 0; c < n; c++)
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

	TipoCuadrado tipo;

	void imprimir(ostream& ost = cout) const
	{
		switch (tipo)
		{
		case NINGUNO: ost << "NO"; break;
		case DIABOLICO: ost << "DIABOLICO"; break;
		case ESOTERICO: ost << "ESOTERICO"; break;
		}
	}
};

size_t calcularCM(const vector<vector<size_t>>& matriz)
{
	size_t CM = 0;

	for (size_t c = 0; c < matriz.size(); ++c)
	{
		CM += matriz[0][c];
	}

	return CM;
}

bool comprobarFilas(const vector<vector<size_t>>& matriz, const size_t CM)
{
	size_t suma = CM;
	
	for (size_t f = 1; f < matriz.size() && suma == CM; ++f)
	{
		suma = 0;
		for (size_t c = 0; c < matriz.size(); ++c)
		{
			suma += matriz[f][c];
		}
	}

	return suma == CM;
}

bool comprobarColumnas(const vector<vector<size_t>>& matriz, const size_t CM)
{
	size_t suma = CM;

	for (size_t c = 0; c < matriz.size() && suma == CM; ++c)
	{
		suma = 0;
		for (size_t f = 0; f < matriz.size(); ++f)
		{
			suma += matriz[f][c];
		}
	}

	return suma == CM;
}

bool comprobarDiagonales(const vector<vector<size_t>>& matriz, const size_t CM)
{
	size_t suma1 = 0;
	size_t suma2 = 0;

	for (size_t i = 0; i < matriz.size(); ++i)
	{
		suma1 += matriz[i][i];
	}

	if (suma1 == CM)
	{
		for (size_t i = 0; i < matriz.size(); ++i)
		{
			suma2 += matriz[i][matriz.size() - 1 - i];
		}
	}

	return suma1 == CM && suma2 == CM;
}

bool comprobarCifras(const vector<vector<size_t>>& matriz)
{
	vector<vector<bool>> cifraEncontrada(matriz.size(), vector<bool>(matriz.size(), false));

	// Anotar todas las cifras encontradas
	for (size_t f = 0; f < matriz.size(); ++f)
	{
		for (size_t c = 0; c < matriz.size(); ++c)
		{
			if (matriz[f][c] > matriz.size() * matriz.size() || matriz[f][c] == 0)
			{
				return false;
			}

			size_t cifra = matriz[f][c] - 1;
			size_t fila = cifra / matriz.size();
			size_t columna = cifra % matriz.size();

			cifraEncontrada[fila][columna] = true;
		}
	}

	// Comprobar que todas las cifras han sido encontradas
	for (size_t f = 0; f < matriz.size(); ++f)
	{
		for (size_t c = 0; c < matriz.size(); ++c)
		{
			if (!cifraEncontrada[f][c])
			{
				return false;
			}
		}
	}

	return true;
}

bool comprobarEsquinas(const vector<vector<size_t>>& matriz, const size_t CM2)
{
	size_t esq1 = matriz[0][0],
		esq2 = matriz[0][matriz.size() - 1],
		esq3 = matriz[matriz.size() - 1][0],
		esq4 = matriz[matriz.size() - 1][matriz.size() - 1];

	return  CM2 == esq1 + esq2 + esq3 + esq4;
}

bool comprobarLaterales(const vector<vector<size_t>>& matriz, const size_t CM2)
{
	const size_t n = matriz.size();

	if (n % 2 != 0) // n es impar
	{
		size_t l1 = matriz[0][(n - 1) / 2],
			l2 = matriz[(n - 1) / 2][0],
			l3 = matriz[(n - 1) / 2][n - 1],
			l4 = matriz[n - 1][(n - 1) / 2];

		return CM2 == l1 + l2 + l3 + l4;
	}
	else // n es par
	{
		size_t l1 = matriz[0][(n / 2) - 1],
			l2 = matriz[0][n / 2],
			l3 = matriz[(n / 2) - 1][0],
			l4 = matriz[n / 2][0],
			l5 = matriz[(n / 2) - 1][n - 1],
			l6 = matriz[n / 2][n - 1],
			l7 = matriz[n - 1][(n / 2) - 1],
			l8 = matriz[n - 1][n / 2];

		return 2 * CM2 == l1 + l2 + l3 + l4 + l5 + l6 + l7 + l8;
	}
}

bool comprobarCentros(const vector<vector<size_t>>& matriz, const size_t CM2)
{
	const size_t n = matriz.size();

	if (n % 2 != 0) // n es impar
	{
		return CM2 == 4 * matriz[(n - 1) / 2][(n - 1) / 2];
	}
	else // n es par
	{
		size_t c1 = matriz[(n / 2) - 1][(n / 2) - 1],
			c2 = matriz[(n / 2) - 1][n / 2],
			c3 = matriz[n / 2][(n / 2) - 1],
			c4 = matriz[n / 2][n / 2];

		return CM2 == c1 + c2 + c3 + c4;
	}
}

// Resolución del problema
Solucion resolver(const Entrada& entrada)
{
	TipoCuadrado tipo = NINGUNO;

	const size_t CM = calcularCM(entrada.matriz);

	if (comprobarFilas(entrada.matriz, CM) && comprobarColumnas(entrada.matriz, CM) &&
		comprobarDiagonales(entrada.matriz, CM))
	{
		tipo = DIABOLICO;
	}

	const size_t CM2 = 4 * CM / entrada.matriz.size();

	if (tipo == DIABOLICO && comprobarCifras(entrada.matriz) && comprobarEsquinas(entrada.matriz, CM2)
		&& comprobarLaterales(entrada.matriz, CM2) && comprobarCentros(entrada.matriz, CM2))
	{
		tipo = ESOTERICO;
	}

	Solucion solucion;
	solucion.tipo = tipo;

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