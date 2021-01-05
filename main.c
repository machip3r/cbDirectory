/*

    Braulio José Baca Barbosa

    Descripción: Implementar una lista enlazada para el manejo de un agenda de información de personas.
        La cual contenga la siguiente información:
            - ID
            - Nombre
            - Apellido Paterno
            - Apellido Materno
            - Dirección
            - Teléfono
            - Correo Electrónico

        El programa debe contener un menú que permita realizar las siguientes operaciones:
            1. Ingresar un nuevo registro
            2. Borrar un registro
            3. Buscar un registro:
                a. Por ID
                b. Por nombre
                c. Por apellido paterno
            4. Mostrar la lista completa
            5. Ordenar la lista
                a. Por nombre
                b. Por apellido paterno
                c. Por apellido materno

        Ejemplo de captura y almacenamiento de la lista en un archivo:
        2 - n registros en la agenda
        1 - ID
        Pedro - Nombre
        Gonzalez - Apellido Paterno
        Perez - Apellido Materno
        Conocida - Dirección
        4641002030 - Teléfono
        peter@gmail.com - Correo Electrónico
        2 - ID
        ...

*/

// Directivas del preprocesador
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declaraciones globales
// Estructuras
typedef struct {
    int id_guy;
    char name[80];
    char fLastName[80];
    char mLastName[80];
    char address[200];
    char phone[15];
    char email[200];
} Guy;

typedef struct {
    struct Node* next;
    Guy* guy;
} Node;

// Prototipos de funciones
// PRINCIPALES
// Creación
Node* createNodeList(Guy*);
// Manipulación
int addGuyToList(Node**);
int deleteGuyFromList(Node**, int); // edit
// Búsqueda
int searchGILByID(Node*, int);
int searchGILByName(Node*, char*);
int searchGILByFLastName(Node*, char*);
// Muestra
int showGuysList(Node*);
// Ordenamiento
int orderGILByName(Node*); // edit
int orderGILByFLastName(Node*); // edit
int orderGILByMLastName(Node*); // edit
// Carga
int loadGuysInList(Node**);
// Guardado
int saveGuysFromList(Node*);

// DEPENDIENTES
// Manipulación
int getNGuys(Node*);
int addGuyToListFromFile(Node**, Guy*);
Guy* setInfoGuy();
// Muestra
int showGuyInfo(Node*);
int showGuysListWOrder(Node*, int, int*); // edit

