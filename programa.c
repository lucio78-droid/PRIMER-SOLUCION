#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

// Constantes de límites aceptables (según la OMS, pueden ajustarse según necesidades)
#define LIMITE_CO2 10.0     // ppm
#define LIMITE_SO2 0.02     // ppm
#define LIMITE_NO2 0.03     // ppm
#define LIMITE_PM2_5 25.0   // µg/m3

int esNombreValido(const char *nombre) {
    for (int i = 0; nombre[i] != '\0'; i++) {
        if (!isalpha(nombre[i])) {
            return 0; // Retorna 0 si el nombre contiene caracteres no alfabéticos
        }
    }
    return 1; // Retorna 1 si el nombre es válido
}

void cargarDatos(Zona zonas[], int *numZonas) {
    printf("\nIngrese el número de zonas (máximo %d): ", MAX_ZONAS);
    scanf("%d", numZonas);

    while (*numZonas <= 0 || *numZonas > MAX_ZONAS) {
        printf("Número inválido. Debe estar entre 1 y %d. Intente nuevamente: ", MAX_ZONAS);
        scanf("%d", numZonas);
    }

    for (int i = 0; i < *numZonas; i++) {
        printf("\nZona %d:\n", i + 1);

        // Validación del nombre de la zona
        do {
            printf("Nombre de la zona: ");
            scanf("%s", zonas[i].nombreZona);

            if (!esNombreValido(zonas[i].nombreZona)) {
                printf("Error: el nombre de la zona debe contener solo letras.\n");
            }
        } while (!esNombreValido(zonas[i].nombreZona));

        do {
            printf("Nivel de CO2 (ppm): ");
            scanf("%f", &zonas[i].CO2);
            if (zonas[i].CO2 < 0) {
                printf("Error: el nivel de CO2 no puede ser negativo.\n");
            }
        } while (zonas[i].CO2 < 0);

        do {
            printf("Nivel de SO2 (ppm): ");
            scanf("%f", &zonas[i].SO2);
            if (zonas[i].SO2 < 0) {
                printf("Error: el nivel de SO2 no puede ser negativo.\n");
            }
        } while (zonas[i].SO2 < 0);

        do {
            printf("Nivel de NO2 (ppm): ");
            scanf("%f", &zonas[i].NO2);
            if (zonas[i].NO2 < 0) {
                printf("Error: el nivel de NO2 no puede ser negativo.\n");
            }
        } while (zonas[i].NO2 < 0);

        do {
            printf("Nivel de PM2.5 (µg/m3): ");
            scanf("%f", &zonas[i].PM2_5);
            if (zonas[i].PM2_5 < 0) {
                printf("Error: el nivel de PM2.5 no puede ser negativo.\n");
            }
        } while (zonas[i].PM2_5 < 0);

        do {
            printf("Temperatura (°C): ");
            scanf("%f", &zonas[i].temperatura);
            if (zonas[i].temperatura < -50 || zonas[i].temperatura > 60) {
                printf("Error: la temperatura debe estar entre -50 y 60 °C.\n");
            }
        } while (zonas[i].temperatura < -50 || zonas[i].temperatura > 60);

        do {
            printf("Velocidad del viento (km/h): ");
            scanf("%f", &zonas[i].velocidadViento);
            if (zonas[i].velocidadViento < 0) {
                printf("Error: la velocidad del viento no puede ser negativa.\n");
            }
        } while (zonas[i].velocidadViento < 0);

        do {
            printf("Humedad relativa (%%): ");
            scanf("%f", &zonas[i].humedad);
            if (zonas[i].humedad < 0 || zonas[i].humedad > 100) {
                printf("Error: la humedad debe estar entre 0 y 100%%.\n");
            }
        } while (zonas[i].humedad < 0 || zonas[i].humedad > 100);

        zonas[i].promedio30Dias = 0; // Inicializa el promedio
    }
}

