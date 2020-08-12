#include "Vistas.h"
#include "Aplicacion.h"
#include "Funciones.h"
#include "Utilidades.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

void vistaControlBasculista( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/ControlBasculista.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Conecta las señales
    contenido -> conectarSenal( "BotonBascula", "clicked", G_CALLBACK( vistaBascula ), aplicacion );
}

void vistaBascula( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/Bascula.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    contenido -> removerElementosHijos( "ContenedorTickets" );
    
    // Obtenemos la referencia a los tickets
    aplicacion -> actualizarTicketsPendientes();
    const vector< TicketPendiente * >ticketsPendientes = aplicacion -> obtenerTicketsPendientes();
    Widget *objeto = new Widget();
    for( TicketPendiente *elemento : ticketsPendientes ){
        stringstream folio;
        folio << setfill( '0' ) << setw( 6 ) << elemento -> folio;
        
        // Agrega los elementos
        try{
            objeto -> cargarWidget( "../resources/interfaces/ElementoTicket.glade" );
            objeto -> establecerTextoEtiqueta( "ItemEntradaNumeroEconomico", elemento -> numeroEconomico );
            objeto -> establecerTextoEtiqueta( "ItemEntradaFolio", folio.str() );
            
            contenido -> insertarElementoAGrid( objeto, "Ticket", "ContenedorTickets", 0, (elemento -> folio - 1), 1, 1 );
        }
        catch( runtime_error &e ){
            cout << e.what() << endl;
            break;
        }
        
        folio.str( "" );
    }
    
    // Conecta las señales y los eventos
    contenido -> conectarSenal( "BotonRegresar", "clicked", G_CALLBACK( vistaControlBasculista ), aplicacion );
    contenido -> conectarSenal( "BotonNuevoTicket", "clicked", G_CALLBACK( vistaNuevoTicket ), aplicacion );
    contenido -> conectarSenal( "BotonCierre", "clicked", G_CALLBACK( vistaCierreDia ), aplicacion );
    contenido -> conectarSenal( "BotonSeguimiento", "clicked", G_CALLBACK( vistaSeguimientoTicketPendienteEntrada ), aplicacion );
    contenido -> conectarSenal( "EntradaNumeroEconomico", "activate", G_CALLBACK( vistaSeguimientoTicketPendienteEntrada ), aplicacion );
    contenido -> conectarSenal( "EntradaNumeroEconomico", "insert-text", G_CALLBACK( insert_text_handler ), nullptr );
}

void vistaNuevoTicket( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/RegistroTicket/NumeroEconomico.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Actualiza el folio del ticket a crear
    aplicacion -> establecerFolioTicketActual();
    
    // Establece el folio en la vista
    Ticket *ticket = aplicacion -> obtenerTicket();
    contenido -> establecerTextoEtiqueta( "EntradaFolio", to_string( ticket -> obtenerFolio() ) );
    
    // Configura las señales
    contenido -> conectarSenal( "EntradaNumeroEconomico", "activate", G_CALLBACK( registrarNumeroEconomico ), aplicacion );
    contenido -> conectarSenal( "EntradaNumeroEconomico", "insert-text", G_CALLBACK( insert_text_handler ), nullptr );
    contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarNumeroEconomico ), aplicacion );
}

void vistaRegistrarPlacas( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/RegistroTicket/Placas.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Establece el folio en la vista
    Ticket *ticket = aplicacion -> obtenerTicket();
    contenido -> establecerTextoEtiqueta( "EntradaFolio", to_string( ticket -> obtenerFolio() ) );
    
    // Configura las señales
    contenido -> conectarSenal( "EntradaNumeroPlacas", "activate", G_CALLBACK( registrarNumeroPlacas ), aplicacion );
    contenido -> conectarSenal( "EntradaNumeroPlacas", "insert-text", G_CALLBACK( insert_text_handler ), nullptr );
    contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarNumeroPlacas ), aplicacion );
}

void vistaRegistrarTipoCaja( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/RegistroTicket/TipoCaja.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Establece el folio en la vista
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Establece el folio del ticket seleccionado
    stringstream folio;
    folio << setfill( '0' ) << setw( 6 ) << ticket -> obtenerFolio();
    contenido -> establecerTextoEtiqueta( "EntradaFolio", folio.str() );
    
    // Configura las señales
    contenido -> conectarSenal( "EntradaTipoCaja", "activate", G_CALLBACK( registrarTipoCaja ), aplicacion );
    contenido -> conectarSenal( "EntradaTipoCaja", "insert-text", G_CALLBACK( insert_text_handler ), nullptr );
    contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarTipoCaja ), aplicacion );
}