// Función principal
int main() {
    // Declaración e inicialización de variables
    Node* listGuy = NULL;
    Guy* guy = NULL;
    int optionM = -1, optionSM = -1, idGuy = 0;
    char nameGuy[80], fLastNameGuy[80];

    // Presentación
    printf("\nPráctica listas enlazadas, ordenamiento y busqueda \n\n");
    printf("\nBienvenido a la agenda\n\n");

    // Buscar y cargar el archivo automaticamente
    loadGuysInList(&listGuy)
        ? printf("\n\t- No se encontro el archivo 'agenda.txt' para cargar\n\n")
        : printf("\n\t- Agenda cargada correctamente con el archivo 'agenda.txt'\n\n");

    // Menú de acciones
    do {
        // Impresiones estéticas
        printf("\t[ 1 ] Agregar persona a la agenda");
        printf("\n\t[ 2 ] Eliminar persona de la agenda");
        printf("\n\t[ 3 ] Buscar persona");
        printf("\n\t[ 4 ] Mostrar la agenda");
        printf("\n\t[ 5 ] Ordenar la agenda");
        printf("\n\t[ 6 ] Guardar agenda en 'agenda.txt'");
        printf("\n\t[ 7 ] Salir");

        // Solicitud de variable
        printf("\n\nIndica la opcion: ");
        // Lectura de variable
        scanf("%d", &optionM);

        // Acciones del menú
        switch(optionM) {
            case 1:
                // Agregar persona
                addGuyToList(&listGuy);
                // Asignación de valor a opción para mantener el menú
                optionM= -1;
                break;
            case 2:
                // Solicitud de variable
                printf("\nIngresa el ID de la persona que quieres eliminar\n(Ingresa '-1' si quieres regresar al menu): ");
                // Lectura de variable
                scanf("%d", &idGuy);
                // Decisión
                (idGuy > 0)
                    // Eliminar persona
                    ? deleteGuyFromList(&listGuy, idGuy)
                    // Impresión estética
                    : printf("\n\tVolviendo al menu...\n\n");

                // Asignación de valor a opción para mantener el menú
                optionM = -1;
                break;
            case 3:
                do {
                    // Impresiones estéticas
                    printf("\nBuscar persona en la agenda por: ");
                    printf("\n\t[ 1 ] ID");
                    printf("\n\t[ 2 ] Nombre");
                    printf("\n\t[ 3 ] Apellido Paterno");
                    printf("\n\t[ 4 ] Regresar al menu principal");

                    // Solicitud de variable
                    printf("\n\nIndica la opcion: ");
                    // Lectura de variable
                    scanf("%d", &optionSM);

                    // Acciones del menú
                    switch (optionSM) {
                        case 1:
                            // Solicitud de variable
                            printf("\nIngresa el ID de la persona que quieres buscar\n(Ingresa '-1' si quieres regresar al menu): ");
                            // Lectura de variable
                            scanf("%d", &idGuy);
                            // Decisión
                            (idGuy > 0)
                                // Buscar persona por ID
                                ? searchGILByID(listGuy, idGuy)
                                // Impresión estética
                                : printf("\n\tVolviendo al menu...\n\n");

                            // Asignación de valor a opción para mantener el menú
                            optionSM = -1;
                            break;
                        case 2:
                            do {
                                // Solicitud de variable
                                printf("\nIngresa el nombre de la persona que quieres buscar\n(Ingresa '-1' si quieres regresar al menu): ");
                                // Lectura de variable
                                scanf("%s", nameGuy);

                                // Validación
                                if(nameGuy[0] == '\0')
                                    printf("\n\nIngresa un nombre valido\n");
                            } while(nameGuy[0] == '\0');
                            // Decisión
                            (strcmp(nameGuy, "-1"))
                                // Buscar persona por nombre
                                ? searchGILByName(listGuy, nameGuy)
                                // Impresión estética
                                : printf("\n\tVolviendo al menu...\n\n");

                            // Asignación de valor a opción para mantener el menú
                            optionSM = -1;
                            break;
                        case 3:
                            do {
                                // Solicitud de variable
                                printf("\nIngresa el apellido paterno de la persona que quieres buscar\n(Ingresa '-1' si quieres regresar al menu): ");
                                // Lectura de variable
                                scanf("%s", fLastNameGuy);

                                // Validación
                                if(fLastNameGuy[0] == '\0')
                                    printf("\n\nIngresa un apellido paterno valido\n");
                            } while(fLastNameGuy[0] == '\0');
                            // Decisión
                            (strcmp(fLastNameGuy, "-1"))
                                // Buscar persona por apellido paterno
                                ? searchGILByFLastName(listGuy, fLastNameGuy)
                                // Impresión estética
                                : printf("\n\tVolviendo al menu...\n\n");

                            // Asignación de valor a opción para mantener el menú
                            optionSM = -1;
                            break;
                        case 4:
                            // Impresión estética
                            printf("\n\tVolviendo al menu principal...\n\n");
                            break;

                        default:
                            // Impresión estética
                            printf("\n\n--Introduce una opcion valida\n\n");
                            // Asignación de valor a opción para mantener el menú
                            optionSM = -1;
                            break;
                    }
                } while(optionSM < 0 || optionSM > 4);

                // Asignación de valor a opción para mantener el menú
                optionM = -1;
                break;
            case 4:
                // Mostrar la lista de personas
                showGuysList(listGuy);
                // Asignación de valor a opción para mantener el menú
                optionM = -1;
                break;
            case 5:
                do {
                    // Impresiones estéticas
                    printf("\nOrdenar agenda por: ");
                    printf("\n\t[ 1 ] Nombre");
                    printf("\n\t[ 2 ] Apellido Paterno");
                    printf("\n\t[ 3 ] Apellido Materno");
                    printf("\n\t[ 4 ] Regresar al menu principal");

                    // Solicitud de variable
                    printf("\n\nIndica la opcion: ");
                    // Lectura de variable
                    scanf("%d", &optionSM);

                    // Acciones del menú
                    switch (optionSM) {
                        case 1:
                            // Ordenamiento por nombre
                            orderGILByName(listGuy);

                            // Asignación de valor a opción para mantener el menú
                            optionSM = -1;
                            break;
                        case 2:
                            // Ordenamiento por apellido paterno
                            orderGILByFLastName(listGuy);

                            // Asignación de valor a opción para mantener el menú
                            optionSM = -1;
                            break;
                        case 3:
                            // Ordenamiento por apellido materno
                            orderGILByMLastName(listGuy);

                            // Asignación de valor a opción para mantener el menú
                            optionSM = -1;
                            break;
                        case 4:
                            // Impresión estética
                            printf("\n\tVolviendo al menu principal...\n\n");
                            break;

                        default:
                            // Impresión estética
                            printf("\n\n--Introduce una opcion valida\n\n");
                            // Asignación de valor a opción para mantener el menú
                            optionSM = -1;
                            break;
                    }
                } while(optionSM < 0 || optionSM > 4);

                // Asignación de valor a opción para mantener el menú
                optionM = -1;
                break;
            case 6:
                // Crear y guardar la agenda en el archivo 'agenda.txt'
                saveGuysFromList(listGuy)
                    ? printf("\n\t- No se pudo crear el archivo 'agenda.txt'\n\n")
                    : printf("\n\t- Agenda guardada exitosamente en el archivo 'agenda.txt'\n\n");
                // Asignación de valor a opción para mantener el menú
                optionM = -1;
                break;
            case 7:
                // Impresión estética
                printf("\n\nAdios!\n\n");
                break;

            default:
                // Impresión estética
                printf("\n\n--Introduce una opcion valida\n\n");
                // Asignación de valor a opción para mantener el menú
                optionM = -1;
                break;
        }
    } while(optionM < 0 || optionM > 7);

    // Dos saltos de línea
    printf("\n\n");

    // Finalización del programa sin errores
    return 0;
}

