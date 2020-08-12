#include "Funciones.h"
#include "Vistas.h"
#include "Aplicacion.h"
#include "Utilidades.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

void registrarTicket( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el ticket con el que se validan los datos
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    contenido -> establecerTextoEtiqueta( "EstadoLectura", "Grabando..." );
    
    cout << "Datos registrados" << endl
	     << "Folio: " << ticket -> obtenerFolio() << endl
	     << "Placas: " << ticket -> obtenerNumeroPlacas() << endl
		 << "Tipo de caja: " << ticket -> obtenerNombreTipoCaja() << endl
		 << "Nombre del conductor: " << ticket -> obtenerNombreConductor() << endl
		 << "Nombre de la empresa: " << ticket -> obtenerNombreProcedencia() << endl
		 << "Departamento: " << ticket -> obtenerNombreDepartamento() << endl
		 << "Zona: " << ticket -> obtenerZona() << endl
		 << "Subzona: " << ticket -> obtenerSubzona() << endl
		 << "Peso bruto: " << ticket -> obtenerPesoBruto() << endl;
		 
	try{
		string consulta = "insert into tickets values( null, \'" + ticket -> obtenerNumeroEconomico() + "\', " + "\'" + ticket -> obtenerNumeroPlacas() + "\', " +
						  to_string( ticket -> obtenerClaveTipoCaja() ) + ", " + "\'" + ticket -> obtenerNombreConductor() + "\', " + to_string( ticket -> obtenerClaveProcedencia() ) + ", " +
						  "\'" + ticket -> obtenerZona() + "\', " + "\'" + ticket -> obtenerSubzona() + "\', " + to_string( ticket -> obtenerClaveDepartamento() ) + ", " +
						  "date( \'now\', \'localtime\' ), time( \'now\', \'localtime\' ), null, " + to_string( ticket -> obtenerPesoBruto() ) + ", null, null, 1 );";
						  
		database.query( consulta, NULL );
		
		// Muestra el mensaje de que el usuario fue creado exitosamente
        Widget *widget = new Widget( "../resources/interfaces/RegistroTicket/MensajeInformacion.glade" );
        widget -> ocultarElemento( "Elemento" );
		widget -> establecerTextoEtiqueta( "EntradaElemento", "Ticket registrado correctamente." );
        widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );		
        vistaBascula( nullptr, aplicacion );						    																 
	}
	catch( runtime_error &e ){
		cerr << e.what() << endl;
	}
}

void registrarNumeroEconomico( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el numero de económico
    GObject *objeto = contenido -> obtenerObjeto( "EntradaNumeroEconomico" );
    const char * numeroEconomico = gtk_entry_get_text( GTK_ENTRY( objeto ) );
    
	// Obtiene el objeto para registrar errores
	objeto = contenido -> obtenerObjeto( "MensajeError" );
    
    try{
		aplicacion -> obtenerTicket() -> establecerNumeroEconomico(  numeroEconomico );
		vistaRegistrarPlacas( nullptr, aplicacion );
	}
	catch( invalid_argument &e ){
		string what = e.what();
        gtk_label_set_text( GTK_LABEL( objeto ), what.c_str() );
        gtk_widget_show( GTK_WIDGET( objeto ) );
	}
}

void registrarNumeroPlacas( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    
    // La aplicación no apunta hacia ningún lado
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el numero de económico
    GObject *objeto = contenido -> obtenerObjeto( "EntradaNumeroPlacas" );
    const char * numeroPlacas = gtk_entry_get_text( GTK_ENTRY( objeto ) );
    
	// Obtiene el objeto para registrar errores
	objeto = contenido -> obtenerObjeto( "MensajeError" );
    
    try{
		aplicacion -> obtenerTicket() -> establecerNumeroPlacas(  numeroPlacas );
		
		vistaRegistrarTipoCaja( nullptr, aplicacion );
	}
	catch( invalid_argument &e ){
		string what = e.what();
        gtk_label_set_text( GTK_LABEL( objeto ), what.c_str() );
        gtk_widget_show( GTK_WIDGET( objeto ) );
	}
}

