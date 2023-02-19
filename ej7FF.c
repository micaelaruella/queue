/*La represa Yaciretá tiene capacidad en su exclusa para 30 embarcaciones medianas. Las embarcaciones
llegan por un extremo y salen por el otro. Prefectura debe registrar el nombre de las embarcaciones que
se anotan para cruzar por día. Se necesita generar un listado de todas las embarcaciones anotadas en la
fecha para cruzar y la disponibilidad de lugar en esa fecha. Utilizar la implementación con frente fijo.*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX 3

/*Declaración de tipos de datos personalizados*/
typedef char tString[20];
typedef tString tArrayEmbarcacion[MAX];
typedef struct{
	tArrayEmbarcacion lista;
	int frente, final;
}tCola;

/*Declaración de prototipo*/
void crearColaVacia();
bool colaVacia(tCola);
bool colaLlena(tCola);
void registrarEmbarcacion(tString);
void eliminarEmbarcacionFF();
void listadoEmbarcaciones(tCola);
void disponibilidad();
void menu();
/*Declaración de variables globales*/
tCola vColaEmbarcacion;
/*Función principal*/
int main(){
	crearColaVacia();
	menu();
	return 0;
}
/*Implementacion de funciones*/
void crearColaVacia(){
	vColaEmbarcacion.frente = -1;
	vColaEmbarcacion.final = -1;
}

bool colaVacia(tCola pCola){
	return (pCola.frente == -1 && pCola.final == -1);
}

bool colaLlena(tCola pCola){
	return (pCola.final == (MAX - 1));
}

void menu(){
	tCola dato;
	int menu;
	do{
		tString nombre;
		printf("\t\t\t-------------------------------------------------\n");
		printf("\t\t\t|\t\tM E N U\t\t\t\t|\n");
		printf("\t\t\t-------------------------------------------------\n");	
		printf("\t\t\t|\t1. Agregar embarcacion\t\t\t|\n");
		printf("\t\t\t|\t2. Mostrar listado de embarcaciones\t|\n");
		printf("\t\t\t|\t3. Disponibilidad de lugar\t\t|\n");
		printf("\t\t\t|\t4. Eliminar embarcacion\t\t\t|\n");	
		printf("\t\t\t|\t0. Salir\t\t\t\t|\n");
		printf("\t\t\t-------------------------------------------------\n");
		printf("\n\t\t\tSeleccione una opcion del menu:");
		scanf("%d", &menu);
		system("cls");
		switch (menu){
			case 1:{
				printf("Ingrese el nombre de la embarcacion: ");
				fflush(stdin);
				gets(nombre);
				registrarEmbarcacion(nombre);
				break;
			}
			case 2: listadoEmbarcaciones(vColaEmbarcacion);
				break;
			case 3: disponibilidad();
				break;
			case 4: eliminarEmbarcacionFF();			
				break;
			default: printf("Opcion invalida!\n");
		}
		system("pause");
		system("cls");
	}while (menu != 0);
}

void registrarEmbarcacion(tString pNombre){
	/*Ver si hay lugar*/
	if (colaLlena(vColaEmbarcacion)){
		printf("No hay lugar\n");
	}else{
		/*Actualizar indice*/
		vColaEmbarcacion.final = vColaEmbarcacion.final + 1;
		/*Almacenar el elemento en la lista*/
		strcpy(vColaEmbarcacion.lista[vColaEmbarcacion.final], pNombre);
		/*Verificar que esté insertado el primer elemento*/
		if (vColaEmbarcacion.final == 0){
			/*Primer elemento*/	
			vColaEmbarcacion.final = 0;
		}
		printf("Embarcacion registrada: %s\n", vColaEmbarcacion.lista[vColaEmbarcacion.final]);	
	}
	
	
}
void eliminarEmbarcacionFF(){
	tString barcoEliminar;

	/*Variable auxilar para eliminar*/
	if (colaVacia(vColaEmbarcacion)){
		printf("No hay embarcaciones registradas\n");
	}else{
		int i;
		/*Resguardar el elemento a eliminar*/
		strcpy(barcoEliminar, vColaEmbarcacion.lista[vColaEmbarcacion.frente]);		
		/*Borrar el elemento que se encuentra en el frente*/
		strcpy(vColaEmbarcacion.lista[vColaEmbarcacion.frente], " ");		
		/*Reacomodar la lista*/
		for(i=0; i<vColaEmbarcacion.final; i++){
			strcpy(vColaEmbarcacion.lista[i], vColaEmbarcacion.lista[i+1]);
		}
		/*Borrar el valor duplicado al final*/
		strcpy(vColaEmbarcacion.lista[vColaEmbarcacion.final], " ");
		strcpy(vColaEmbarcacion.lista[vColaEmbarcacion.final], " ");
		/*Verificar si la cola tiene un solo elemento y actualizar índice*/
		if(vColaEmbarcacion.frente == vColaEmbarcacion.final){
			crearColaVacia();
		}else{
			vColaEmbarcacion.final = vColaEmbarcacion.final - 1;
		}
		/*Mensaje de eliminado*/
		printf("Embarcacion eliminada\n");
	}
	
}
void listadoEmbarcaciones(tCola pCola){
	int i;
	if(colaVacia(vColaEmbarcacion)){
		printf("No hay embarcaciones en la lista\n");
	}else{
		printf("Lista de nombres de embarcaciones registradas: ");
		for (i=0; i<=pCola.final; i++){
			printf("\n\t -%s\n", pCola.lista[i]);
		}
	}
}
void disponibilidad(){
		if(colaLlena(vColaEmbarcacion)){
		printf("No hay estacionamiento disponible\n");
	}else{
		printf("La disponibilidad de lugar es: %d\n\n", (MAX-1) - vColaEmbarcacion.final);
	}
	
}


