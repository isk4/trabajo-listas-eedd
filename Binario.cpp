#include "Binario.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

// Definición de nombres de archivos que utilzia el programa
const char NOMBRE_CSV[] = "palabras.csv";
const char NOMBRE_BIN[] = "palabras.dat";

// Función auxiliar para mostrar info de un elemento del binario
void mostrar_info_principal(struct_principal info)
{
    cout << info.palabra << endl;
    cout << info.tipo << endl;
    cout << info.descripcion << endl;
    cout << info.frecuencia_conocimiento << endl;
    cout << info.ejemplo << endl;
}

void Binario::construir()
{   
    // Se incializan en cero las cantidades de elementos
    info_binario struct_binario = {};
    // Nodo para trabajar con las palabras principales
    struct_principal info_principal;
    // Nodo para trabajar con las palabras secundarias
    struct_secundario info_secundaria;
    // Archivo binario donde se escribiran los archivos
    FILE* binario = fopen(NOMBRE_BIN, "wb");
    // Linea a leer del archivo
    string linea;
    // Numero de columna a leer, id de palabra principal
    int columna, aux_datos;
    // Archivo csv de donde se extraen los datos para generar el binario
    ifstream archivo_entrada(NOMBRE_CSV);
    // Contenido del archivo CSV correspondiente columnas y sus datos
    istringstream columnas_archivo, datos_col, sub_datos_col;

    // Si los archivos son válidos
    if (archivo_entrada.is_open() && binario)
    {
        // Sacando el encabezado del archivo
        getline(archivo_entrada, linea);
        // Leyendo contenido
        while(getline(archivo_entrada, linea))
        {   
            // Se limpia el struct de info de palabra
            info_principal = {};
            // Inicialización de columna en 1
            columna = 1;
            // Se saca un stream de la string "linea"
            columnas_archivo.str(linea);
            // Leemos el stream generado separado por ';'
            while (getline(columnas_archivo, linea, ';'))
            {
                // Si la columna tiene contenido
                if (linea.length() != 0 && linea[0] != '\n' && linea[0] != '\r')
                {
                    // Un caso para cada columna
                    switch (columna)
                    {
                        // Se asignan los datos donde corresponden
                        case 1:
                            strcpy(info_principal.palabra, linea.c_str());
                            break;
                        case 2:
                            strcpy(info_principal.tipo, linea.c_str());
                            break;
                        case 3:
                            strcpy(info_principal.descripcion, linea.c_str());
                            break;
                        case 4:
                            info_principal.frecuencia_conocimiento = stoi(linea);
                            break;
                        case 5:
                            strcpy(info_principal.ejemplo, linea.c_str());
                            break;
                        case 6:
                            // Se separa el string por '-'
                            datos_col.str(linea);
                            while (getline(datos_col, linea, '-'))
                            {
                                sub_datos_col.str(linea);
                                // Obteniendo palabra
                                getline(sub_datos_col, linea, ':');
                                // Asignando palabra a nuevo dato
                                strcpy(info_secundaria.palabra, linea.c_str());
                                // Obteniendo frecuencia
                                getline(sub_datos_col, linea);
                                info_secundaria.frecuencia_conocimiento = stoi(linea);
                                // Añadiendo a sinonimos
                                info_principal.sinonimos[info_principal.cant_sinonimos] = info_secundaria;
                                info_principal.cant_sinonimos++;
                                // Limpiando variables
                                info_secundaria = {};
                                sub_datos_col.clear();
                            }
                            break;
                        case 7:
                            // Se separa el string por '-'
                            datos_col.str(linea);
                            while (getline(datos_col, linea, '-'))
                            {
                                sub_datos_col.str(linea);
                                // Obteniendo palabra
                                getline(sub_datos_col, linea, ':');
                                // Asignando palabra a nuevo dato
                                strcpy(info_secundaria.palabra, linea.c_str());
                                // Obteniendo frecuencia
                                getline(sub_datos_col, linea);
                                info_secundaria.frecuencia_conocimiento = stoi(linea);
                                // Añadiendo a antonimos
                                info_principal.antonimos[info_principal.cant_antonimos] = info_secundaria;
                                info_principal.cant_antonimos++;
                                // Limpiando variables
                                info_secundaria = {};
                                sub_datos_col.clear();
                            }
                            break;
                    }
                }
                // Avanzando de columa
                datos_col.clear();
                columna == 7 ? columna = 1 : columna++;
            }
            // Se limpia el stream de los datos de la columna
            columnas_archivo.clear();
            // Se ingresan los datos al struct principal y se actualiza la cantidad de datoss
            struct_binario.datos[struct_binario.cant_datos] = info_principal;
            struct_binario.cant_datos++;
        }
    }
    // Se escribe la información al archivo binario y se cierra
    fwrite(&struct_binario, sizeof(info_binario), 1, binario);
    fclose(binario);
}

// Lectura de binario
info_binario Binario::extraerDatos()
{
    FILE* binario = fopen("palabras.dat", "rb");
    info_binario info = {};
    // Se extraen los datos del archivo y se retornan
    if (binario) fread(&info, sizeof(info_binario), 1, binario);
    fclose(binario);
    return info;
}