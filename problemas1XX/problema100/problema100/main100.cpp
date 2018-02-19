// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema XXX de Acepta el Reto:
// Nombre del Problema
//
// Coste en tiempo: O(k) con k constante
//
// Coste en espacio adicional: O(t) con t constante
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = true; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada100.txt"; // El nombre del fichero de entrada

size_t pot(const size_t& base, const size_t& exp)
{
	if (exp == 0)
		return 1;

	size_t result = pot(base, exp / 2);
	result = result * result;
	if (exp % 2 == 1)
		result = result * base;
	
	return result;
}

size_t obtenerInt(const vector<size_t>& v)
{
	size_t result = 0;
	for (size_t i = 0; i < v.size(); i++)
		result += v[i] * pot(10, v.size() - i - 1);
	
	return result;
}



class Entrada // Tipo de la entrada a leer
{
public: // Los atributos y operaciones son todos públicos por comodidad

	vector<size_t> num;

	void escanear(istream & ist = cin)
	{
		size_t n;
		ist >> n;
		num = obtenerVector(n);
	}

	vector<size_t> obtenerVector(const size_t& n) const
	{
		vector<size_t> result;

		// Escribir el número cifra a cifra en el vector
		for (size_t i = 0; i < 4; i++)
			result.push_back((n % (pot(10, 4 - i))) / pot(10, 3 - i));

		return result;
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	size_t numVueltas;

	Solucion(size_t numV)
	{
		numVueltas = numV;
	}

	void imprimir(ostream& ost = cout) const
	{
		ost << numVueltas;
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
	vector<size_t> vectorMayor = entrada.num;
	vector<size_t> vectorMenor = entrada.num;
	size_t vueltas = 0;
	size_t numeroMayor;
	size_t numeroMenor;
	size_t resta;
	
	resta = obtenerInt(entrada.num);


	
	// Restamos hasta llegar al 6174
	while (resta != 6174 && resta != 0)
	{
		vueltas++;

		vectorMayor = entrada.obtenerVector(resta);
		vectorMenor = entrada.obtenerVector(resta);
		
		sort(vectorMayor.begin(), vectorMayor.end());
		sort(vectorMenor.begin(), vectorMenor.end(), greater<size_t>());

		numeroMayor = obtenerInt(vectorMayor);
		numeroMenor = obtenerInt(vectorMenor);

		if (numeroMayor < numeroMenor)
		{
			swap(vectorMayor, vectorMenor);
			swap(numeroMayor, numeroMenor);
		}

		resta = numeroMayor - numeroMenor;
	}

	if (resta == 0)
		vueltas = 8;

	return Solucion(vueltas);
}

// Resolución de un caso con entrada sin número de casos
bool resuelveCasoSinNumCasos()
{
	// ENTRADA
	Entrada entrada;
	cin >> entrada;
	if (!cin)
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