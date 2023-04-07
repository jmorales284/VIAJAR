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
//- Archivo de cabecera que contiene las funciones que nos permite hacer el manejo 
//- adecuado de los vuelos que realiza periodicamente la aerolinea "VIAJAR" mediante el manejo de listas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estructura para guardar los datos de los pasajeros en la memoria
typedef struct
{
    char id[11]; //numero identificacion pasajero
    char name[21]; //nombre pasajero
    char phone[11]; //numero del pasajero
} passenger;

//estructura para guardar los datos de los vuelos en la memoria
typedef struct
{
    char flightNumber[7]; //numero de vuelo
    char origin[9]; //ciudad origen
    char arrival[9]; //ciudad destino
    char planeId[7]; //matricula avion
    char pilotName[21]; //nombre del piloto
    char fligthTime[8]; //hora del vuelo
    char fligthDate[8]; //fecha del vuelo
    int status; //estado del vuelo
} flight;

//estructura para guardar los datos de los pasajeros en una lista
struct passengerNode
{
    char id[11]; //numero identificacion pasajero
    char name[21]; //nombre pasajero
    char phone[11]; //numero del pasajero
    int status; // esta variable indica el estado del vuelo (1: reserva, 2: a bordo)
    passengerNode *next; //puntero al proximo nodo
};

//estructura para guardar los datos de los vuelos en una lista
struct flightNode
{
    char flightNumber[7]; //numero de vuelo
    char origin[9]; //ciudad origen
    char arrival[9]; //ciudad destino
    char planeId[7]; //matricula avion
    char pilotName[21]; //nombre del piloto
    char fligthTime[8]; //hora del vuelo
    char fligthDate[8]; //fecha del vuelo
    int status; // esta variable indica el status del vuelo (0: programado, 1: realizado)
    passengerNode *passengersList; //puntero a la lista de pasajeros
    flightNode *next; //puntero al proximo nodo
};

// estructura que contiene puntero a la lista de los vuelos que es la principal
struct airline
{
    flightNode *flightList;
};

// Funcion que nos permite adicionar vuelos y los guarda en el archivo "VUELOS.txt"
void addFlight(airline &airline, flight flights, int option)
{
    flightNode *newFlight = new flightNode; //creamos un nuevo nodo de vuelos
    strcpy(newFlight->flightNumber, flights.flightNumber); //copiamos el numero del vuelo
    strcpy(newFlight->origin, flights.origin); //copiamos la ciudad de origen
    strcpy(newFlight->arrival, flights.arrival); //copiamos la ciudad de destino
    strcpy(newFlight->planeId, flights.planeId); //copiamos la matricula del avion
    strcpy(newFlight->pilotName, flights.pilotName); //copianos el nombre del piloto
    strcpy(newFlight->fligthTime, flights.fligthTime); //copiamos la hora del vuelo
    strcpy(newFlight->fligthDate, flights.fligthDate); //copiamos la fecha del vuelo
    newFlight->status = flights.status; //copiamos el estado del vuelo
    newFlight->passengersList = NULL; //apuntamos a una lista de pasajeros vacia
    newFlight->next = NULL; //apuntamos al NULL
    if (airline.flightList == NULL) //si la lista de vuelos esta vacia
        airline.flightList = newFlight; //reemplazamos la lista por el nodo actual
    else //de lo contrario
    {
        flightNode *current = airline.flightList; //creamos un nodo de vuelos igual a la lista de vuelos
        while (current->next != NULL) //recorremos la lista de vuelos hasta el final
            current = current->next; //avanzamos al siguiente nodo
            
        current->next = newFlight; //apuntamos el ultimo nodo de los vuelos al nodo con el vuelo que queremos agregar
    }

    if (option == 0) //si option es igual a 0
    {
        // aqui vamos a guardar la lista en el archivo de texto
        FILE *file = fopen("VUELOS.txt", "a"); // abrimos el archivo "VUELOS.txt" en modo appened 
        if (file != NULL) //sino hubieron errores de apertura
        {
            fwrite(&flights, sizeof(flight), 1, file); //escribimos en el archivo el contenido de la estructura de vuelos
            fclose(file); // cerramos el archivo
        }
        else //de lo contrario
            printf("No se pudo abrir el archivo para escribir.\n"); //mensaje de error
    }
} // fin de la definicion de la funcion addFlight

