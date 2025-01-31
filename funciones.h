#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_NOMBRE 50
#define MAX_ZONAS 10
#define MAX_DIAS 30 

// Estructura para representar los datos de una zona
typedef struct {
    char nombreZona[MAX_NOMBRE];  // Nombre de la zona
    float nivelesContaminacion[MAX_DIAS];  // Niveles de contaminación (en las últimas 30 días)
    float CO2;  // Nivel de CO2
    float SO2;  // Nivel de SO2
    float NO2;  // Nivel de NO2
    float PM2_5;  // Nivel de PM2.5
    float promedio30Dias;  // Promedio de los últimos 30 días de contaminación
    float temperatura;  // Temperatura en la zona
    float velocidadViento;  // Velocidad del viento en la zona
    float humedad;  // Humedad en la zona
} Zona;

// Declaraciones de las funciones
void cargarDatos(Zona zonas[], int *numZonas);
void mostrarDatosActuales(Zona zonas[], int numZonas);
void calcularPromedios(Zona zonas[], int numZonas);
void predecirContaminacion(Zona zonas[], int numZonas);
void generarAlertas(Zona zonas[], int numZonas);
void generarRecomendaciones(Zona zonas[], int numZonas);
void exportarReporte(Zona zonas[], int numZonas, const char *archivo);
int esNombreValido(const char *nombre);

#endif