void mostrarDatosActuales(Zona zonas[], int numZonas) {
    if (numZonas == 0) {
        printf("\nNo hay datos cargados.\n");
        return;
    }

    printf("\nDatos actuales de las zonas:\n");
    for (int i = 0; i < numZonas; i++) {
        printf("\nZona %d: %s\n", i + 1, zonas[i].nombreZona);
        printf("CO2: %.2f ppm, SO2: %.2f ppm, NO2: %.2f ppm, PM2.5: %.2f µg/m3\n",
               zonas[i].CO2, zonas[i].SO2, zonas[i].NO2, zonas[i].PM2_5);
        printf("Temperatura: %.2f °C, Viento: %.2f km/h, Humedad: %.2f%%\n",
               zonas[i].temperatura, zonas[i].velocidadViento, zonas[i].humedad);
    }
}
// Función para calcular promedios históricos
void calcularPromedios(Zona zonas[], int numZonas) {
    for (int i = 0; i < numZonas; i++) {
        printf("Calculando promedio histórico para la zona: %s\n", zonas[i].nombreZona);
        
        float suma = 0;
        for (int j = 0; j < MAX_DIAS; j++) {
            suma += zonas[i].nivelesContaminacion[j];
        }
        zonas[i].promedio30Dias = suma / MAX_DIAS;  
        
        printf("Promedio histórico de los últimos 30 días para la zona %s: %.2f µg/m3\n", zonas[i].nombreZona, zonas[i].promedio30Dias);
    }
}
void predecirContaminacion(Zona zonas[], int numZonas) {
    for (int i = 0; i < numZonas; i++) {
        zonas[i].CO2 = (zonas[i].CO2 * 0.7) + (zonas[i].promedio30Dias * 0.3);
        zonas[i].SO2 = (zonas[i].SO2 * 0.7) + (zonas[i].promedio30Dias * 0.3);
        zonas[i].NO2 = (zonas[i].NO2 * 0.7) + (zonas[i].promedio30Dias * 0.3);
        zonas[i].PM2_5 = (zonas[i].PM2_5 * 0.7) + (zonas[i].promedio30Dias * 0.3);

        printf("\nPredicción de contaminación para la zona: %s\n", zonas[i].nombreZona);
        printf("CO2: %.2f ppm, SO2: %.2f ppm, NO2: %.2f ppm, PM2.5: %.2f µg/m3\n",
               zonas[i].CO2, zonas[i].SO2, zonas[i].NO2, zonas[i].PM2_5);
    }
}
void generarAlertas(Zona zonas[], int numZonas) {
    for (int i = 0; i < numZonas; i++) {
        printf("\nAlertas para la zona: %s\n", zonas[i].nombreZona);

        if (zonas[i].CO2 > LIMITE_CO2) {
            printf("ALERTA: CO2 (%.2f ppm) excede el límite de %.2f ppm.\n", zonas[i].CO2, LIMITE_CO2);
        }
        if (zonas[i].SO2 > LIMITE_SO2) {
            printf("ALERTA: SO2 (%.2f ppm) excede el límite de %.2f ppm.\n", zonas[i].SO2, LIMITE_SO2);
        }
        if (zonas[i].NO2 > LIMITE_NO2) {
            printf("ALERTA: NO2 (%.2f ppm) excede el límite de %.2f ppm.\n", zonas[i].NO2, LIMITE_NO2);
        }
        if (zonas[i].PM2_5 > LIMITE_PM2_5) {
            printf("ALERTA: PM2.5 (%.2f µg/m3) excede el límite de %.2f µg/m3.\n", zonas[i].PM2_5, LIMITE_PM2_5);
        }
    }
}

// Función para generar medidas de mitigación
void generarRecomendaciones(Zona zonas[], int numZonas) {
    for (int i = 0; i < numZonas; i++) {
        printf("\nRecomendaciones para la zona: %s\n", zonas[i].nombreZona);

        if (zonas[i].CO2 > LIMITE_CO2 || zonas[i].SO2 > LIMITE_SO2 ||
            zonas[i].NO2 > LIMITE_NO2 || zonas[i].PM2_5 > LIMITE_PM2_5) {
            printf("- Reducir el tráfico vehicular.\n");
            printf("- Cierre temporal de industrias.\n");
            printf("- Suspender actividades al aire libre.\n");
        } else {
            printf("Niveles dentro de los límites aceptables. No se requieren medidas especiales.\n");
        }
    }
}

// Función para guardar los datos en un archivo de texto
#include <stdio.h>
#include "funciones.h"

void exportarReporte(Zona zonas[], int numZonas, const char *archivo) {
    // Abrir el archivo en modo "a" (append) para agregar los datos al final sin sobrescribir
    FILE *file = fopen(archivo, "a");
    if (file == NULL) {
        printf("Error al abrir el archivo para guardar el reporte.\n");
        return;
    }

    // Escribir los datos de las zonas en el archivo
    for (int i = 0; i < numZonas; i++) {
        fprintf(file, "Zona: %s\n", zonas[i].nombreZona);
        fprintf(file, "CO2: %.2f ppm\n", zonas[i].CO2);
        fprintf(file, "SO2: %.2f ppm\n", zonas[i].SO2);
        fprintf(file, "NO2: %.2f ppm\n", zonas[i].NO2);
        fprintf(file, "PM2.5: %.2f µg/m³\n", zonas[i].PM2_5);
        fprintf(file, "Promedio de los últimos 30 días: %.2f µg/m³\n", zonas[i].promedio30Dias);
        fprintf(file, "Temperatura: %.2f °C\n", zonas[i].temperatura);
        fprintf(file, "Velocidad del viento: %.2f km/h\n", zonas[i].velocidadViento);
        fprintf(file, "Humedad: %.2f%%\n\n", zonas[i].humedad);
    }

    fclose(file);
    printf("Reporte exportado a: %s\n", archivo);
}