// FUNCIONES

// PRINCIPALES
// Función para crear un nodo
Node* createNodeList(Guy* g) {
    // Declaración de variables
    Node* node;

    // Asignación de memoria para el nodo
    node = (Node*) malloc(sizeof(Node));

    // Validación si la reservación de memoria fue correcta
    if(node == NULL) {
        printf("\n\nError al reservar memoria para la persona en la agenda\n");

        // Salida del programa con error
        exit(0);
    }

    // Inicialización de las variables del nodo
    (node -> guy) = g;
    (node -> next) = NULL;

    // Devolver el nodo creado
    return node;
}

// Función para agregar un nodo a la lista
int addGuyToList(Node** list) {
    // Declaración de variables
    Node *newNode, *aux;
    Guy* g;

    // Creación de la persona
    g = setInfoGuy(list);

    // Creación del nodo
    newNode = createNodeList(g);

    // Verificación de lista vacía
    if(*list == NULL) *list = newNode;
    else {
        // Búsqueda del nodo final
        aux = *list;
        while((aux -> next) != NULL)
            aux = (Node*) (aux -> next);

        // El nuevo nodo se posiciona al final
        (aux -> next) = (struct Node*) newNode;
    }

    // Impresión estética
    printf("\n\n\tSe agrego correctamente a la agenda\n\n");

    // Salida exitosa de la función
    return 0;
}