void registrarTipoCaja( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene una referencia al ticket que está siendo registrado
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Obtiene el tipo de caja
    string tipoCaja = contenido -> obtenerTextoEntrada( "EntradaTipoCaja" );
    
    try{
		// Valida y establece el tipo de caja
		ticket -> establecerClaveTipoCaja( obtenerEntero( tipoCaja ) );
		
		// Busca el tipo de procedencia con la clave registrada
		string consulta = "select * from tipos_caja where clave_tipo = " + to_string( ticket -> obtenerClaveTipoCaja() ) + " limit 1;";
		database.query( consulta, databaseCallback );
		
		// Obtiene el campo del nombre del tipo de caja
		if( results > 0 ){
			tipoCaja = rows.at( 0 ) -> campos[ 1 ];
		
			// Valida y establece el tipo de caja
			ticket -> establecerNombreTipoCaja( tipoCaja );
		
			// Establece el indicador del tipo de caja y lo muestra
			contenido -> establecerTextoEtiqueta( "EntradaCaja", ticket -> obtenerNombreTipoCaja() );
			
			// Muestra el mensaje de que el usuario fue creado exitosamente
			Widget *widget = new Widget( "../resources/interfaces/RegistroTicket/MensajeInformacion.glade" );
			widget -> establecerTextoEtiqueta( "Elemento", "Tipo de caja: " );
			widget -> establecerTextoEtiqueta( "EntradaElemento", ticket -> obtenerNombreTipoCaja() );
			widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );
	
			// Da pausa de un segundo para cambiar de vista
			vistaRegistrarConductor( nullptr, aplicacion );
		}
		else{
			contenido -> establecerTextoEtiqueta( "MensajeError", "Tipo de caja no existente." );
			contenido -> mostrarElemento( "MensajeError" );
		}
	}
	catch( invalid_argument &ia ){
        contenido -> establecerTextoEtiqueta( "MensajeError", ia.what() );
		contenido -> mostrarElemento( "MensajeError" );
	}
	catch( runtime_error &er ){
		contenido -> establecerTextoEtiqueta( "MensajeError", "Tipo de caja no existente." );
		contenido -> mostrarElemento( "MensajeError" );
	}
}

void registrarNombreConductor( GtkWidget *widget, gpointer ptr )
{	
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene una referencia al ticket que se está registrando
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Obtiene el nombre del conductor
    string nombreConductor = contenido -> obtenerTextoEntrada( "EntradaNombreConductor" );
    
    try{
		// Valida y establece el nombre del conductor
		aplicacion -> obtenerTicket() -> establecerNombreConductor( nombreConductor );
		
		// Prosigue a registrar la procedencia
		vistaRegistrarProcedencia( nullptr, aplicacion );
	}
	catch( invalid_argument &ia ){
		contenido -> establecerTextoEtiqueta( "MensajeError",ia.what() );
		contenido -> mostrarElemento( "MensajeError" );
	}
}