void vistaRegistrarConductor( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/RegistroTicket/NombreConductor.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Establece el folio en la vista
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Establece el folio del ticket seleccionado
    stringstream folio;
    folio << setfill( '0' ) << setw( 6 ) << ticket -> obtenerFolio();
    contenido -> establecerTextoEtiqueta( "EntradaFolio", folio.str() );
    
    // Configura las señales
    contenido -> conectarSenal( "EntradaNombreConductor", "activate", G_CALLBACK( registrarNombreConductor ), aplicacion );
    contenido -> conectarSenal( "EntradaNombreConductor", "insert-text", G_CALLBACK( insert_text_handler ), nullptr );
    contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarNombreConductor ), aplicacion );
}

void vistaRegistrarProcedencia( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/RegistroTicket/Procedencia.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Establece el folio en la vista
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Establece el folio del ticket seleccionado
    stringstream folio;
    folio << setfill( '0' ) << setw( 6 ) << ticket -> obtenerFolio();
    contenido -> establecerTextoEtiqueta( "EntradaFolio", folio.str() );
    
    // Configura las señales
    contenido -> conectarSenal( "EntradaProcedencia", "activate", G_CALLBACK( registrarProcedencia ), aplicacion );
    contenido -> conectarSenal( "EntradaProcedencia", "insert-text", G_CALLBACK( insert_text_handler ), nullptr );
    contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarProcedencia ), aplicacion );
}

void vistaRegistrarZona( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/RegistroTicket/Zona.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Establece el folio en la vista
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Establece el folio del ticket seleccionado
    stringstream folio;
    folio << setfill( '0' ) << setw( 6 ) << ticket -> obtenerFolio();
    contenido -> establecerTextoEtiqueta( "EntradaFolio", folio.str() );
    
    // Configura las señales
    contenido -> conectarSenal( "EntradaZona", "activate", G_CALLBACK( registrarZona ), aplicacion );
    contenido -> conectarSenal( "EntradaZona", "insert-text", G_CALLBACK( insert_text_handler ), nullptr );
    contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarZona ), aplicacion );
}

void vistaRegistrarSubzona( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/RegistroTicket/Subzona.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Establece el folio en la vista
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Establece el folio del ticket seleccionado
    stringstream folio;
    folio << setfill( '0' ) << setw( 6 ) << ticket -> obtenerFolio();
    contenido -> establecerTextoEtiqueta( "EntradaFolio", folio.str() );
    
    // Configura las señales
    contenido -> conectarSenal( "EntradaSubzona", "activate", G_CALLBACK( registrarSubzona ), aplicacion );
    contenido -> conectarSenal( "EntradaSubzona", "insert-text", G_CALLBACK( insert_text_handler ), nullptr );
    contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarSubzona ), aplicacion );
}

void vistaLectorBasculaEntrada( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/RegistroTicket/LectorBascula.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Establece el folio en la vista
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // S
    stringstream folio;
    folio << setfill( '0' ) << setw( 6 ) << ticket -> obtenerFolio();
    contenido -> establecerTextoEtiqueta( "EntradaFolio", folio.str() );
    
    // Configura las señales
    contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarPesoBruto ), aplicacion );
}

void vistaRegistrarClaveDepartamento( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "../resources/interfaces/RegistroTicket/ClaveDepartamento.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Establece el folio en la vista
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Establece el folio del ticket seleccionado
    stringstream folio;
    folio << setfill( '0' ) << setw( 6 ) << ticket -> obtenerFolio();
    contenido -> establecerTextoEtiqueta( "EntradaFolio", folio.str() );
    
    // Obtiene el departamento predefinido y completa el formulario automáticamente con ese departamento
    try{
        string consulta = "select clave_departamento from procedencias where clave_procedencia = " + to_string( ticket -> obtenerClaveProcedencia() ) + " and clave_departamento not null limit 1;";
        database.query( consulta, databaseCallback );
        
        // Obtiene la clave_departamento
        if( results > 0 ){
            string claveDepartamento = rows.at( 0 ) -> campos[ 0 ];
            contenido -> establecerTextoEntrada( "EntradaClaveDepartamento", claveDepartamento );
        } 
        
    }
    catch( runtime_error &e ){
        // No hace nada, no hubo resultados
    }
    
    // Configura las señales
    contenido -> conectarSenal( "EntradaClaveDepartamento", "activate", G_CALLBACK( registrarClaveDepartamento ), aplicacion );
    contenido -> conectarSenal( "EntradaClaveDepartamento", "insert-text", G_CALLBACK( insert_text_handler ), nullptr );
    contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarClaveDepartamento ), aplicacion );
}