// Función para eliminar un nodo
int deleteGuyFromList(Node** list, int idGuy) {
    // Declaración e inicialización de variables
    Node *beforeEndNode, *endNode;
    Guy *lastGuy;

    // Verificación de lista vacía
    if(list == NULL) printf("\n--La agenda esta vacia\n\n");
    else {
        // Asignación del nodo lista al ultimo nodo
        endNode = *list;

        // Verificación del nodo siguiente del último nodo no es vacío
        if((endNode -> next) == NULL) {
            // Último nodo de la lista eliminado
            *list = NULL;

            // Liberación de memoria del último nodo
            free(endNode);
        } else {
            lastGuy = (endNode -> guy);

            if((lastGuy -> id_guy) == idGuy) {
                // Cambiar posición de los nodos de la lista
                while(((endNode -> next) != NULL) && idGuy != (lastGuy -> id_guy)) {
                    beforeEndNode = endNode; //adelanto una posicion la var ante.
                    endNode = (Node*) (endNode -> next); //avanzo al siguiente nodo.
                }

                // El penúltimo nodo pasa a ser eliminado
                (beforeEndNode -> next) = NULL;

                // Liberación de memoria del último nodo
                free(endNode);
            }
        }
    }
    // Impresión estética
    printf("\n\n\tSe elimino correctamente de la agenda\n\n");
    // Salida exitosa de la función
    return 0;
}

// Función para buscar una persona por ID
int searchGILByID(Node* list, int id) {
    // Declaración de variables
    Node* searchList;
    Guy* searchGuy;

    // Verificación de lista vacía
    if(list == NULL) printf("\n--La agenda esta vacia\n\n");
    else {
        // Asignación de lista y persona a variables temporales
        searchList = list;
        searchGuy = (searchList -> guy);

        // Búsqueda de la persona
        // Validación por si la persona buscada está en el primer nodo
        while((searchGuy -> id_guy) != id && (searchList -> next) != NULL) {
            searchList = (Node*) (searchList -> next);
            searchGuy = (searchList -> guy);
        }

        // Impresiones estéticas
        if((searchGuy -> id_guy) != id)
            printf("\n--No se encontro la persona buscada por ID\n");
        else showGuyInfo(searchList);
    }

    // Salida exitosa de la función
    return 0;
}

// Función para buscar una persona por nombre
int searchGILByName(Node* list, char* n) {
    // Declaración de variables
    Node* searchList;
    Guy* searchGuy;

    // Verificación de lista vacía
    if(list == NULL) printf("\n--La agenda esta vacia\n\n");
    else {
        // Asignación de lista y persona a variables temporales
        searchList = list;
        searchGuy = (searchList -> guy);

        // Búsqueda de la persona
        // Validación por si la persona buscada está en el primer nodo
        while(strcmp((searchGuy -> name), n) != 0 && (searchList -> next) != NULL) {
            searchList = (Node*) (searchList -> next);
            searchGuy = (searchList -> guy);
        }

        // Impresiones estéticas
        if(strcmp((searchGuy -> name), n) != 0)
            printf("\n--No se encontro la persona buscada por nombre\n");
        else showGuyInfo(searchList);
    }

    // Salida exitosa de la función
    return 0;
}

// Función para buscar una persona por apellido paterno
int searchGILByFLastName(Node* list, char* fln) {
    // Declaración de variables
    Node* searchList;
    Guy* searchGuy;

    // Verificación de lista vacía
    if(list == NULL) printf("\n--La agenda esta vacia\n\n");
    else {
        // Asignación de lista y persona a variables temporales
        searchList = list;
        searchGuy = (searchList -> guy);

        // Búsqueda de la persona
        // Validación por si la persona buscada está en el primer nodo
        while(strcmp((searchGuy -> fLastName), fln) != 0 && (searchList -> next) != NULL) {
            searchList = (Node*) (searchList -> next);
            searchGuy = (searchList -> guy);
        }

        // Impresiones estéticas
        if(strcmp((searchGuy -> fLastName), fln) != 0)
            printf("\n--No se encontro la persona buscada por apellido paterno\n");
        else showGuyInfo(searchList);
    }

    // Salida exitosa de la función
    return 0;
}

