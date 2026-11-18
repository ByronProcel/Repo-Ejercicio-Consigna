#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 5          /* cinco productos distintos */
#define LARGO 30       /* largo maximo del nombre */

/* ---------- Busqueda propia (sin funciones predefinidas) ---------- */

char aMinuscula(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

/* Compara dos textos ignorando mayusculas. Devuelve 1 si son iguales */
int sonIguales(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (aMinuscula(*a) != aMinuscula(*b)) return 0;
        a++;
        b++;
    }
    return (*a == '\0' && *b == '\0');
}

/* Busqueda lineal: devuelve la posicion o -1 si no existe */
int buscarProducto(char nombres[][LARGO], int n, const char *buscado) {
    int i;
    for (i = 0; i < n; i++) {
        if (sonIguales(nombres[i], buscado)) return i;
    }
    return -1;
}

/* ---------- Operaciones del menu ---------- */

void ingresarProducto(char nombres[][LARGO], int *demanda, float *tiempo,
                      float *recurso, int *n) {
    if (*n < MAX) {
        printf("Nombre del producto: ");
        scanf("%s", nombres[*n]);
        printf("Demanda (unidades): ");
        scanf("%d", &demanda[*n]);
        printf("Tiempo de fabricacion por unidad (horas): ");
        scanf("%f", &tiempo[*n]);
        printf("Recursos por unidad: ");
        scanf("%f", &recurso[*n]);
        (*n)++;
    }
}

void listarProductos(char nombres[][LARGO], int *demanda, float *tiempo,
                     float *recurso, int n) {
    int i;
    printf("%-3s %-30s %-10s %-12s %-10s", "#", "Producto", "Demanda",
           "Tiempo/u (h)", "Recurso/u");
    puts("");
    for (i = 0; i < n; i++) {
        printf("%-3d %-30s %-10d %-12.2f %-10.2f", i + 1, nombres[i],
               demanda[i], tiempo[i], recurso[i]);
        puts("");
    }
}

void editarProducto(char nombres[][LARGO], int *demanda, float *tiempo,
                    float *recurso, int n) {
    char buscado[LARGO];
    int pos, opcion;

    printf("Nombre del producto a editar: ");
    scanf("%s", buscado);
    pos = buscarProducto(nombres, n, buscado);

    if (pos != -1) {
        puts("1. Nombre");
        puts("2. Demanda");
        puts("3. Tiempo por unidad");
        puts("4. Recursos por unidad");
        printf("Que desea editar?: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            printf("Nuevo nombre: ");
            scanf("%s", nombres[pos]);
            break;
        case 2:
            printf("Nueva demanda: ");
            scanf("%d", &demanda[pos]);
            break;
        case 3:
            printf("Nuevo tiempo por unidad (horas): ");
            scanf("%f", &tiempo[pos]);
            break;
        case 4:
            printf("Nuevos recursos por unidad: ");
            scanf("%f", &recurso[pos]);
            break;
        }
    }
}

void eliminarProducto(char nombres[][LARGO], int *demanda, float *tiempo,
                      float *recurso, int *n) {
    char buscado[LARGO];
    int pos, i;

    printf("Nombre del producto a eliminar: ");
    scanf("%s", buscado);
    pos = buscarProducto(nombres, *n, buscado);

    if (pos != -1) {
        /* Se desplazan los elementos posteriores una posicion hacia atras */
        for (i = pos; i < *n - 1; i++) {
            strcpy(nombres[i], nombres[i + 1]);
            demanda[i] = demanda[i + 1];
            tiempo[i]  = tiempo[i + 1];
            recurso[i] = recurso[i + 1];
        }
        (*n)--;
    }
}

void analizarProduccion(int *demanda, float *tiempo, float *recurso, int n) {
    int i;
    float tiempoTotal = 0, recursoTotal = 0;
    float tiempoDisp, recursoDisp;

    for (i = 0; i < n; i++) {
        tiempoTotal  += demanda[i] * tiempo[i];
        recursoTotal += demanda[i] * recurso[i];
    }
    printf("Tiempo total de fabricacion requerido: %.2f horas", tiempoTotal);
    puts("");
    printf("Recursos totales necesarios: %.2f", recursoTotal);
    puts("");

    printf("Tiempo de produccion disponible (horas): ");
    scanf("%f", &tiempoDisp);
    printf("Recursos disponibles: ");
    scanf("%f", &recursoDisp);

    if (tiempoTotal <= tiempoDisp && recursoTotal <= recursoDisp) {
        puts("La fabrica SI puede cumplir con la demanda.");
    } else {
        puts("La fabrica NO puede cumplir con la demanda.");
        if (tiempoTotal > tiempoDisp) {
            printf("- Faltan %.2f horas de produccion.", tiempoTotal - tiempoDisp);
            puts("");
        }
        if (recursoTotal > recursoDisp) {
            printf("- Faltan %.2f unidades de recurso.", recursoTotal - recursoDisp);
            puts("");
        }
    }
}

/* ---------- Programa principal ---------- */

int main(void) {
    char nombres[MAX][LARGO];
    int   demanda[MAX];
    float tiempo[MAX];
    float recurso[MAX];
    int n = 0;
    int opcion;

    do {
        puts("===== PRODUCCION DE COMPONENTES ELECTRONICOS =====");
        puts("1. Ingresar producto");
        puts("2. Listar productos");
        puts("3. Editar producto");
        puts("4. Eliminar producto");
        puts("5. Calcular y verificar produccion");
        puts("6. Salir");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1: ingresarProducto(nombres, demanda, tiempo, recurso, &n); break;
        case 2: listarProductos(nombres, demanda, tiempo, recurso, n);   break;
        case 3: editarProducto(nombres, demanda, tiempo, recurso, n);    break;
        case 4: eliminarProducto(nombres, demanda, tiempo, recurso, &n); break;
        case 5: analizarProduccion(demanda, tiempo, recurso, n);         break;
        }
    } while (opcion != 6);

    return 0;
}