// Funcion que nos permite agregar un pasajero a un vuelo y lo guarda en el archivo "PASAJEROS.txt"
void addPassenger(airline &airline, char flightNumber[7], passenger passengers, int status, int option)
{
    flightNode *current = airline.flightList; //variable auxiliar para recorrer la lista de vuelos
    while (current != NULL && strcmp(current->flightNumber, flightNumber) != 0) //mientras no sea el final de la lista y no coincidan los numeros de vuelo
        current = current->next; //avanzamos al siguiente nodo
        
    if (current != NULL && current->status == 0) // si se encuentra el vuelo y esta programado
    {
        passengerNode *newPassenger = new passengerNode; //creamos un nuevo nodo de pasajero
        strcpy(newPassenger->id, passengers.id); //copiamos la cedula del pasajero
        strcpy(newPassenger->name, passengers.name); //copiamos el nombre del pasajero
        strcpy(newPassenger->phone, passengers.phone); //copiamos el numero del pasajero
        newPassenger->status = status; // decimos que el pasajero esta en estado de reserva
        newPassenger->next = NULL; //apuntamos a NULL
        if (current->passengersList == NULL) //si la lista de pasajeros esta vacia
            current->passengersList = newPassenger; //reemplazamos la lista con el nodo actual
        else // de lo contrario
        {
            passengerNode *currentPassenger = current->passengersList; //creamos un nuevo nodo de pasajeros igual a nuestra lista de pasajeros
            while (currentPassenger->next != NULL) //recorremos la lista hasta el final
                currentPassenger = currentPassenger->next;//avanzamos al proximo nodo

            currentPassenger->next = newPassenger; //reemplazamos el ultimo nodo con el nodo actual con el nuevo pasajero
        }

        if (option == 0) //si option es igual a 0
        {
            // aqui guardamos la lista en un archivo
            FILE *file = fopen("PASAJEROS.txt", "a"); //abrimos el archivo "PASAJEROS.txt" en modo appened
            if (file != NULL) //sino hubieron errores de apertura
            {
                fwrite(flightNumber, 7, 1, file); //escribimos en el archivo el numero del vuelo
                fwrite(&passengers, sizeof(passenger), 1, file); //escribimos en el archivo el contenido de la estructura de pasajeros
                int status = 1; //creamos una variable para el estado del vuelo igual a 1
                fwrite(&status, 4, 1, file); //escribimos en el archivo el estado del vuelo
                fclose(file); //cerramos el archivo
            }
            else //de lo contrario
                printf("No se pudo abrir el archivo para escribir.\n"); //mensaje de error
        }
    }
    else //de lo contrario
        printf("No se encontró el vuelo con número %s o el vuelo ya fue realizado\n", flightNumber); //mensaje de error
}

// Funcion que nos permite ver los pasajeros de un vuelo
void passengerFligths(airline &airline, char flightNumber[7])
{
    flightNode *current = airline.flightList; //creamos un nodo de vuelos
    while (current != NULL && strcmp(current->flightNumber, flightNumber) != 0) //mientras no sea el final de la lista y no coincidan los numeros de vuelo
        current = current->next; //avanzamos al proximo nodo

    if (current != NULL) // preguntamos si se encuentra el vuelo
    {
        passengerNode *currentPassenger = current->passengersList; //creamos un nuevo nodo de pasajero
        printf("%c-------------------------------------------------------------%c\n",218,191); //estructura para la tabla
        printf("| %-10s | %-20s | %-10s | %-10s |\n","Cedula", "Nombre", "Telefono", "Estado"); //estructura para la tabla
        printf("%c-------------------------------------------------------------%c\n",195,180); //estructura para la tabla
        while (currentPassenger != NULL) //mientras no sea el final de la lista
        {
            printf("| %-11s| %-21s| %-11s|",currentPassenger->id, currentPassenger->name, currentPassenger->phone); //imprimimos los datos del pasajero
            if(currentPassenger->status==1) //si el estado del pasajero es 1
                printf(" %-10s |\n", "Reservado"); //imprimimos el estado de reservado
            else //de lo contrario
                printf(" %-10s |\n", "A bordo"); //imprimimos el estado de a bordo
            currentPassenger = currentPassenger->next; //avanzamos al proximo nodo de pasajero
        }
        printf("%c-------------------------------------------------------------%c\n",192,217); //estructura para la tabla
    }
    else //de lo contrario
        printf("No se encontró el vuelo con número %s\n", flightNumber); //mensaje de error

    return;
}