// Función para mostrar la lista de nodos
int showGuysList(Node* list) {
    // Declaración de variables
    Node* aux;
    Guy* guy;

    // Impresión estética
    printf("\n\tAgenda:\n\n");

    // Verificación de lista vacía
    if(list == NULL) printf("\n\t--La agenda esta vacia \n\n");
    else {
        // Asignación del primer nodo al nodo auxiliar
        aux = list;

        do {
            // Asignación de la persona a la variable
            guy = (aux -> guy);

            // Impresión de la persona
            printf("\t- %d\n", (guy -> id_guy));
            printf("\t\tApellido Paterno: %s\n", (guy -> fLastName));
            printf("\t\tApellido Materno: %s\n", (guy -> mLastName));
            printf("\t\tNombre: %s\n", (guy -> name));
            printf("\t\tDireccion: %s\n", (guy -> address));
            printf("\t\tCorreo electronio: %s\n\n", (guy -> email));

            // Asignación del siguiente nodo al nodo auxiliar
            aux = (Node*) (aux -> next);
        } while(aux != NULL);
    }

    // Salida exitosa de la función
    return 0;
}

// Función para ordenar la lista por nombre
int orderGILByName(Node* list) {
    // Declaración e inicialización de variables
    Node *selectedAux, *nextAux;
    int nG = 0, *o, indexAux = 0, smallestIndex = 0;

    // Verificación de lista vacía
    if(list == NULL) printf("\n--La agenda esta vacia\n\n");
    else {
        // Obtener el número de personas
        nG = (getNGuys(list));
        o = (int*) malloc(nG * sizeof(int));

        // Copia de la lista para no alterar datos
        selectedAux = list;

        // Inicialización del arreglo de orden
        for (int i = 0; i < nG; i++)
            (*(o + i)) = i;

        // Ordenamiento
        for(int i = 0; i < (nG - 1); i++) {
            // Asignación del índice menor
            smallestIndex = i;
            // Comparación de nombres
            for( int j = (i + 1); j < nG; j++ )
                if(strcmp(((selectedAux -> guy) -> name), ((nextAux -> guy) -> name)) < 0)
                    smallestIndex = j;
            // Intercambio de índices
            indexAux = (*(o + i));
            (*(o + i)) = (*(o + smallestIndex));
            (*(o + smallestIndex)) = indexAux;
        }

        // Muestra de los datos con el orden
        showGuysListWOrder(list, nG, o);
    }

    // Salida exitosa de la función
    return 0;
}

// Función para ordenar la lista por apellido paterno
int orderGILByFLastName(Node* list) {
    // Declaración e inicialización de variables
    Node *selectedAux, *nextAux;
    int nG = 0, *o, indexAux = 0, smallestIndex = 0;

    // Verificación de lista vacía
    if(list == NULL) printf("\n--La agenda esta vacia\n\n");
    else {
        // Obtener el número de personas
        nG = (getNGuys(list));
        o = (int*) malloc(nG * sizeof(int));

        // Copia de la lista para no alterar datos
        selectedAux = list;

        // Inicialización del arreglo de orden
        for (int i = 0; i < nG; i++)
            (*(o + i)) = i;

        // Ordenamiento
        for(int i = 0; i < (nG - 1); i++) {
            // Asignación del índice menor
            smallestIndex = i;
            // Comparación de apellidos
            for( int j = (i + 1); j < nG; j++ )
                if(strcmp(((selectedAux -> guy) -> name), ((nextAux -> guy) -> name)) < 0)
                    smallestIndex = j;
            // Intercambio de índices
            indexAux = (*(o + i));
            (*(o + i)) = (*(o + smallestIndex));
            (*(o + smallestIndex)) = indexAux;
        }

        // Muestra de los datos con el orden
        showGuysListWOrder(list, nG, o);
    }

    // Salida exitosa de la función
    return 0;
}

// Función para ordenar la lista por apellido materno
int orderGILByMLastName(Node* list) {
    // Declaración e inicialización de variables
    Node *selectedAux, *nextAux;
    int nG = 0, *o, indexAux = 0, smallestIndex = 0;

    // Verificación de lista vacía
    if(list == NULL) printf("\n--La agenda esta vacia\n\n");
    else {
        // Obtener el número de personas
        nG = getNGuys(list);
        o = (int*) malloc(nG * sizeof(int));

        // Copia de la lista para no alterar datos
        selectedAux = list;

        // Inicialización del arreglo de orden
        for (int i = 0; i < nG; i++)
            (*(o + i)) = i;

        // Ordenamiento
        for(int i = 0; i < (nG - 1); i++) {
            // Asignación del índice menor
            smallestIndex = i;
            // Comparación de apellidos
            for( int j = (i + 1); j < nG; j++ )
                if(strcmp(((selectedAux -> guy) -> name), ((nextAux -> guy) -> name)) < 0)
                    smallestIndex = j;
            // Intercambio de índices
            indexAux = (*(o + i));
            (*(o + i)) = (*(o + smallestIndex));
            (*(o + smallestIndex)) = indexAux;
        }

        // Muestra de los datos con el orden
        showGuysListWOrder(list, nG, o);
    }

    // Salida exitosa de la función
    return 0;
}

