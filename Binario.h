#pragma once
using namespace std;

// Struct para sinonimos y antonimos
struct struct_secundario
{
    char palabra[20];
    int frecuencia_conocimiento;
};

// Struct principal para palabras
struct struct_principal
{
    char palabra[20];
    char tipo[10];
    char descripcion[200];
    int frecuencia_conocimiento;
    char ejemplo[50];
    struct_secundario sinonimos[20];
    struct_secundario antonimos[20];
    int cant_sinonimos;
    int cant_antonimos;
};

// Almacén de datos para ingreso y lectura a un archivo binario
struct info_binario
{
    struct_principal datos[20];
    int cant_datos;
};

class Binario
{
public:
    // Función que construye un archivo binario a partir de un CSV
    void construir();
    // Función que extrae datos a partir de un archivo binario
    info_binario extraerDatos();
};