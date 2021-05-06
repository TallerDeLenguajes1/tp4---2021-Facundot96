#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)


typedef struct Tarea {
	int TareaID; //Numerado en ciclo iterativo
	char* Descripcion; //
	int Duracion; // entre 10 � 100
}Tarea;

void recorrerTarea(Tarea**, int);
void checkTarea(Tarea**, Tarea**, int);
void mostrarTareas(Tarea*);
Tarea* carga(int);
Tarea buscarTareaPalabra(Tarea**, int);


int main() {

	srand(time(NULL));

	Tarea** tareasPendientes, ** tareasRealizadas;
	int cantidadTareas;

	printf("Ingrese la cantidad de tareas: ");
	scanf_s("%d", &cantidadTareas);
	fflush(stdin);

	tareasRealizadas = (Tarea**)malloc(sizeof(Tarea*) * cantidadTareas);
	tareasPendientes = (Tarea**)malloc(sizeof(Tarea*) * cantidadTareas);
	


	recorrerTarea(tareasPendientes, cantidadTareas);
	checkTarea(tareasPendientes, tareasRealizadas, cantidadTareas);

	printf("\n\n--------TAREAS PENDIENTES---------");
	for (int i = 0; i < cantidadTareas; i++)
	{

		if (*(tareasPendientes + i) != NULL)
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
			printf("\n�La tarea %s se complet�? S/N:", tareas[i]->Descripcion);
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
				printf("\nERROR. Ingrese un par�metro v�lido");
			}
		}
	}

	return;
}

void mostrarTareas(Tarea* tareas) {

	printf("\n\nID de Tarea: %d", tareas->TareaID);
	printf("\nDescripci�n de tarea: %s", tareas->Descripcion);
	printf("\nDuraci�n de tarea: %d", tareas->Duracion);

	return;
}

Tarea buscarTareaPalabra(Tarea** tareas, int cantidad) {

	char buscarPal[50];
	char* palabraClave;

	printf("Ingresar la descripción de la tarea a buscar: ");
	scanf(" %s", &buscarPal);


	for (int indice = 0; buscarPal[indice] != '\0'; ++indice) {
		buscarPal[indice] = tolower(buscarPal[indice]);
	}

	for (int i = 0; i < cantidad; i++)
	{
		if (tareas[i] != NULL && strstr(tareas[i]->Descripcion, buscarPal))
		{
			printf("\n\nID de Tarea: %d", tareas[i]->TareaID);
			printf("\nDescripci�n de tarea: %s", tareas[i]->Descripcion);
			printf("\nDuraci�n de tarea: %d", tareas[i]->Duracion);
			return **(tareas + i);
		}
	}

	printf("No se encontraron resultados");
	return;
}