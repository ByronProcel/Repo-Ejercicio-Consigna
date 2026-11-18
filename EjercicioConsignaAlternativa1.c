#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTOS 5

char productos[MAX_PRODUCTOS][30];
float tiempo[MAX_PRODUCTOS];
float recursos[MAX_PRODUCTOS];
int cantidadDemandada[MAX_PRODUCTOS];
int horasDisFabrica = 0;
float recursosDisponibles = 0;
int posicion = -1;
int hayCapacidad = 0;
int totalProductos = 0;

// prototipos de funciones
void mostrarMenu();
void limpiarBuffer();
int comparar(char a[], char b[]);
void calcularTotales(float *t, float *r);
void mostrarResultado();
void funcionEditar();
void funcionEliminar();
void registroTiempoRecursos();
void registroProductos(char productos[MAX_PRODUCTOS][30], float tiempo[MAX_PRODUCTOS], float recursos[MAX_PRODUCTOS], int cantidadDemandada[MAX_PRODUCTOS]);
void buscarProducto();
void mostrarProductos();

void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int comparar(char a[], char b[])
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return 1;
        }
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0')
    {
        return 0;
    }
    return 1;
}

void mostrarMenu()
{
    int opcion;
    while (1)
    {
        printf(" \n========== MENU ==========\n ");
        printf("Escoja una opcion: \n");
        printf("\n");
        printf("1. Registro de tiempo y recursos disponibles en fabrica.\n");
        printf("2. Registro de Productos.\n");
        printf("3. Editar y Eliminar Productos. \n");
        printf("4. Mostrar productos.\n");
        printf("5. salir\n");
        printf("Ingrese su eleccion: ");

        if (scanf("%d", &opcion) != 1)
        {
            limpiarBuffer();
            printf("\nOpcion invalida\n");
            continue;
        }
        limpiarBuffer();

        switch (opcion)
        {
        case 1:
            registroTiempoRecursos();
            break;

        case 2:
            registroProductos(productos, tiempo, recursos, cantidadDemandada);
            break;

        case 3:
            buscarProducto();
            break;

        case 4:
            mostrarProductos();
            mostrarResultado();
            break;

        case 5:
            printf("Finalizando...");
            exit(0);
            break;

        default:
            printf("\nOpcion no valida, ingrese nuevamente\n");
            break;
        }
    }
}
void registroTiempoRecursos()
{
    printf("\nIngresa las horas disponibles en fabrica: ");
    if (scanf("%d", &horasDisFabrica) != 1 || horasDisFabrica <= 0)
    {
        limpiarBuffer();
        printf("\n Error: las horas deben ser mayores a 0");
        return;
    }
    limpiarBuffer();
    printf("\nIngrea los recursos disponibles en la fabrica: ");
    if (scanf("%f", &recursosDisponibles) != 1 || recursosDisponibles <= 0)
    {
        limpiarBuffer();
        printf("\n Error: recursos deben ser mayores a 0\n");
        return;
    }
    limpiarBuffer();

    hayCapacidad = 1;

    printf("\n Capacidad guardada: %d horas y %.2f recursos\n", horasDisFabrica, recursosDisponibles);
}

void registroProductos(char productos[MAX_PRODUCTOS][30], float tiempo[MAX_PRODUCTOS], float recursos[MAX_PRODUCTOS], int cantidadDemandada[MAX_PRODUCTOS])
{
    int p;

    if (hayCapacidad == 0)
    {
        printf("Registre primero la capcidad de la fabrica (opcion 1)\n");
        return;
    }

    if (totalProductos >= MAX_PRODUCTOS)
    {
        printf("no se pueden registrar mas productos (maximo %d)\n", MAX_PRODUCTOS);
        return;
    }

    p = totalProductos;

    printf("\nIngrese el producto #%d\n", p + 1);
    fgets(productos[p], 30, stdin);
    if (productos[p][strlen(productos[p]) - 1] == '\n')
    {
        productos[p][strlen(productos[p]) - 1] = '\0';
    }

    if (productos[p][0] == '\0')
    {
        printf("el nombre no puede estar vacio\n");
        return;
    }

    printf("\nIngrese el tiempo unitario: ");
    if (scanf("%f", &tiempo[p]) != 1 || tiempo[p] <= 0)
    {
        limpiarBuffer();
        printf("Tiempo Invalido\n");
        return;
    }
    limpiarBuffer();

    printf("\ningrese la cantidad de recursos utilizados en el producto: ");
    if (scanf("%f", &recursos[p]) != 1 || recursos[p] <= 0)
    {
        limpiarBuffer();
        printf("Recursos invalidos\n");
        return;
    }
    limpiarBuffer();

    printf("\nIngrese la cantidad demandada: ");
    if (scanf("%d", &cantidadDemandada[p]) != 1 || cantidadDemandada[p] <= 0)
    {
        limpiarBuffer();
        printf("Cantidad demandada invalida");
        return;
    }
    limpiarBuffer();

    totalProductos++;
    printf("\nProducto Guardado: %s\n", productos[p]);
}

void calcularTotales(float *t, float *r)
{
    int i;
    *t = 0;
    *r = 0;

    for (i = 0; i < totalProductos; i++)
    {
        *t = *t + (tiempo[i] * cantidadDemandada[i]);
        *r = *r + (recursos[i] * cantidadDemandada[i]);
    }
}

