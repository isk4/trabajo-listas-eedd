#pragma once
using namespace std;

#define MAX_PALABRA 20
#define MAX_TIPO 20
#define MAX_DESCRIPCION 200
#define MAX_EJEMPLO 100
#define MAX_SINONIMOS 20
#define MAX_ANTONIMOS 20

// Struct para sinonimos y antonimos
struct struct_secundario
{
    char palabra[20];
    int frecuencia_conocimiento;
};

// Struct principal para palabras
struct struct_principal
{
    char palabra[MAX_PALABRA];
    char tipo[MAX_TIPO];
    char descripcion[MAX_DESCRIPCION];
    int frecuencia_conocimiento;
    char ejemplo[MAX_EJEMPLO];
    struct_secundario sinonimos[MAX_SINONIMOS];
    struct_secundario antonimos[MAX_ANTONIMOS];
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
private:
    info_binario info;
public:
    // Función que construye un archivo binario a partir de un CSV
    void construir();
    // Función que extrae datos a partir de un archivo binario
    info_binario extraerDatos();
};