// Funcion que nos permite ver los vuelos programados
void schedulesFlights(airline &airline)
{
    flightNode *current = airline.flightList; //creamos un nodo de vuelo igual a la lista de vuelos
    printf("%c-------------------------------------%c\n",218,191); //estructura para la tabla
    printf("| %-10s | %-9s | %-10s |\n","nroVuelo", "Origen", "Destino"); //estructura para la tabla
    printf("%c-------------------------------------%c\n",195,180); //estructura para la tabla
    while (current != NULL) //mientras no sea el final de la lista
    {
        if (current->status == 0) //si el estado es 0
        {
            printf("| %-11s| %-10s| %-11s|\n",current->flightNumber, current->origin, current->arrival); //imprimios los datos del vuelo
        }
        current = current->next; //avanzamos con el proximo nodo
    }
    printf("%c-------------------------------------%c\n",192,217); //estructura para la tabla

    return;
}

//Funcion para imprimir los vuelos realizados
void finishedFlights(airline &airline)
{
    flightNode *current = airline.flightList;//puntero para accerder a la lista de vuelos
    printf("%c-------------------------------------%c\n",218,191); //estructura para la tabla
    printf("| %-10s | %-9s | %-10s |\n","nroVuelo", "Origen", "Destino"); //estructura para la tabla
    printf("%c-------------------------------------%c\n",195,180); //estructura para la tabla
    while (current != NULL)//ciclo para recorrer toda la lista
    {
        if (current->status == 1)//condicional para imprimir los vuelos realizados (status=1)
        {
            printf("| %-11s| %-10s| %-11s|\n",current->flightNumber, current->origin, current->arrival); //imprimimos la informacion del vuelo
        }
        current = current->next;//le asignamos al nodo actual el nodo siguiente
    }
    printf("%c-------------------------------------%c\n",192,217); //estructura para la tabla
    return;
}

//Funcion para imprimir los vuelos de una persona
void peopleFlights(airline &airline, char id[11])
{
    flightNode *fligth = airline.flightList;//puntero para acceder a la lista de vuelos
    printf("%c-----------------------------------------------------------------------------%c\n",218,191); //estructura para la tabla
    printf("| %-10s | %-9s | %-10s | %-9s | %-9s | %-13s |\n","nroVuelo", "Origen", "Destino","Fecha", "Hora", "Estado"); //estructura para la tabla
    printf("%c-----------------------------------------------------------------------------%c\n",195,180); //estructura para la tabla
    while (fligth != NULL)//ciclo para recorrer toda la lista de vuelos
    {
        passengerNode *passenger = fligth->passengersList;//puntero para acceder a la lista de los pasajeros
        while (passenger != NULL)//ciclo para recorrer toda la lista de pasajeros
        {
            if (strcmp(passenger->id, id) == 0)//verificamos si el pasajero existe
            {
                printf("| %-10s | %-9s | %-10s | %-9s | %-9s |",fligth->flightNumber, fligth->origin, fligth->arrival,fligth->fligthDate,fligth->fligthTime); //imprimimos la informacion del vuelo
                if (fligth->status == 0) //preguntamos si el estado es programado o realizado
                    printf(" %-13s |\n","Programado"); //imprimimos el estado Programado
                else
                    printf(" %-13s |\n","Realizado"); //imprimimos el estado Realizado
            }
            passenger = passenger->next;//le asignamos al nodo actual el nodo siguiente
        }
        fligth = fligth->next;//le asignamos al nodo actual el nodo siguiente
    }
     printf("%c-----------------------------------------------------------------------------%c\n",192,217); //estructura para la tabla
}