void mostrarResultado()
{
    float tTotal, rTotal;

    if (hayCapacidad == 0)
    {
        printf("\nAun no se ha registrado la capacidad de la fabrica\n");
        return;
    }

    if (totalProductos == 0)
    {
        printf("\nAun no hay productos registrados\n");
        return;
    }

    calcularTotales(&tTotal, &rTotal);

    printf("\n------ RESULTADO ------\n");
    printf("Tiempo necesario  : %.2f\n", tTotal);
    printf("Recursos necesarios: %.2f\n", rTotal);
    printf("Horas disponibles : %d\n", horasDisFabrica);
    printf("Recursos disponibles: %.2f\n", recursosDisponibles);

    if (tTotal <= horasDisFabrica && rTotal <= recursosDisponibles)
    {
        printf("La fabrica SI puede cumplir con la demanda\n");
    }
    else
    {
        printf("La fabrica NO puede cumplir con la demanda\n");
        if (tTotal > horasDisFabrica)
        {
            printf("   Falta tiempo de produccion\n");
        }
        if (rTotal > recursosDisponibles)
        {
            printf("   Faltan recursos\n");
        }
    }
}

void buscarProducto()
{
    int i;
    char nombre[30];
    int opcionBuscar;
    posicion = -1; // se reinicia para cada nueva busqueda
    printf("Ingrese el nombre buscado: \n");
    fgets(nombre, 30, stdin);
    if (nombre[strlen(nombre) - 1] == '\n')
    {
        nombre[strlen(nombre) - 1] = '\0';
    }

    for (i = 0; i < totalProductos; i++)
    {
        if (comparar(productos[i], nombre) == 0)
        {
            posicion = i;
            break;
        }
    }

    if (posicion == -1)
    {
        printf("\n valor invalido, ingrese nuevamente");
        return;
    }

    printf("\nProducto Encontrado");
    printf("  Nombre: %s\n", productos[posicion]);
    printf("  Tiempo: %.2f\n", tiempo[posicion]);
    printf("  Recursos: %.2f\n", recursos[posicion]);
    printf("  Cantidad: %d\n", cantidadDemandada[posicion]);

    printf("\nDesea editar o eliminar los datos del producto? ");
    printf("\n1. Editar");
    printf("\n2. Eliminar");
    printf("\n3. Cancelar");
    printf("\nIngrese su eleccion");
    scanf("%d", &opcionBuscar);
    limpiarBuffer();

    switch (opcionBuscar)
    {
    case 1:
        funcionEditar();
        break;

    case 2:
        funcionEliminar();
        break;

    case 3:
        break;

    default:
        printf("\nProducto no encontrado\n");
        break;
    }
}

void funcionEditar()
{
    char nuevo[30];
    int opc;

    printf("\nDesea cambiar el nombre? (1=si / 2=no): ");
    if (scanf("%d", &opc) != 1)
    {
        limpiarBuffer();
        printf("Opcion invalida\n");
        return;
    }
    limpiarBuffer();

    if (opc == 1)
    {
        printf("Ingrese el nuevo nombre: ");
        fgets(nuevo, 30, stdin);
        if (nuevo[strlen(nuevo) - 1] == '\n')
        {
            nuevo[strlen(nuevo) - 1] = '\0';
        }
        if (nuevo[0] != '\0')
        {
            strcpy(productos[posicion], nuevo);
        }
        else
        {
            printf("Nombre vacio, se queda el anterior\n");
        }
    }

    printf("Nuevo tiempo por unidad: ");
    if (scanf("%f", &tiempo[posicion]) != 1 || tiempo[posicion] <= 0)
    {
        limpiarBuffer();
        printf("Tiempo invalido\n");
        return;
    }
    limpiarBuffer();

    printf("Nuevos recursos por unidad: ");
    if (scanf("%f", &recursos[posicion]) != 1 || recursos[posicion] <= 0)
    {
        limpiarBuffer();
        printf("Recursos invalidos\n");
        return;
    }
    limpiarBuffer();

    printf("Nueva cantidad demandada: ");
    if (scanf("%d", &cantidadDemandada[posicion]) != 1 || cantidadDemandada[posicion] <= 0)
    {
        limpiarBuffer();
        printf("Cantidad invalida\n");
        return;
    }
    limpiarBuffer();

    printf("\nProducto actualizado\n");
}

void funcionEliminar()
{
    int i;
    for (i = posicion; i < totalProductos - 1; i++)
    {
        strcpy(productos[i], productos[i + 1]);
        tiempo[i] = tiempo[i + 1];
        recursos[i] = recursos[i + 1];
        cantidadDemandada[i] = cantidadDemandada[i + 1];
    }
    totalProductos--;

    /* limpio la ultima posicion que ya quedo libre */
    productos[totalProductos][0] = '\0';
    tiempo[totalProductos] = 0;
    recursos[totalProductos] = 0;
    cantidadDemandada[totalProductos] = 0;

    printf("\nProducto eliminado\n");
}

void mostrarProductos()
{
    int i;

    if (totalProductos == 0)
    {
        printf("No hay productos registrados");
    }
    else
    {
        for (i = 0; i < totalProductos; i++)
        {
            printf("\n");
            printf("Existen datos registrados para producto #%d\n", i + 1);
            printf("Nombre del producto: %s\n", productos[i]);
            printf("Tiempo por Unidad: %f\n", tiempo[i]);
            printf("Recursos por Unidad: %f\n", recursos[i]);
            printf("Cantidad demandada del producto: %d\n", cantidadDemandada[i]);
            printf("\n");
        }
    }
}

int main()
{
    int opcion;

    mostrarMenu(opcion);

    return 0;
}