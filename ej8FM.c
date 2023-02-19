/*En el Call Center de una empresa telefónica, un asesor tiene N llamadas en cola de espera y debe atender 
por hora no más de 40 llamadas. El sistema registra el número de teléfono y localidad de los usuarios en 
espera. Se desea: obtener la cantidad de llamadas en espera en esa hora, eliminar las llamadas de la cola 
de espera a medida que se vayan atendiendo (utilizar la implementación con frente móvil) y generar un 
listado con todos los números que fueron atendidos durante una hora.*/

/*Declaracion de librerias*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*Definicion de constante maxima*/
#define MAX 40

/*Declaracion de tipo de datos personalizados*/
typedef char tString[20];
typedef struct{
	tString localidad;
	int telefono;
}tDatosUsuario;

typedef tDatosUsuario tArrayLlamada[MAX];
typedef struct{
	tArrayLlamada lista;
	int frente, final;
}tCola;

/*Declaración de prototipo*/
void crearColaVacia();
bool colaVacia(tCola);
bool colaLlena(tCola);
void registrarLlamada(int, tString);
int cantidadLlamadasEspera(tCola); /*Llamadas en espera*/
void listadoLlamadasAtendidas(); /*Llamadas atendidas*/
void atenderLlamadaFM();
void menu();

/*Declaracion de variables globales*/
tCola vColaLlamada;

/*Funcion principal*/
int main (){
	crearColaVacia();
	menu();
	return 0;
}

/*Implementacion de funciones*/
void crearColaVacia(){
	/*Inicializa frente y final*/
	vColaLlamada.frente = -1;	
	vColaLlamada.final = -1;
}

bool colaVacia(tCola pCola){
	return (pCola.frente == -1 && pCola.final == -1);
}

bool colaLlena(tCola pCola){
	return (pCola.final == (MAX - 1));
}

void menu(){
	tDatosUsuario usuario;
	int menu;
	do{
		printf("\t\t\t-----------------------------------------\n");
		printf("\t\t\t|\t\tM E N U\t\t\t|\n");
		printf("\t\t\t-----------------------------------------\n");	
		printf("\t\t\t|\t1. Agregar llamadas\t\t|\n");
		printf("\t\t\t|\t2. Mostrar cantidad de llamadas\t|\n");
		printf("\t\t\t|\t3. Atender y eliminar llamada\t|\n");
		printf("\t\t\t|\t4. Listado de numeros atendidos |\n");	
		printf("\t\t\t|\t0. Salir\t\t\t|\n");
		printf("\t\t\t-----------------------------------------\n");
		printf("\n\t\t\tSeleccione una opcion del menu:");
		scanf("%d", &menu);
		system("cls");
		switch (menu){
			case 1:{
				/*Solicitar ingresar datos por teclado*/
				printf("Ingresar telefono del usuario: ");
				scanf("%d", &usuario.telefono);
				printf("Ingresar localidad del usuario: ");
				fflush(stdin);
				gets(usuario.localidad);
				registrarLlamada(usuario.telefono, usuario.localidad);
				break;
			}
			case 2:{
					if (colaVacia(vColaLlamada)){
						printf("No hay llamadas en espera! \n");
					}else{
						printf("Cantidad de llamadas en espera: %d \n", cantidadLlamadasEspera(vColaLlamada));
					}				
				break;
			}
			case 3: atenderLlamadaFM();
				break;
			case 4: listadoLlamadasAtendidas();
				break;
			default: {
				if (menu == 0){
					printf("Hasta luego!\n");
				}else{
					printf("Opcion incorrecta! \n");	
				}
			} 
		}
		system("pause");
		system("cls");
	}while(menu != 0);
}

void registrarLlamada(int pTelefono, tString pLocalidad){
	tDatosUsuario usuario;
	/*Verificar que haya espacio libre*/
	if (colaLlena(vColaLlamada)){
		printf("No se puede registrar mas llamadas\n");
	}else{
		/*Actualizar indice final*/
		vColaLlamada.final = vColaLlamada.final + 1;
		/*Almacenar el elemento en la lista*/
		vColaLlamada.lista[vColaLlamada.final].telefono = pTelefono;
		strcpy(vColaLlamada.lista[vColaLlamada.final].localidad, pLocalidad);
		/*Verificar que se inserte el primer elemento*/
		if(vColaLlamada.final == 0){
			/*Es el primer elemento*/
			vColaLlamada.frente = 0;			
		}
		/*Emitir mensaje de ingreso*/
		printf("Llamada en espera: telefono %d con localidad en %s\n", vColaLlamada.lista[vColaLlamada.final].telefono, vColaLlamada.lista[vColaLlamada.final].localidad);
	}
}
int cantidadLlamadasEspera(tCola pCola){
	
	return (pCola.final - pCola.frente + 1);		
}

void atenderLlamadaFM(){

	/*Verificar que haya lugar ocupado en la cola*/
	if(colaVacia(vColaLlamada)){
		printf("No hay llamadas en espera!\n");
	}else{
		/*Mensaje de eliminado*/
		printf("Llamada de %d de la localidad %s fue atendido\n", vColaLlamada.lista[vColaLlamada.frente].telefono, vColaLlamada.lista[vColaLlamada.frente].localidad);
		vColaLlamada.frente = vColaLlamada.frente + 1;
		printf("Llamada eliminada!\n");
	}	
}

void listadoLlamadasAtendidas(){
	int i;
	/*Verificar que haya espacio ocupado en cola*/
	if (colaVacia(vColaLlamada)){
		printf("No hay llamadas atendidas\n");
	}else{
		if (vColaLlamada.frente == 0){
			printf("No se atendieron las llamadas registradas\n");
		}else{
			printf("Listado de llamadas atendidas:\n");
				for (i=0; i<vColaLlamada.frente; i++){
					printf("\t%d%c llamada atendida: %d de la locadad de %s\n", i+1, 167, vColaLlamada.lista[i].telefono, vColaLlamada.lista[i].localidad);
				}			
		}
	}

}
 
