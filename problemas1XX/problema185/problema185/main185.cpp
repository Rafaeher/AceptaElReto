// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 185 de Acepta el Reto:
// Potitos
//
// Coste en tiempo: O(i), con i = número de ingredientes entre todos los potitos
//
// Coste en espacio adicional: O(k), con k constante
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada185.txt"; // El nombre del fichero de entrada

class Entrada // Tipo de la entrada a leer
{
public: // Los atributos y operaciones son todos públicos por comodidad

	bool es_caso; // Solo se utiliza si la entrada no es por número de casos, para indicar si hay que tratar el caso o no
	size_t numPotitos;
	vector<pair<vector<string>, bool>> potitos;

	void escanear(istream& ist = cin)
	{
		ist >> numPotitos;
		es_caso = numPotitos != 0;
		potitos = vector<pair<vector<string>, bool>>(numPotitos);

		if (es_caso)
		{
			for (size_t i = 0; i < numPotitos; i++)
			{
				string gusta, ingrediente;
				ist >> gusta;
				potitos[i].second = gusta == "SI:";

				ist >> ingrediente;
				while (ingrediente != "FIN")
				{
					potitos[i].first.push_back(ingrediente);
					ist >> ingrediente;
				}
			}
		}
	}
};

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	vector<string> ingredientes;

	void imprimir(ostream& ost = cout) const
	{
		if (ingredientes.size() > 0)
		{
			for (size_t i = 0; i < ingredientes.size() - 1; i++)
				ost << ingredientes[i] << ' ';
			ost << ingredientes[ingredientes.size() - 1];
		}
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
	unordered_map<string, bool> gusta; // <nombre del ingrediente, el ingrediente gusta>
	unordered_map<string, bool> no_gusta; // <nombre del ingrediente, el ingrediente no gusta>
	Solucion solucion;

	for (auto potito : entrada.potitos)
	{
		for (auto ingrediente : potito.first)
		{
			if (potito.second) // Si el potito gusta
			{
				gusta[ingrediente] = true;
				no_gusta[ingrediente] = false;
			}
			else // Si el potito no gusta
			{
				try
				{
					gusta.at(ingrediente); // Si el ingrediente está en un potito que gusta
				}
				catch (exception e) // Si el ingrediente no está en un potito que gusta
				{
					no_gusta[ingrediente] = true;
				}

			}

		}
	}

	for (auto ingrediente : no_gusta)
		if (ingrediente.second) // Si el ingrediente no gusta
			solucion.ingredientes.push_back(ingrediente.first);

	sort(solucion.ingredientes.begin(), solucion.ingredientes.end());

	return solucion;
}

// Resolución de un caso con entrada sin número de casos
bool resuelveCasoSinNumCasos()
{
	// ENTRADA
	Entrada entrada;
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