// Función para cargar la agenda desde un archivo
int loadGuysInList(Node** list) {
    // Declaración de variables
    FILE* file;
    Guy* g;
    int nG = 0;

    // Lectura del archivo y asignación a la variable
    file = fopen("agenda.txt", "r");

    // Validación por si el archivo no existe
    if(!file) return 1;

    // Lectura del número de personas que existen
    fscanf(file, "%d", &nG);

    // Validación por si no hay ninguna persona registrada
    if(nG <= 0) return 1;

    // Asignación de datos a cada persona y creación de persona
    for (int i = 0; i < nG; i++) {
        // Nueva persona
        g = (Guy*) malloc(sizeof(Guy));
        // ID
        fscanf(file, "%d", &(g -> id_guy));
        // Nombre
        fscanf(file, "%s", (g -> name));
        // Apellido Paterno
        fscanf(file, "%s", (g -> fLastName));
        // Apellido Materno
        fscanf(file, "%s", (g -> mLastName));
        // Dirección
        fscanf(file, "%s", (g -> address));
        // Teléfono
        fscanf(file, "%s", (g -> phone));
        // Correo electrónico
        fscanf(file, "%s", (g -> email));

        // Agregar persona a la agenda
        addGuyToListFromFile(list, g);
    }

    // Salida exitosa de la función
    return 0;
}

// Función para guardar la agenda en un archivo ("agenda.txt")
int saveGuysFromList(Node* list) {
    // Declaración de variables
    FILE* file;
    Node* aux;
    Guy* g;
    int nG = 0;

    // Verificación de lista vacía
    if(list == NULL) printf("\n--La agenda esta vacia\n\n");
    else {
        // Obtener el número de personas
        nG = getNGuys(list);

        // Creación del archivo y asignación a la variable
        file = fopen("agenda.txt", "w");
        // Validación por si el archivo no existe
        if(!file) return 1;
        // Impresión del número de personas
        fprintf(file, "%d\n", nG);

        // Uso de variable temporal para la manipulación de la lista
        aux = list;

        // Asignación de datos a cada persona y creación de persona
        for (int i = 0; i < nG; i++) {
            // Asignación de variable para obtener los datos
            g = (aux -> guy);
            // ID
            fprintf(file, "%d\n", (g -> id_guy));
            // Nombre
            fprintf(file, "%s\n", (g -> name));
            // Apellido Paterno
            fprintf(file, "%s\n", (g -> fLastName));
            // Apellido Materno
            fprintf(file, "%s\n", (g -> mLastName));
            // Dirección
            fprintf(file, "%s\n", (g -> address));
            // Teléfono
            fprintf(file, "%s\n", (g -> phone));
            // Correo electrónico
            fprintf(file, "%s\n", (g -> email));

            // Cambio de persona
            aux = (Node*) (aux -> next);
        }
    }

    // Salida exitosa de la función
    return 0;
}

// DEPENDIENTES
// Función para obtener el número de personas en la lista
int getNGuys(Node* list) {
    // Declaración de variables
    Node* aux = list;
    // Como la lista no está vacía se inicializa en 1
    int nG = 1;

    // Contador de personas
    do {
        nG++;
        aux = (Node*) (aux -> next);
    } while((aux -> next) != NULL);

    // Devolver el número de personas en la lista
    return nG;
}

