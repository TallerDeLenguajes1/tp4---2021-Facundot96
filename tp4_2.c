#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)


typedef struct Tarea {
	int TareaID; //Numerado en ciclo iterativo
	char* Descripcion; //
	int Duracion; // entre 10 – 100
}Tarea;

void recorrerTarea(Tarea**, int);
void checkTarea(Tarea**, Tarea**, int);
void mostrarTareas(Tarea *);
Tarea* carga(int);
Tarea* buscarTareaID(Tarea**, int);

int main() {

	srand(time(NULL));

	Tarea** tareasPendientes, ** tareasRealizadas, * tareaBuscada;
	int cantidadTareas;

	printf("Ingrese la cantidad de tareas: ");
	scanf_s("%d", &cantidadTareas);
	fflush(stdin);

	tareasRealizadas = (Tarea**)malloc(sizeof(Tarea*) * cantidadTareas);
	tareasPendientes = (Tarea**)malloc(sizeof(Tarea*) * cantidadTareas);
	tareaBuscada = (Tarea*)malloc(sizeof(Tarea*));

	recorrerTarea(tareasPendientes, cantidadTareas);

	tareaBuscada = buscarTareaID(tareasPendientes, cantidadTareas);
	mostrarTareas(tareaBuscada);




	checkTarea(tareasPendientes, tareasRealizadas, cantidadTareas);

	printf("\n\n--------TAREAS PENDIENTES---------");
	for (int i = 0; i < cantidadTareas; i++)
	{

		if (*(tareasPendientes+i) != NULL)
		{
			mostrarTareas(*(tareasPendientes + i));
		}

	}

	printf("\n\n--------TAREAS REALIZADAS---------");
	for (int i = 0; i < cantidadTareas; i++)
	{

		if (*(tareasRealizadas + i) != NULL)
		{
			mostrarTareas(*(tareasRealizadas + i));
		}

	}

	free(tareasPendientes);
	free(tareasRealizadas);

	return 0;
}

void recorrerTarea(Tarea** tareas, int cantidad) {

	for (int i = 0; i < cantidad; i++)
	{
		tareas[i] = carga(i);
	}
	return;
}

Tarea* carga(int i) {

	char nombreTarea[50];
	Tarea* aux = (Tarea*)malloc(sizeof(Tarea));
	
	
	printf("Ingresar la tarea a realizar: ");
	scanf(" %s", &nombreTarea);
	aux->TareaID = i + 1;
	aux->Descripcion = (char*)malloc(sizeof(char) * strlen(nombreTarea));
	strcpy(aux->Descripcion, nombreTarea);
	aux->Duracion = rand() % 91 + 10;

	return aux;
}

void checkTarea(Tarea** tareas, Tarea** tareasCompletadas, int cantidad) {

	int bandera;
	char check;


	for (int i = 0; i < cantidad; i++)
	{

		bandera = 0;

		while (bandera == 0)
		{
			printf("\n¿La tarea %s se completó? S/N:", tareas[i]->Descripcion);
			scanf(" %c", &check);
			check = tolower(check);

			if (check == 's' || check == 'n') {

				if (check == 's') {

					tareasCompletadas[i] = tareas[i];
					tareas[i] = NULL;
				}
				else {
					tareasCompletadas[i] = NULL;
				}
				bandera++;
			}
			else {
				printf("\nERROR. Ingrese un parámetro válido");
			}
		}
	}

	return;
}

void mostrarTareas(Tarea* tareas) {

	printf("\n\nID de Tarea: %d", tareas->TareaID);
	printf("\nDescripción de tarea: %s", tareas->Descripcion);
	printf("\nDuración de tarea: %d", tareas->Duracion);

	return;
}

Tarea* buscarTareaID(Tarea** tareas, int cantidad) {

	int searchId;

	printf("Ingrese el ID de la tarea que está buscando: ");
	scanf_s("%d", &searchId);

	if (searchId >= cantidad || searchId < 1) {

		printf("El ID buscado no pertenece a ninguna tarea.");
		buscarTareaID(tareas, cantidad);

	}


	return *(tareas + (searchId - 1));
}