void registrarProcedencia( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el ticket con el que se validan los datos
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Obtiene el numero de procedencia
    string procedencia = contenido -> obtenerTextoEntrada( "EntradaProcedencia" );
    
    try{
		// Valida y establece la procedencia
		ticket -> establecerClaveProcedencia( obtenerEntero( procedencia ) );
		
		// Busca la procedencia con la clave registrada
		string consulta = "select * from procedencias where clave_procedencia = " + to_string( ticket -> obtenerClaveProcedencia() ) + " limit 1;";
		database.query( consulta, databaseCallback );
		if( results > 0 ){
			// Obtiene el campo del nombre de la procedencia
			procedencia = rows.at( 0 ) -> campos[ 1 ];
			
			// Valida y establece la procedencia
			ticket -> establecerNombreProcedencia( procedencia );
			
			Widget *widget = new Widget( "../resources/interfaces/RegistroTicket/MensajeInformacion.glade" );
			widget -> establecerTextoEtiqueta( "Elemento", "Lugar de procedencia: " );
			widget -> establecerTextoEtiqueta( "EntradaElemento", ticket -> obtenerNombreProcedencia() );
			widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );

			// Decide hacia donde ir
			switch( ticket -> obtenerClaveProcedencia() ){
				// Caabsa GDL
				case 1:
					ticket -> establecerClaveDepartamento( 0 );
					ticket -> establecerNombreDepartamento( "No especificado" );
					vistaRegistrarZona( nullptr, aplicacion );
					break;
				// Sólo registran departamentos
				case 2:
				case 3:
				case 4:
				case 5:
					ticket -> establecerZona( "Sin especificar" );
					ticket -> establecerSubzona( "Sin especificar" );
					vistaRegistrarClaveDepartamento( nullptr, aplicacion );
					break;
			}
		}
		else{
			contenido -> ocultarElemento( "IndicadorDependencia" );
			contenido -> establecerTextoEtiqueta( "MensajeError", "Introduce un código de dependencia\nexistente." );
			contenido -> mostrarElemento( "MensajeError" );
		}
	}
	catch( invalid_argument &ia ){
		contenido -> ocultarElemento( "IndicadorDependencia" );
		contenido -> establecerTextoEtiqueta( "MensajeError",ia.what() );
		contenido -> mostrarElemento( "MensajeError" );
	}
	catch( runtime_error &re ){
		contenido -> ocultarElemento( "IndicadorDependencia" );
		contenido -> establecerTextoEtiqueta( "MensajeError", "Dependencia no encontrada." );
		contenido -> mostrarElemento( "MensajeError" );
	}
}

void registrarClaveDepartamento( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el ticket con el que se validan los datos
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Obtiene la zona
    string claveDepartamento = contenido -> obtenerTextoEntrada( "EntradaClaveDepartamento" );
    
    try{
		// Valida y establece el departamento
		ticket -> establecerClaveDepartamento( obtenerEntero( claveDepartamento ) );
		
		// Revisa que la clave departamento introducida exista
		string consulta = "select nombre_departamento from departamentos de where clave_departamento = " + to_string( ticket -> obtenerClaveDepartamento() ) + " limit 1;";
		database.query( consulta, databaseCallback );
		if( results > 0 ){
			// Obtiene el departamento predefinido y completa el formulario automáticamente con ese departamento
            string nombreDepartamento = rows.at( 0 ) -> campos[ 0 ];
			ticket -> establecerNombreDepartamento( nombreDepartamento );
            
            // Crea la ventana en la que muestra el nombre del departamento
            Widget *widget = new Widget( "../resources/interfaces/RegistroTicket/MensajeInformacion.glade" );
			widget -> establecerTextoEtiqueta( "Elemento", "Departamento: " );
			widget -> establecerTextoEtiqueta( "EntradaElemento", ticket -> obtenerNombreDepartamento() );
			widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );
			
			vistaLectorBasculaEntrada( nullptr, aplicacion );
		}
		else{
			contenido -> establecerTextoEtiqueta( "MensajeError", "Debe indroducir un departamento existente." );
			contenido -> mostrarElemento( "MensajeError" );
		}
	}
	catch( invalid_argument &ia ){
		contenido -> establecerTextoEtiqueta( "MensajeError", ia.what() );
		contenido -> mostrarElemento( "MensajeError" );
	}
}

void registrarNombreDepartamento( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el ticket con el que se validan los datos
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Obtiene el nombre del departamento
    string nombreDepartamento = contenido -> obtenerTextoEntrada( "EntradaNombreDepartamento" );
    
    try{
		// Valida y establece el nombre departamento
		ticket -> establecerNombreDepartamento( nombreDepartamento );
		
		// Prosigue con el lector de báscula
		vistaLectorBasculaEntrada( nullptr, aplicacion );
	}
	catch( invalid_argument &ia ){
		contenido -> establecerTextoEtiqueta( "MensajeError", ia.what() );
		contenido -> mostrarElemento( "MensajeError" );
	}
}