void vistaSeguimientoTicketPendienteEntrada( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el
    string nCamion = contenido -> obtenerTextoEntrada( "EntradaNumeroEconomico" );
    if( nCamion.empty() ){
        Widget *widget = new Widget( "../resources/interfaces/RegistroExitoso.glade" );
        widget -> establecerTextoEtiqueta( "Mensaje", "Introduzca un numero\neconomico." );
        widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );
        return;
    }
    
    // Obtiene los ticket pendientes
    TicketPendiente *pendiente = nullptr;
    const vector< TicketPendiente * >ticketsPendientes = aplicacion -> obtenerTicketsPendientes();
    for( TicketPendiente *ticket : ticketsPendientes ){
        // ¿El numero de camion coincide con el ticket?
        if( nCamion.compare( ticket -> numeroEconomico ) == 0 ){
            pendiente = ticket;
            break;
        }
    }
    
    if( pendiente != nullptr ){
        // Establece la vista del lector báscula
        aplicacion -> establecerVistaContenido( "../resources/interfaces/RegistroTicket/LectorBascula.glade" );
        
        // Establece los datos del ticket que va a actualizar
        Ticket *ticket = aplicacion -> obtenerTicket();
        ticket -> establecerNumeroEconomico( pendiente -> numeroEconomico );
        ticket -> establecerFolio( pendiente -> folio );
        ticket -> establecerPesoBruto( pendiente -> pesoBruto );
                
        // Establece el folio del ticket seleccionado
        stringstream folio;
        folio << setfill( '0' ) << setw( 6 ) << ticket -> obtenerFolio();
        contenido -> establecerTextoEtiqueta( "EntradaFolio", folio.str() );
        
        // Conecta las señales
        contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarPesoTara ), aplicacion );
    }
    else{
        Widget *widget = new Widget( "../resources/interfaces/RegistroExitoso.glade" );
        widget -> establecerTextoEtiqueta( "Mensaje", "El ticket con el código indicado\nno fue encontrado." );
        widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );
    }
}

void vistaCierreDia( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene los ticket pendientes
    TicketPendiente *pendiente = nullptr;
    const vector< TicketPendiente * >ticketsPendientes = aplicacion -> obtenerTicketsPendientes();
    // Si hay tickets pendiente
    if( !ticketsPendientes.empty() ){
        Widget *widget = new Widget( "../resources/interfaces/RegistroExitoso.glade" );
        widget -> establecerTextoEtiqueta( "Mensaje", "No se puede continuar con\nel cierre si hay tickets pendientes." );
        widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );
        return;
    }
    
    try{
        // Obtiene los totales del dia actual
        string consulta = "select count( folio ), sum( peso_neto ) from tickets where fecha = date(\'now\', \'localtime\' );";
        database.query( consulta, databaseCallback );
        if( results > 0 ){
            string totalTickets = rows.at( 0 ) -> campos[ 0 ];
            string totalKilogramos = rows.at( 0 ) -> campos[ 1 ];
            
            if( totalKilogramos.empty() ){
                // Crea el reporte 
                consulta = "insert into reportes values( null, date( \'now\', \'localtime\' ), time( \'now\', \'localtime\' ), " + 
                        ( totalKilogramos.empty() ? "null" : totalKilogramos ) + ", " + ( totalTickets.empty() ? "null" : totalTickets ) + " );";
                cout << consulta << endl;
                database.query( consulta, NULL );
                
                // Obtiene el reporte generado
                consulta = "select folio from reportes where fecha = date( 'now', 'localtime' );";
                cout << consulta << endl;
                database.query( consulta, databaseCallback );
                if( results > 0 ){
                    // Obtiene el folio
                    string folio = rows.at( 0 ) -> campos.at( 0 );
                
                    // Obtiene los tickets realizados en la fecha realizada
                    for( unsigned int i = 1; i < 6; ++i ){
                        consulta = "select count( folio ), sum( peso_neto ) from tickets where fecha = date( 'now', 'localtime' ) and codigo_empresa = " + to_string( i ) + ";";
                        database.query( consulta, databaseCallback );
                        if( results > 0 ){
                            vector< Row >filas;
                            // Para cada uno de los resultados
                            for( unsigned int i = 0; i < rows.size(); ++i ){
                                Row fila;
                    
                                for( unsigned int j = 0; j < rows.at( i ) -> campos.size(); ++j ){
                                    fila.campos.push_back( rows.at( i ) -> campos.empty() ? "0" :  rows.at( i ) -> campos.at( j ) );
                                }
                    
                                filas.push_back( fila );
                            }
                    
                            for( unsigned int i = 0; i < filas.size(); ++i ){
                                consulta = "insert into reportes values( " + folio + ", " + to_string( i ) + ", " + filas.at( i ).campos.at( 1 ) + ", " + filas.at( i ).campos.at( 0 ) + " );";
                    
                                cout << consulta << endl;
                            }
                        }
                    }
                }
            }
            else{
                Widget *widget = new Widget( "../resources/interfaces/RegistroExitoso.glade" );
                widget -> establecerTextoEtiqueta( "Mensaje", "No se puede continuar, \nno hay tickets registrados." );
                widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );
                return;
            }
        }
        else{
            cout << "No se ha registrado ningún ticket el día de hoy." << endl;
        }
    }
    catch( runtime_error &e ){
        cerr << e.what() << endl;
    }
}
