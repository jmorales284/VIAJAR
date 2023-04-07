//- 6 de abril del 2023
//- hora: 10:30
//- version de su codigo: 6
//- Autores: Ing(c) Juan Manuel Morales Santacruz - Ing(c) Cristian David Arango Torres
//- Nombre del lenguaje utilizado: c++
//- Versión del lenguaje utilizado: c11
//- Presentado a: Francisco Medina Aguirre
//- Universidad Tecnológica de Pereira
//- Programa de: Ingeniería de Sistemas y Computación
//- Asignatura: IS304 estructura de datos
//- Archivo main que funciona como menu para hacer el llamado a las funciones de la libreria "lists.h" que son funciones que nos permite hacer el manejo 
//- adecuado de los vuelos que realiza periodicamente la aerolinea "VIAJAR"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "lists.h" 

void menu() //funcion para imprimir el menu
{
    system("cls"); //limpiamos la pantalla
    printf("+----+----------------------------------------------------------+\n"); //mensaje de notificacion
    printf("|                             Menu                              |\n"); //mensaje de notificacion
    printf("+----+----------------------------------------------------------+\n"); //mensaje de notificacion
    printf("|  1  | Adicionar vuelos                                        |\n"); //mensaje de notificacion
    printf("|  2  | Adicionar pasajeros                                     |\n"); //mensaje de notificacion
    printf("|  3  | Consultar pasajeros de vuelos                           |\n"); //mensaje de notificacion
    printf("|  4  | Consultar vuelos programados                            |\n"); //mensaje de notificacion
    printf("|  5  | Consultar vuelos realizados                             |\n"); //mensaje de notificacion
    printf("|  6  | Consultar vuelos de una persona                         |\n"); //mensaje de notificacion
    printf("|  7  | Modificar estado de vuelo                               |\n"); //mensaje de notificacion
    printf("|  8  | Registrar cuando un pasajero pasa a bordo               |\n"); //mensaje de notificacion
    printf("|  0  | Salir                                                   |\n"); //mensaje de notificacion
    printf("+----+----------------------------------------------------------+\n"); //mensaje de notificacion
    printf("Ingrese la opcion: "); //mensaje de notificacion
}