//Funcion para cambiar el estado de un vuelo
void changeFlightStatus(airline *airline, char flightNumber[7])
{
    flightNode *current = airline->flightList;//creamos un puntero para acceder a la lista de vuelos
    int flag=0;//bandera para indicar si el vuelo esta programado
    while (current != NULL) //ciclo para recorrer toda la lista
    {
        if (strcmp(current->flightNumber, flightNumber) == 0)//verificamos que el vuelo exista
        {
            if(current->status == 0) //si el estado es 0
            {
                current->status = 1;//cambiamos el estado del vuelo
                printf("El estado del vuelo %s ha sido modificado\n", flightNumber); //mensaje de notificacion
                flag=1;//cambiamos la bandera para indicar que el estado ha sido cambiado
            }
        }
        current = current->next;//al nodo actual le asignamos el siguiente nodo
    }

    if(flag==0)//verificamos si el vuelo existe
        printf("No se ha encontrado el vuelo %s\n o el vuelo no esta programado", flightNumber); //mensaje de notificacion
    else //de lo contrario
    {
        flight flights; //creamos un dato flights con la estructura fligth
        //iniciamos manejo de archivos para gurdar los datos modificados en el archivo
        FILE *file = fopen("VUELOS.txt","rb+");//abrimos el archivo
        int cont=0; //creamos un contador para los registros
        while(!feof(file))//ciclo para recorrer todo el archivo
        {
            fread(&flights,sizeof(flight),1,file); //leemos todo el registro de vuelo
            if(strcmp(flights.flightNumber,flightNumber) == 0) //verificamos si el numero de vuelo coincide
            {
                flights.status = 1;//cambiamos el estado en la memoria
                fseek(file,sizeof(flight) * cont,SEEK_SET); //nos movemos al inicio del registro
                fwrite(&flights,sizeof(flight),1,file); //escribimos el nuevo registro cambiado
                fclose(file);//cerramos el archivo
                return;
            }
            cont++; //agregamos uno al contador
        }
    }
    return;
}

//Funcion para cambiar el estado de un pasajero de 1 (reserva) a 2 (a bordo)
void changePassengerStatus(airline *airline, char id[11], char flightNumber[7])
{
    flightNode *fligth = airline->flightList; //puntero para acceder a la lista de vuelos
    int flag=0;//bandera que nos indica si se encontro el vuelo y que cambia al momento de que cambiamos el estado
    while (fligth != NULL)//ciclo para recorrer la lista de vuelos
    {
        if(strcmp(fligth->flightNumber,flightNumber)==0)//comprobamos si el vuelo existe
        {
            passengerNode *passenger = fligth->passengersList;//puntero para acceder a la lista de pasajeros
            while (passenger != NULL)//ciclo para recorrer la lista de pasajeros
            {
                if (strcmp(passenger->id, id) == 0) //comprobamos si el usuario se encuentra en el vuelo
                {
                    passenger->status=2;//cambiamos el estado del pasajero
                    flag=1;//cambiamos la bandera indicando que el estado ya esta programado
                }
                passenger = passenger->next;//al nodo passenger le asignamos el siguiente nodo
            }
        }
        fligth = fligth->next;//al nodo vuelo le asignamos el siguiente nodo
    }

    if(flag==0)//comprobamos si se encontró el vuelo 
        printf("No se ha encontrado el vuelo %s\n o el vuelo no esta programado", flightNumber); //mensaje de notificacion
    else
    {
        passenger passengers; //creamos un dato passengers con la estructura passenger
        //empezamos el manejo de archivos para guardar el cambio del estado de la lista en el archivo
        FILE *file1 = fopen("PASAJEROS.txt","rb+");//abrimos el archivo "PASAJEROS.txt"
        int cont=0 , status = 0;  //contador para los registros y status para el estado a leer
        char fligth[7] = ""; //variable para guardar el numero de vuelo
        while(!feof(file1))//ciclo para recorrer todo el archivo
        {
            while (!feof(file1))//ciclo para recorrer todo el archivo
            {
                fread(fligth, 7, 1, file1);//leemos el numero del vuelo
                fread(&passengers, sizeof(passenger),1,file1);//leemos los datos de los pasajeros
                fread(&status,4,1,file1); //leemos el estado del vuelo

                if(strcmp(flightNumber, fligth)==0 && strcmp(passengers.id, id) == 0) //verificamos si el numero de vuelo coincide y la cedula coincide
                {
                    status = 2;//cambiamos el estado en la memoria
                    fseek(file1,(11 + sizeof(passenger))*cont, SEEK_SET); //nos movemos al inicio del registro
                    fwrite(fligth,7,1,file1); //escribimos el numero del vuelo en el archivo
                    fwrite(&passengers, sizeof(passenger),1,file1); //escribimos el contenido de la estructura en el archivo
                    fwrite(&status,4,1,file1); //escribimos el estado en el archivo
                    fclose(file1);//cerramos el archivo
                    return;
                }
                cont++; //sumamos uno al contador
            }
        }
    }
    return;
}

