#include <gtk/gtk.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <regex>
#include "Utilidades.h"
#include "Vistas.h"
#include "Aplicacion.h"
#include "Widget.h"
#include "Funciones.h"
using namespace std;

Aplicacion::Aplicacion():
    ventana( nullptr )
{
    // Nada por hacer
}

int Aplicacion::iniciar()
{
    try{
        // Conecta con la base de datos
        database.connect( "../resources/databases/database.db" );
        
        // Carga la ventana principal y conecta la función para cerrar la ventana y finalizar el programa
        ventana = new Widget( "../resources/interfaces/Principal.glade" );
        ventana -> conectarSenal( "VentanaPrincipal", "destroy", G_CALLBACK( gtk_main_quit ), nullptr );
        
        // Carga el widget de contenido
        contenido = new Widget();
        
        // Carga la vista de la báscula
        vistaControlBasculista( nullptr, this );
    }
    catch( runtime_error &excepcion ){
        cerr << excepcion.what() << endl;
        return 1;
    }

    return 0;
}

Widget* Aplicacion::obtenerWidget() const
{
	return ventana;
}

void Aplicacion::establecerVistaContenido( std::string archivo )
{
    // Si hay un elemento llamado contenido
    if( contenido -> obtenerBuilder() != nullptr ){
        // Lo remueve
        ventana -> eliminarElemento( contenido, "Contenido", "GridPrincipal" );
    }
    
    // Carga la interfaz de registro
    contenido -> cargarWidget( archivo );
    
    // Lo inserta en el grid
    ventana -> insertarElementoAGrid( contenido, "Contenido", "GridPrincipal", 0, 2, 1, 1 );
}

Widget *Aplicacion::obtenerVistaContenido() const
{
    return contenido;
}

void Aplicacion::establecerFecha( std::string fecha )
{
    this -> fecha = fecha;
}

std::string Aplicacion::obtenerFecha() const
{
    return fecha;
}

void Aplicacion::establecerFolioTicketActual()
{
    try{
        string consulta = "select max( folio ) from tickets"   ;
        database.query( consulta, databaseCallback );
        if( results > 0 ){
            int folio = obtenerEntero( rows.at( 0 ) -> campos[ 0 ] );
            if( folio > 0 ){
                ticket.establecerFolio( folio + 1 );
            }
            else{
                ticket.establecerFolio( 1 );
            }
        }
        else{
            ticket.establecerFolio( 1 );
        }
    }
    catch( runtime_error &e ){
        cerr << e.what() << endl;
    }
}

Ticket *Aplicacion::obtenerTicket()
{
    return &ticket;
}

void Aplicacion::limpiarTicketsPendientes()
{
    // Para cada elemento del vector
    for( TicketPendiente *elemento : ticketsPendientes ){
        // Elimina el elemento
        delete elemento;
    }
    
    // Limpia el vector
    ticketsPendientes.clear(); 
}

void Aplicacion::actualizarTicketsPendientes()
{
    // Limpia los tickets pendientes
    limpiarTicketsPendientes();
    
    // Intenta
    try{
        string consulta = "select folio, numero_economico , peso_bruto from tickets where pendiente = 1";
        database.query( consulta, databaseCallback );
        if( results > 0 ){
            // Para cada uno de los renglones
            for( Row *row : rows ){
                // Crea el ticket
                TicketPendiente *pendiente = new TicketPendiente();
                
                // Establece su contenido
                pendiente -> folio = obtenerEntero( row -> campos[ 0 ] );
                pendiente -> numeroEconomico = row -> campos[ 1 ];
                pendiente -> pesoBruto = stod( row -> campos[ 2 ] );
                
                // Lo añade en los tickets pendientes
                ticketsPendientes.push_back( pendiente );
            }
        }
    }
    catch( runtime_error &re ){
        // Nada
    }
}

const vector< TicketPendiente * >& Aplicacion::obtenerTicketsPendientes() const
{
    return ticketsPendientes;
}