void registrarZona( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el ticket con el que se validan los datos
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Obtiene la zona
    string zona = contenido -> obtenerTextoEntrada( "EntradaZona" );
    
    try{
		// Valida y establece la zona
		ticket -> establecerZona( zona );
		
		// Prosigue a la seccion de subzona
		vistaRegistrarSubzona( nullptr, aplicacion );
	}
	catch( invalid_argument &ia ){
		contenido -> establecerTextoEtiqueta( "MensajeError",ia.what() );
		contenido -> mostrarElemento( "MensajeError" );
	}
}

void registrarSubzona( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el ticket con el que se validan los datos
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Obtiene la zona
    string subzona = contenido -> obtenerTextoEntrada( "EntradaSubzona" );
    
    try{
		// Valida y establece la subzona
		ticket -> establecerSubzona( subzona );
		
		vistaLectorBasculaEntrada( nullptr, aplicacion );
	}
	catch( invalid_argument &ia ){
		contenido -> establecerTextoEtiqueta( "MensajeError",ia.what() );
		contenido -> mostrarElemento( "MensajeError" );
	}
}

void registrarPesoBruto( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
    
    // Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el ticket con el que se validan los datos
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Lee el peso bruto
    string pesoBruto = contenido -> obtenerTextoEntrada( "EntradaPeso" );
    
    try{
		// Valida y establece el peso bruto
		ticket -> establecerPesoBruto( stod( pesoBruto ) );
		
		registrarTicket( nullptr, aplicacion );
	}
	catch( invalid_argument &ia ){
		contenido -> ocultarElemento( "IndicadorDependencia" );
		contenido -> establecerTextoEtiqueta( "MensajeError",ia.what() );
		contenido -> mostrarElemento( "MensajeError" );
	}
}

void registrarPesoTara( GtkWidget *widget, gpointer ptr )
{
	// Referencia a la aplicacion
    Aplicacion *aplicacion = static_cast< Aplicacion * >( ptr );
    if( aplicacion == nullptr ){
        throw invalid_argument( "Aplicacion no encontrada." );
    }
 
	// Obtiene el contenido de la aplicacion
    Widget *contenido = aplicacion -> obtenerVistaContenido();
    
    // Obtiene el ticket que va a finalizar
    Ticket *ticket = aplicacion -> obtenerTicket();
    
    // Lee el peso tara
    string pesoTara = contenido -> obtenerTextoEntrada( "EntradaPeso" );
    
	try{
		// Valida y establece el peso tara
		ticket -> establecerPesoTara( stod( pesoTara ) );
		
		// Calcula el peso neto
		ticket -> calcularPesoNeto();
		
		// Realiza la inserción
		string consulta = "update tickets set hora_salida = time( \'now\', \'localtime\' ), peso_tara = " + to_string( ticket -> obtenerPesoTara() ) + ", peso_neto = " + to_string( ticket -> obtenerPesoNeto() ) + ", pendiente = 0 where folio = " + to_string( ticket -> obtenerFolio() ) + " limit 1;";
		database.query( consulta, NULL );
		
		// Crea la ventana en la que muestra el nombre del departamento
        Widget *widget = new Widget( "../resources/interfaces/RegistroTicket/MensajeInformacion.glade" );
		widget -> ocultarElemento( "Elemento" );
		widget -> establecerTextoEtiqueta( "EntradaElemento", "Registro completo.\nImprimiento..." );
		widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );
		vistaControlBasculista( nullptr, aplicacion );
	}
	catch( invalid_argument &ia ){
		cerr << ia.what() << endl;
	}
	catch( runtime_error &re ){
		cerr << re.what() << endl;
	}
}

void hola( GtkWidget *widget, gpointer ptr )
{
	cout << "Hola" << endl;
}