// Función para agregar un nodo a la lista desde un archivo
int addGuyToListFromFile(Node** list, Guy* g) {
    // Declaración de variables
    Node *newNode, *aux;

    // Creación del nodo
    newNode = createNodeList(g);

    // Verificación de lista vacía
    if(*list == NULL) *list = newNode;
    else {
        // Búsqueda del nodo final
        aux = *list;
        while((aux -> next) != NULL)
            aux = (Node*) (aux -> next);

        // El nuevo nodo se posiciona al final
        (aux -> next) = (struct Node*) newNode;
    }

    // Salida exitosa de la función
    return 0;
}

// Función para capturar los datos de una persona
Guy* setInfoGuy() {
    // Declaración de variables
    Guy* guy = (Guy*) malloc(sizeof(Guy));

    // Lectura y validación de variable
    do {
        printf("\nID (entero): "); // asignación automática
        scanf("%d", &(guy -> id_guy));
        fflush(stdin);

        if((guy -> id_guy) < 0)
            printf("\n\nIngresa un ID valido\n");
    } while((guy -> id_guy) < 0);

    // Lectura y validación de variable
    do {
        printf("\nNombre: ");
        scanf("%s", (guy -> name));
        fflush(stdin);

        if((guy -> name[0]) == '\0')
            printf("\n\nIngresa un nombre valido\n");
    } while((guy -> name[0]) == '\0');

    // Lectura y validación de variable
    do {
        printf("\nApellido Paterno: ");
        scanf("%s", (guy -> fLastName));
        fflush(stdin);

        if((guy -> fLastName[0]) == '\0')
            printf("\n\nIngresa un apellido valido\n");
    } while((guy -> fLastName[0]) == '\0');

    // Lectura y validación de variable
    do {
        printf("\nApellido Materno: ");
        scanf("%s", (guy -> mLastName));
        fflush(stdin);

        if((guy -> mLastName[0]) == '\0')
            printf("\n\nIngresa un apellido valido\n");
    } while((guy -> mLastName[0]) == '\0');

    // Lectura y validación de variable
    do {
        printf("\nDireccion: ");
        scanf("%s", (guy -> address));
        fflush(stdin);

        if((guy -> address[0]) == '\0')
            printf("\n\nIngresa una direccion valida\n");
    } while((guy -> address[0]) == '\0');

    // Lectura y validación de variable
    do {
        printf("\nTelefono: ");
        scanf("%s", (guy -> phone));
        fflush(stdin);

        if((guy -> phone[0]) == '\0')
            printf("\n\nIngresa un telefono valido\n");
    } while((guy -> phone[0]) == '\0');

    // Lectura y validación de variable
    do {
        printf("\nCorreo electronico: ");
        scanf("%s", (guy -> email));
        fflush(stdin);

        if((guy -> email[0]) == '\0')
            printf("\n\nIngresa un correo electronico valido\n");
    } while((guy -> email[0]) == '\0');

    // Devolver la persona creada
    return guy;
}

// Función para mostrar una persona específica
int showGuyInfo(Node* node) {
    // Declaración de variables
    Guy* guy;

    // Impresión estética
    printf("\nDatos de la persona:\n\n");

    // Asignación de la persona a una variable
    guy = (node -> guy);

    // Impresión de la persona
    printf("- %d\n", (guy -> id_guy));
    printf("\tApellido Paterno: %s\n", (guy -> fLastName));
    printf("\tApellido Materno: %s\n", (guy -> mLastName));
    printf("\tNombre: %s\n", (guy -> name));
    printf("\tDireccion: %s\n", (guy -> address));
    printf("\tCorreo electronio: %s\n\n", (guy -> email));

    // Salida exitosa de la función
    return 0;
}

// Función para mostrar la lista con un orden específico
int showGuysListWOrder(Node* list, int nG, int* o) {
    Node* aux = list;

    /* while (i < nG) {
        if(aux == NULL) aux = list;
        for (int j = 0; j < nG; j++) {
            if((*(o + j)) == i) showGuyInfo(aux);

            aux = (Node*) (aux -> next);
        }
        i++;
    } */

    for (int i = 0; i < nG; i++) {
        if(aux == NULL) aux = list;
        for (int j = 0; j < nG; j++) {
            if((*(o + j)) == i) showGuyInfo(aux);

            aux = (Node*) (aux -> next);
        }
    }

    return 0;
}
