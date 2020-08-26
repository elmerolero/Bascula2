#include <gtk/gtk.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <regex>
#include <cstdlib>
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
        database.connect( "resources\\databases\\database.db" );
        
        // Carga la ventana principal y conecta la función para cerrar la ventana y finalizar el programa
        ventana = new Widget( "resources/interfaces/Principal.glade" );
        ventana -> establecerIconoVentana( "VentanaPrincipal", "resources\\images\\icons\\logo.png" );
        ventana -> conectarSenal( "VentanaPrincipal", "destroy", G_CALLBACK( gtk_main_quit ), nullptr );
        
        // Carga el widget de contenido
        contenido = new Widget();
        
        // Carga la vista de la báscula
        vistaControlBasculista( nullptr, this );
    }
    catch( runtime_error &excepcion ){
        cerr << excepcion.what() << endl;
        exit( 1 );
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
        string consulta = "select max( folio ) from tickets";
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
    for( Ticket *elemento : ticketsPendientes ){
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
        // Consulta para obtener los tickets pendientes
        string consulta = "select folio, numero_economico, numero_placa, clave_tipo, nombre_tipo, nombre_conductor, clave_procedencia, "
                          "nombre_procedencia, zona, subzona, departamentos.clave_departamento, departamentos.nombre_departamento, peso_bruto from tickets join procedencias "
                          "on tickets.codigo_empresa = procedencias.clave_procedencia join tipos_caja on tickets.tipo_caja = "
                          "tipos_caja.clave_tipo join departamentos on tickets.codigo_departamento = departamentos.clave_departamento where pendiente = 1";
        
        //Realiza la consulta
        database.query( consulta, databaseCallback );
        if( results > 0 ){
            // Para cada uno de los tickets
            for( Row * row : rows ){
                // Apuntador a ticket
                Ticket *ticket = new Ticket();

                // Establecemos sus características
                ticket -> establecerFolio( obtenerEntero( row -> campos.at( 0 ) ) );
                ticket -> establecerNumeroEconomico( row -> campos.at( 1 ) );
                ticket -> establecerNumeroPlacas( row -> campos.at( 2 ) );
                ticket -> establecerClaveTipoCaja( obtenerEntero( row -> campos.at( 3 ) ) );
                ticket -> establecerNombreTipoCaja( row -> campos.at( 4 ) );
                ticket -> establecerNombreConductor( row-> campos.at( 5 ) );
                ticket -> establecerClaveProcedencia( obtenerEntero( row -> campos.at( 6 ) ) );
                ticket -> establecerNombreProcedencia( row -> campos.at( 7 ) );
                ticket -> establecerZona( row -> campos.at( 8 ) );
                ticket -> establecerSubzona( row -> campos.at( 9 ) );
                ticket -> establecerClaveDepartamento( obtenerEntero( row -> campos.at( 10 ) ) );
                ticket -> establecerNombreDepartamento( row -> campos.at( 11 ) );
                ticket -> establecerPesoBruto( stod( row -> campos.at( 12 ) ) );
                ticket -> establecerPendiente( true );
                
                // Lo agregamos a tickets pendientes
                ticketsPendientes.push_back( ticket );
            }
        }
    }
    catch( runtime_error &re ){
        // Nada
    }
}

const vector< Ticket* >& Aplicacion::obtenerTicketsPendientes() const
{
    return ticketsPendientes;
}

void Aplicacion::actualizarRegistrosProcedencias()
{
    // Limpia los registros de las procedencias
    limpiarRegistrosProcedencias();

    try{
        // Obtiene los registros de las procedencias
        string consulta = "select clave_procedencia, nombre_procedencia from procedencias;";
        database.query( consulta, databaseCallback );
        if( results > 0 ){
            // Obtiene el registro de los resultados
            for( Row *row : rows ){
                // Crea un nuevo registro
                Registro *registro = new Registro;

                // Establece los datos del nuevo registro
                registro -> clave = obtenerEntero( row -> campos.at( 0 ) );
                registro -> nombre = row -> campos.at( 1 );

                // Lo añade al arreglo de registros
                if( registro -> clave != 0 ){
                    registrosProcedencias.push_back( registro );
                }
            }
        } 
    }
    catch( runtime_error &e ){
        cerr << e.what() << endl;
    }
}

const vector< Registro * > &Aplicacion::obtenerRegistrosProcedencias() const
{
    return registrosProcedencias;
}

void Aplicacion::limpiarRegistrosProcedencias()
{
    limpiarRegistros( registrosProcedencias );
}

void Aplicacion::actualizarRegistrosDepartamentos()
{
    // Limpia los registros de las procedencias
    limpiarRegistrosProcedencias();

    try{
        // Obtiene los registros de las procedencias
        string consulta = "select clave_departamento, nombre_departamento from departamentos;";
        database.query( consulta, databaseCallback );
        if( results > 0 ){
            // Obtiene el registro de los resultados
            for( Row *row : rows ){
                // Crea un nuevo registro
                Registro *registro = new Registro;

                // Establece los datos del nuevo registro
                registro -> clave = obtenerEntero( row -> campos.at( 0 ) );
                registro -> nombre = row -> campos.at( 1 );

                // Lo añade al arreglo de registros
                if( registro -> clave != 0 ){
                    registrosDepartamentos.push_back( registro );
                }else{
                    delete registro;
                }
            }
        } 
    }
    catch( runtime_error &e ){
        cerr << e.what() << endl;
    }
}

const vector< Registro * > &Aplicacion::obtenerRegistrosDepartamentos() const
{
    return registrosDepartamentos;
}

void Aplicacion::limpiarRegistrosDepartamentos()
{
    limpiarRegistros( registrosDepartamentos );
}

void Aplicacion::actualizarRegistrosTiposCaja()
{
    // Limpia los registros de las procedencias
    limpiarRegistrosTiposCaja();

    try{
        // Obtiene los registros de las procedencias
        string consulta = "select clave_tipo, nombre_tipo from tipos_caja;";
        database.query( consulta, databaseCallback );
        if( results > 0 ){
            // Obtiene el registro de los resultados
            for( Row *row : rows ){
                // Crea un nuevo registro
                Registro *registro = new Registro;

                // Establece los datos del nuevo registro
                registro -> clave = obtenerEntero( row -> campos.at( 0 ) );
                registro -> nombre = row -> campos.at( 1 );

                // Lo añade al arreglo de registros
                if( registro -> clave != 0 ){
                    registrosTiposCaja.push_back( registro );
                }else{
                    delete registro;
                }
            }
        } 
    }
    catch( runtime_error &e ){
        cerr << e.what() << endl;
    }
}

const vector< Registro * > &Aplicacion::obtenerRegistrosTiposCaja() const
{
    return registrosTiposCaja;
}

void Aplicacion::limpiarRegistrosTiposCaja()
{
    limpiarRegistros( registrosTiposCaja );
}

void Aplicacion::limpiarRegistros( vector< Registro * > &registros )
{
    // Para cada elemento del vector
    for( Registro *elemento : registros ){
        // Elimina el elemento
        delete elemento;
    }
    
    // Limpia el vector
    registros.clear();
}