//funcion para cargar los datos del archivo a la lista
void upload(airline &airline)
{
    FILE *file = fopen("VUELOS.txt", "rb"); //abrimos el archivo "VUELOS.txt" en modo lectura
    FILE *file1 = fopen("PASAJEROS.txt", "rb"); //abrimos el archivo "PASAJEROS.txt" en modo lectura
    flight flight; //creamos un nuevo dato fligth con la estructura flight
    if (file != NULL) //verificamos si no hay errores con la apertura del archivo
    {
        while (!feof(file)) //cilco para recorrer el archivo
        {
            if (fread(&flight, sizeof(flight), 1, file) == 1) //si se pudo leer el registro 
                addFlight(airline, flight, 1); //agregamos el registro a la lista de vuelos
        }
        fclose(file); //cerramos el archivo
    }
    else //de lo contrario
        printf("No se pudo abrir el archivo para escribir.\n");//mensaje de notificación
    if (file1 != NULL) //si el archivo no tuvo errores de apertura
    {
        char flightNumber[7] = ""; //creamos una variable para el numero de vuelo
        int status = 0; //creamos una variable para el estado 
        passenger passengers; //creamos un dato de tipo passenger
        while (!feof(file1)) //mientras no sea el final del archivo
        {
            fread(flightNumber, 7, 1, file1); //leemos el numero de vuelo
            if (fread(&passengers, sizeof(passenger), 1, file1) == 1) //si se pudo leer el registro
            {
                fread(&status, 4, 1, file1); //leemos el estado
                addPassenger(airline, flightNumber, passengers, status, 1); //agregamos el pasajero a la lista de pasajeros de su vuelo correspondiente
            }
        }
        fclose(file1); //cerramos el archivo
    }
    return;
}

//funcion para reiniciar las estructuras
void restartSructs(passenger &passangers, flight &flights)
{
    memset(passangers.id,0,sizeof(passangers.id)); //reiniciamos la cedula
    memset(passangers.name,0,sizeof(passangers.name)); //reiniciamos el nombre
    memset(passangers.phone,0,sizeof(passangers.phone)); //reiniciamos el telefono

    memset(flights.arrival,0,sizeof(flights.arrival)); //reiniciamos la ciudad de llegada
    memset(flights.flightNumber,0,sizeof(flights.flightNumber)); //reiniciamos el numero de vuelo
    memset(flights.fligthDate,0,sizeof(flights.fligthDate)); //reiniciamos la fecha del vuelo
    memset(flights.fligthTime,0,sizeof(flights.fligthTime)); //reiniciamos la hora del vuelo
    memset(flights.origin,0,sizeof(flights.origin)); //reiniciamos la ciudad de origen
    memset(flights.pilotName,0,sizeof(flights.pilotName)); //reiniciamos el nombre del piloto
    memset(flights.planeId,0,sizeof(flights.planeId)); //reiniciamos la matricula del avion
    flights.status=0; //reiniciamos el estado del vuelo

    return;
}