int main() //funcion main
{
    airline myAirline; // creamos la lista myAirline
    passenger passengers; //dato passengers para los pasajeros
    flight flights; //dato fligths para los vuelos
    char flightNumber[7]="", id[11]=""; // numero de vuelo y cedula
    int i = 0; //interador
    char character = 0; //caracter
    myAirline.flightList = NULL; // inicializamos la lista de flight como vacia
    int op, option;// variable que vamos a usar para que el usuario ingrese la opcion a realizar para el menu

    upload(myAirline); //cargamos el contenido de los archivos en memoria
    
    do //hacer
    {
        menu(); //imprimir menu
        fflush(stdin); //limpiamos el buffer del teclado
        scanf("%i", &op); //leemos la opcion del menu
        switch (op)
        {
        case 1:
            system("cls"); //limpiamos la pantalla //limpiamos pantalla
            restartSructs(passengers,flights); //reiniciamos estructuras
            printf("Porfavor ingrese el numero de vuelo: "); //mensaje de notificacion
            scanf("%s", &flights.flightNumber); //escaneamos el numero de vuelo
            printf("Porfavor ingrese la ciudad de origen: "); //mensaje de notificacion
            scanf("%s", &flights.origin); //escaneamos la ciudad de origen
            printf("Porfavor ingrese la ciudad de destino: "); //mensaje de notificacion
            scanf("%s", &flights.arrival);  //escaneamos la ciudad de destino
            printf("Porfavor ingrese la matricula del avion: "); //mensaje de notificacion
            scanf("%s", &flights.planeId);  //escaneamos la matricula del avion
            printf("Porfavor ingrese el nombre del piloto: "); //mensaje de notificacion
            fflush(stdin); //limpiamos el buffer del teclado
            i=0; //reiniciamos le iterador 
            while (character != 10) //mientras no sea el "enter"
            {
                character = getchar(); //el caracter sera igual a la tecla que presionemos
                if (character != 10) //si la tecla no es "enter"
                    flights.pilotName[i] = character; //asignamos el caracter a el string

                i++; //sumamos uno al contador
            }
            printf("Porfavor ingrese la hora de vuelo (ej: ingresa las '10:45'): "); //mensaje de notificacion
            scanf("%s", &flights.fligthTime);  //escaneamos la hora del vuelo
            printf("Porfavor ingrese la fecha de vuelo (ej: ingresa '31/03/23'): "); //mensaje de notificacion
            scanf("%s", &flights.fligthDate);  //escaneamos la fecha del vuelo
            printf("Porfavor ingrese el estado del vuelo: "); //mensaje de notificacion
            scanf("%i", &flights.status);  //escaneamos el estado del vuelo
            addFlight(myAirline, flights, 0); //llamamos a la funcion para agregar a la lista
            i = 0; //reiniciamos el iterador
            character = 0; //reiniciamos el caracter
            break; //fin del caso
        case 2:
            system("cls"); //limpiamos la pantalla
            restartSructs(passengers,flights); //reiniciamos estructurs
            memset(flightNumber, 0, sizeof(flightNumber)); //reiniciamos el contenido del string
            printf("Porfavor ingrese el numero de vuelo: "); //mensaje de notificacion
            scanf("%s", flightNumber);  //escaneamos el numero de vuelo
            printf("Porfavor ingrese el numero de id: "); //mensaje de notificacion
            scanf("%s", &passengers.id);  //escaneamos la cedula
            printf("Porfavor ingrese el nombre del pasajero: "); //mensaje de notificacion
            fflush(stdin); //limpiamos el buffer del teclado
            i=0; //reiniciamos le iterador
            while (character != 10) //mientras no sea el "enter"
            {
                character = getchar(); //el caracter sera igual a la tecla que presionemos
                if (character != 10) //si la tecla no es "enter"
                    passengers.name[i] = character; //asignamos el caracter a el string

                i++; //sumamos uno al contador
            }
            printf("Porfavor ingrese el telefono del pasajero: "); //mensaje de notificacion
            scanf("%s", &passengers.phone);  //escaneamos el numero de telefono
            addPassenger(myAirline, flightNumber, passengers, 1, 0);//llamamos a la funcion para agregar a la lista
            break; //fin del caso
        case 3:
            system("cls"); //limpiamos la pantalla
            restartSructs(passengers,flights); //reiniciamos estructurs
            memset(flightNumber, 0, sizeof(flightNumber)); //reiniciamos el contenido del string
            printf("Ingresa el numero del vuelo: "); //mensaje de notificacion
            scanf("%s", flightNumber);  //escaneamos el numero de vuelo
            passengerFligths(myAirline, flightNumber);//llamamos a la funcion para ver los pasajeros de un vuelo
            break; //fin del caso
        case 4:
            system("cls"); //limpiamos la pantalla
            restartSructs(passengers,flights); //reiniciamos estructurs
            schedulesFlights(myAirline); //llamamos a la funcion para ver los vuelos programados
            break; //fin del caso
        case 5:
            system("cls"); //limpiamos la pantalla
            restartSructs(passengers,flights); //reiniciamos estructurs
            finishedFlights(myAirline); //llamamos a la funcion para ver los vuelos realizados
            break; //fin del caso
        case 6:
            system("cls"); //limpiamos la pantalla
            restartSructs(passengers,flights); //reiniciamos estructurs
            memset(id, 0, sizeof(id)); //reiniciamos el string
            printf("Ingresa la id de la persona a consultar: "); //mensaje de notificacion
            scanf("%s",id);  //escaneamos la cedula
            peopleFlights(myAirline, id);//llamamos a la funcion para ver los vuelos de una persona
            break; //fin del caso
        case 7:
            system("cls"); //limpiamos la pantalla
            restartSructs(passengers,flights); //reiniciamos estructurs
            memset(flightNumber, 0, sizeof(flightNumber)); //reiniciamos el contenido del string
            printf("Ingresa el numero del vuelo a modificar (a realizado): "); //mensaje de notificacion
            scanf("%s", flightNumber);  //escaneamos el numero de vuelo
            changeFlightStatus(&myAirline, flightNumber);//llamamos a la funcion para cambiar el estado de un vuelo
            break; //fin del caso
        case 8:
            system("cls"); //limpiamos la pantalla
            restartSructs(passengers,flights); //reiniciamos estructurs
            memset(flightNumber, 0, sizeof(flightNumber)); //reiniciamos el contenido del string
            memset(id, 0, sizeof(id)); //reiniciamos el string
            printf("Ingresa el numero del vuelo: "); //mensaje de notificacion
            scanf("%s", flightNumber);  //escaneamos el numero de vuelo
            printf("Ingresa la id de la persona a modificar (a bordo): "); //mensaje de notificacion
            scanf("%s",id);  //escaneamos la cedula
            changePassengerStatus(&myAirline,id, flightNumber);//llamamos a la funcion para cambiar el estado de un pasajero
            break; //fin del caso
        }
        printf("\n\n"); //mensaje de notificacion
        system("pause"); //presione una tecla para continuar
    } while (op != 0); //mientras que
    return 0;
}
