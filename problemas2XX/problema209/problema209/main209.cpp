// GNU GPLv3
// Rafael Andrés Hernández Roldán
//
// Nick en Acepta el Reto: Rafael
// Correo: rafaeher@ucm.es
//         rafael.ahr96@gmail.com
//
// Problema 209 de Acepta el Reto:
// Pánico en el túnel
//
// Coste en tiempo: O(s), con s = número de secciones
//
// Coste en espacio adicional: O(k), con k constante
//

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

const bool QUIERO_TESTEAR = false; // Poner a false para enviar a Acepta el Reto
const bool ENTRADA_CON_NUMERO_DE_CASOS = false; // true para entrada con número de casos, false para entrada ilimitada o con centinela
const string FICHERO_ENTRADA = "entrada209.txt"; // El nombre del fichero de entrada
const char TELEFONO = 'T';
const char SIN_TELEFONO = '.';

using uint = unsigned int;

typedef enum{PENINSULA, ISLAS, AQUI}Direccion;

class DatosPrevios // Información previa a la entrada del problema
{
public: // Los atributos y operaciones son todos públicos por comodidad

	bool es_caso;

	void escanear(istream& ist = cin)
	{

	}
};

class Entrada // Tipo de la entrada a leer
{
public: // Los atributos y operaciones son todos públicos por comodidad

	bool es_caso; // Solo se utiliza si la entrada no es por número de casos, para indicar si hay que tratar el caso o no
	string secciones;
	queue<uint> consultas;

	Entrada(DatosPrevios& datos)
	{

	}

	void escanear(istream& ist = cin)
	{
		getline(ist, secciones);
		es_caso = secciones != "";

		if (es_caso)
		{
			size_t numConsultas;
			ist >> numConsultas;
			ist.ignore();

			for (size_t i = 0; i < numConsultas; ++i)
			{
				size_t consulta;
				ist >> consulta;
				ist.ignore();
				consultas.push(consulta - 1);
			}
		}
	}
};

string direccionToString(const Direccion& direccion)
{
	switch (direccion)
	{
	case PENINSULA: return "PENINSULA";
	case ISLAS: return "ISLAS";
	case AQUI: return "AQUI";
	}
}

class Solucion // Tipo de la solución a mostrar
{
public: // Los atributos y operaciones son todos públicos por comodidad

	vector<Direccion> direcciones;

	void imprimir(ostream& ost = cout) const
	{
		for (size_t i = 0; i < direcciones.size() - 1; ++i)
		{
			ost << direccionToString(direcciones[i]) << '\n';
		}

		ost << direccionToString(direcciones[direcciones.size() - 1]);
	}
};

void calcularDistanciasDesdePeninsula(vector<int>& distancias, const string secciones)
{
	int ultimoTelefono = -1;
	for (size_t i = 0; i < secciones.size(); ++i)
	{
		if (secciones[i] == TELEFONO)
		{
			ultimoTelefono = 0;
		}

		distancias.push_back(ultimoTelefono);
		--ultimoTelefono;
	}
}

void calcularDistanciasDesdeIslas(vector<int>& distancias)
{
	int ultimoTelefono = 1;
	for (int i = distancias.size() - 1; i >= 0; --i)
	{
		if (distancias[i] == 0)
		{
			ultimoTelefono = 1;
		}
		else
		{
			if (ultimoTelefono < -distancias[i]) // Si el teléfono derecho está más cerca que el izquierdo
			{
				distancias[i] = ultimoTelefono;
			}
			else if (ultimoTelefono == -distancias[i]) // Si ambos teléfonos están a la misma distancia
			{
				int distanciaPeninsula = 1 + i + distancias[i];
					// La distancia del teléfono izquierdo a la península
				int distanciaIslas = distancias.size() - (i + ultimoTelefono);
					// La distancia del teléfono derecho a las islas

				if (distanciaIslas < distanciaPeninsula)
					// Si la salida del teléfono derecho está más cerca que la salida del izquierdo
				{
					distancias[i] = ultimoTelefono;
				}
			}
			
			++ultimoTelefono;
		}
	}
}

Direccion ejecutarConsulta(const vector<int>& distancias, const int& index)
{
	if (distancias[index] == 0)
	{
		return AQUI;
	}
	else if (distancias[index] < 0)
	{
		return PENINSULA;
	}
	else
	{
		return ISLAS;
	}
}

// Resolución del problema
Solucion resolver(Entrada& entrada)
{
	Solucion solucion;
	vector<int> distancias;
	
	calcularDistanciasDesdePeninsula(distancias, entrada.secciones);
	calcularDistanciasDesdeIslas(distancias);

	while (!entrada.consultas.empty())
	{
		solucion.direcciones.push_back(ejecutarConsulta(distancias, entrada.consultas.front()));
		entrada.consultas.pop();
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