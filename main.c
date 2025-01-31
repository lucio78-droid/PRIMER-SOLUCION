#include <stdio.h>
#include "funciones.h"

#define MAX_ZONAS 10

int main() {
    Zona zonas[MAX_ZONAS];
    int numZonas = 0;
    int opcion;

do {
    printf("\n--- Sistema de Gestión y Predicción de Contaminación ---\n");
    printf("1. Cargar datos\n");
    printf("2. Mostrar datos actuales\n");
    printf("3. Calcular promedios históricos\n");
    printf("4. Predecir niveles de contaminación\n");
    printf("5. Generar alertas\n");
    printf("6. Generar recomendaciones\n");
    printf("7. Exportar reporte\n");
    printf("8. Leer datos desde archivo\n"); // Nueva opción
    printf("9. Salir\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            cargarDatos(zonas, &numZonas);
            break;
        case 2:
            mostrarDatosActuales(zonas, numZonas);
            break;
        case 3:
            calcularPromedios(zonas, numZonas);
            break;
        case 4:
            predecirContaminacion(zonas, numZonas);
            break;
        case 5:
            generarAlertas(zonas, numZonas);
            break;
        case 6:
            generarRecomendaciones(zonas, numZonas);
            break;
        case 7:
            exportarReporte(zonas, numZonas, "reporte.txt");
            break;
        case 8: // Nueva opción para leer datos desde el archivo
            leerReporte(zonas, &numZonas, "reporte.txt");
            break;
        case 9:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción inválida. Intente nuevamente.\n");
    }
} while (opcion != 9);

}
