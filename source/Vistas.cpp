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
    aplicacion -> establecerVistaContenido( "resources\\interfaces\\ControlBasculista.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Conecta las señales
    contenido -> conectarSenal( "BotonRegistros", "clicked", G_CALLBACK( vistaRegistros ), aplicacion );
    contenido -> conectarSenal( "BotonBascula", "clicked", G_CALLBACK( vistaBascula ), aplicacion );
}

void vistaRegistros( GtkWidget *widget, gpointer ptr )
{
    // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de inicio de sesion
    aplicacion -> establecerVistaContenido( "resources/interfaces/Registros.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();

    // Conecta las señales
    contenido -> conectarSenal( "BotonEnlaceRegresar", "activate-link", G_CALLBACK( vistaControlBasculista ), aplicacion );
    contenido -> conectarSenal( "BotonProcedencias", "clicked", G_CALLBACK( vistaConsultarProcedencias ), aplicacion );
    contenido -> conectarSenal( "BotonDepartamentos", "clicked", G_CALLBACK( vistaConsultarDepartamentos ), aplicacion );
    contenido -> conectarSenal( "BotonTiposCaja", "clicked", G_CALLBACK( vistaConsultarTiposCaja ), aplicacion );
}

void vistaConsultarProcedencias( GtkWidget *widget, gpointer ptr )
{
        // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de los registros
    aplicacion -> establecerVistaContenido( "resources/interfaces/ContenedorRegistros.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();

    // Establece el titulo de la etiqueta
    contenido -> establecerTextoEtiqueta( "TituloRegistro", "Procedencias" );

    // Conecta las señales
    contenido -> conectarSenal( "BotonEnlaceRegresar", "activate-link", G_CALLBACK( vistaRegistros ), aplicacion );

    // Remueve los elementos del contenedor
    contenido -> removerElementosHijos( "ContenedorRegistros" );

    // Obtiene las procedencias registradas
    aplicacion -> actualizarRegistrosProcedencias();
    const vector< Registro * > registrosProcedencias = aplicacion -> obtenerRegistrosProcedencias();
    for( Registro *registro : registrosProcedencias ){
        Widget *elemento = new Widget();
        stringstream clave;
        clave << setfill( '0' ) << setw( 6 ) << registro -> clave;
        try{
            elemento -> cargarWidget( "resources/interfaces/ElementoProcedencias.glade" );
            elemento -> establecerTextoEtiqueta( "ItemEntradaNombre", registro -> nombre );
            elemento -> establecerTextoEtiqueta( "ItemEntradaClave", clave.str() );
            contenido -> insertarElementoAGrid( elemento, "ItemProcedencia", "ContenedorRegistros", 0, (registro -> clave - 1), 1, 1 );
        }
        catch( runtime_error &e ){
            cout << e.what() << endl;
            break;
        }
        delete elemento;    
    }
}

void vistaConsultarDepartamentos( GtkWidget *widget, gpointer ptr )
{
        // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de los registros
    aplicacion -> establecerVistaContenido( "resources/interfaces/ContenedorRegistros.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();

    // Establece el titulo de la etiqueta
    contenido -> establecerTextoEtiqueta( "TituloRegistro", "Departamentos" );

    // Conecta las señales
    contenido -> conectarSenal( "BotonEnlaceRegresar", "activate-link", G_CALLBACK( vistaRegistros ), aplicacion );

    // Remueve los elementos del contenedor
    contenido -> removerElementosHijos( "ContenedorRegistros" );

    // Obtiene las procedencias registradas
    aplicacion -> actualizarRegistrosDepartamentos();
    const vector< Registro * > registrosDepartamentos = aplicacion -> obtenerRegistrosDepartamentos();
    for( Registro *registro : registrosDepartamentos ){
        Widget *elemento = new Widget();
        stringstream clave;
        clave << setfill( '0' ) << setw( 6 ) << registro -> clave;
        try{
            elemento -> cargarWidget( "resources/interfaces/ElementoDepartamentos.glade" );
            elemento -> establecerTextoEtiqueta( "ItemEntradaNombre", registro -> nombre );
            elemento -> establecerTextoEtiqueta( "ItemEntradaClave", clave.str() );
            contenido -> insertarElementoAGrid( elemento, "ItemProcedencia", "ContenedorRegistros", 0, (registro -> clave - 1), 1, 1 );
        }
        catch( runtime_error &e ){
            cout << e.what() << endl;
            break;
        }
        delete elemento;    
    }
}

void vistaConsultarTiposCaja( GtkWidget *widget, gpointer ptr )
{
        // Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Establece la vista de los registros
    aplicacion -> establecerVistaContenido( "resources/interfaces/ContenedorRegistros.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();

    // Establece el titulo de la etiqueta
    contenido -> establecerTextoEtiqueta( "TituloRegistro", "Tipos de caja" );

    // Conecta las señales
    contenido -> conectarSenal( "BotonEnlaceRegresar", "activate-link", G_CALLBACK( vistaRegistros ), aplicacion );

    // Remueve los elementos del contenedor
    contenido -> removerElementosHijos( "ContenedorRegistros" );

    // Obtiene las procedencias registradas
    aplicacion -> actualizarRegistrosTiposCaja();
    const vector< Registro * > registrosDepartamentos = aplicacion -> obtenerRegistrosTiposCaja();
    for( Registro *registro : registrosDepartamentos ){
        Widget *elemento = new Widget();
        stringstream clave;
        clave << setfill( '0' ) << setw( 6 ) << registro -> clave;
        try{
            elemento -> cargarWidget( "resources/interfaces/ElementosTiposCaja.glade" );
            elemento -> establecerTextoEtiqueta( "ItemEntradaNombre", registro -> nombre );
            elemento -> establecerTextoEtiqueta( "ItemEntradaClave", clave.str() );
            contenido -> insertarElementoAGrid( elemento, "ItemProcedencia", "ContenedorRegistros", 0, (registro -> clave - 1), 1, 1 );
        }
        catch( runtime_error &e ){
            cout << e.what() << endl;
            break;
        }
        delete elemento;    
    }
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
    aplicacion -> establecerVistaContenido( "resources/interfaces/Bascula.glade" );
    
    // Obtiene la vista contenido
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Remueve los elementos del contenedor
    contenido -> removerElementosHijos( "ContenedorTickets" );
    
    // Obtenemos la referencia a los tickets
    aplicacion -> actualizarTicketsPendientes();
    const vector< Ticket * >ticketsPendientes = aplicacion -> obtenerTicketsPendientes();
    Widget *objeto = new Widget();
    for( Ticket *ticket : ticketsPendientes ){
        stringstream folio;
        folio << setfill( '0' ) << setw( 6 ) << ticket -> obtenerFolio();

        // Agrega los elementos
        try{
            objeto -> cargarWidget( "resources/interfaces/ElementoTicket.glade" );
            objeto -> establecerTextoEtiqueta( "ItemEntradaNumeroEconomico", ticket -> obtenerNumeroEconomico() );
            objeto -> establecerTextoEtiqueta( "ItemEntradaFolio", folio.str() );
            objeto -> establecerTextoEtiqueta( "ItemEntradaNumeroPlaca", ticket -> obtenerNumeroPlacas() );
            
            contenido -> insertarElementoAGrid( objeto, "Ticket", "ContenedorTickets", 0, (ticket -> obtenerFolio() - 1), 1, 1 );
        }
        catch( runtime_error &e ){
            cout << e.what() << endl;
            break;
        }
        
        folio.str( "" );
    }
    
    // Conecta las señales y los eventos
    contenido -> conectarSenal( "BotonRegresar", "clicked", G_CALLBACK( vistaControlBasculista ), aplicacion );
    
    contenido -> conectarSenal( "BotonCierre", "clicked", G_CALLBACK( vistaCierreDia ), aplicacion );
    contenido -> conectarSenal( "BotonSeguimiento", "clicked", G_CALLBACK( vistaSeguimientoTicketPendienteEntrada ), aplicacion );
    contenido -> conectarSenal( "EntradaNumeroEconomico", "activate", G_CALLBACK( vistaSeguimientoTicketPendienteEntrada ), aplicacion );
    contenido -> conectarSenal( "EntradaNumeroEconomico", "insert-text", G_CALLBACK( insert_text_handler ), nullptr );
    contenido -> conectarSenal( "BotonNuevoTicket", "clicked", G_CALLBACK( vistaNuevoTicket ), aplicacion );
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
    aplicacion -> establecerVistaContenido( "resources/interfaces/RegistroTicket/NumeroEconomico.glade" );
    
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
    aplicacion -> establecerVistaContenido( "resources/interfaces/RegistroTicket/Placas.glade" );
    
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
    aplicacion -> establecerVistaContenido( "resources/interfaces/RegistroTicket/TipoCaja.glade" );
    
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
    aplicacion -> establecerVistaContenido( "resources/interfaces/RegistroTicket/NombreConductor.glade" );
    
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
    aplicacion -> establecerVistaContenido( "resources/interfaces/RegistroTicket/Procedencia.glade" );
    
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
    aplicacion -> establecerVistaContenido( "resources/interfaces/RegistroTicket/Zona.glade" );
    
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
    aplicacion -> establecerVistaContenido( "resources/interfaces/RegistroTicket/Subzona.glade" );
    
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
    aplicacion -> establecerVistaContenido( "resources/interfaces/RegistroTicket/LectorBascula.glade" );
    
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
    aplicacion -> establecerVistaContenido( "resources/interfaces/RegistroTicket/ClaveDepartamento.glade" );
    
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
    string numeroPlaca = contenido -> obtenerTextoEntrada( "EntradaNumeroEconomico" );
    if( numeroPlaca.empty() ){
        Widget *widget = new Widget( "resources/interfaces/RegistroExitoso.glade" );
        widget -> establecerTextoEtiqueta( "Mensaje", "Introduzca un numero\neconomico." );
        widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), nullptr );
        return;
    }
    
    // Obtiene los ticket pendientes
    const vector< Ticket* >ticketsPendientes = aplicacion -> obtenerTicketsPendientes();
    for( Ticket *elemento : ticketsPendientes ){
        // ¿El numero de camion coincide con el ticket?
        if( numeroPlaca.compare( elemento -> obtenerNumeroPlacas() ) == 0 ){
            // Establece los datos de ese ticketTicket
            Ticket *ticket = aplicacion -> obtenerTicket();

            // Establece los datos del ticket
            ticket -> establecerFolio( elemento -> obtenerFolio() );
            ticket -> establecerNumeroEconomico( elemento -> obtenerNumeroEconomico() );
            ticket -> establecerNumeroPlacas( elemento -> obtenerNumeroPlacas() );
            ticket -> establecerClaveTipoCaja( elemento -> obtenerClaveTipoCaja() );
            ticket -> establecerNombreTipoCaja( elemento -> obtenerNombreTipoCaja() );
            ticket -> establecerNombreConductor( elemento -> obtenerNombreConductor() );
            ticket -> establecerClaveProcedencia( elemento -> obtenerClaveProcedencia() );
            ticket -> establecerNombreProcedencia( elemento -> obtenerNombreProcedencia() );
            ticket -> establecerZona( elemento -> obtenerZona() );
            ticket -> establecerSubzona( elemento -> obtenerSubzona() );
            ticket -> establecerClaveDepartamento( elemento -> obtenerClaveDepartamento() );
            ticket -> establecerNombreDepartamento( elemento -> obtenerNombreDepartamento() );
            ticket -> establecerPesoBruto( elemento -> obtenerPesoBruto() );
            ticket -> establecerPendiente( true );

            // Establece la vista del lector báscula
            aplicacion -> establecerVistaContenido( "resources/interfaces/RegistroTicket/LectorBascula.glade" );
            
            // Establece el folio del ticket seleccionado
            stringstream folio;
            folio << setfill( '0' ) << setw( 6 ) << ticket -> obtenerFolio();
            contenido -> establecerTextoEtiqueta( "EntradaFolio", folio.str() );
        
            // Conecta las señales
            contenido -> conectarSenal( "BotonSiguiente", "clicked", G_CALLBACK( registrarPesoTara ), aplicacion );
            return;
        }
    }
        
    Widget *alerta = new Widget( "resources/interfaces/RegistroExitoso.glade" );
    alerta -> establecerTextoEtiqueta( "Mensaje", "El ticket con el código indicado\nno fue encontrado." );
    alerta -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );
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
    
    // Revisa si existen tickets pendientes
    const bool ticketsPendientes = aplicacion -> obtenerTicketsPendientes().empty();
    if( !ticketsPendientes ){
        Widget widget( "resources/interfaces/RegistroExitoso.glade" );
        widget.establecerIconoVentana( "RegistroExitoso", "resources/images/icons/logo.png");
        widget.establecerTextoEtiqueta( "Mensaje", "No se puede continuar con\nel cierre si hay tickets pendientes." );
        widget.conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), nullptr );
        return;
    }
    
    try{
        Widget *ventanaCorte = new Widget( "resources/interfaces/CorteDia/CorteDia.glade" );
        ventanaCorte -> establecerIconoVentana( "VentanaCorte", "resources/images/icons/logo.png");
        ventanaCorte -> conectarSenal( "VentanaCorte", "destroy", G_CALLBACK( gtk_widget_destroy ), nullptr );
        ventanaCorte -> conectarSenal( "BotonRealizarCorte", "clicked", G_CALLBACK( generarReporte ), ventanaCorte );
    }
    catch( runtime_error &e ){
        cerr << e.what() << endl;
    }
}
