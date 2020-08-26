#include "Funciones.h"
#include "Vistas.h"
#include "Aplicacion.h"
#include "Utilidades.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <Windows.h>
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
    
   	// Imprimir ticket
		 
	try{
		string pesoBruto = quitarComa( to_string( ticket -> obtenerPesoBruto() ) );

		string consulta = "insert into tickets values( null, '" + ticket -> obtenerNumeroEconomico() + "', " + "'" + ticket -> obtenerNumeroPlacas() + "', " +
						  to_string( ticket -> obtenerClaveTipoCaja() ) + ", " + "'" + ticket -> obtenerNombreConductor() + "', " + to_string( ticket -> obtenerClaveProcedencia() ) + ", " +
						  "'" + ticket -> obtenerZona() + "', " + "'" + ticket -> obtenerSubzona() + "', " + to_string( ticket -> obtenerClaveDepartamento() ) + ", " +
						  "date( 'now', 'localtime' ), time( 'now', 'localtime' ), null, " + pesoBruto + ", null, null, 1 );";
						  
		cout << consulta << endl;
		database.query( consulta, NULL );
		
		// Muestra el mensaje de que el usuario fue creado exitosamente
        Widget *widget = new Widget( "resources/interfaces/RegistroTicket/MensajeInformacion.glade" );
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
			Widget *widget = new Widget( "resources/interfaces/RegistroTicket/MensajeInformacion.glade" );
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
			
			Widget *widget = new Widget( "resources/interfaces/RegistroTicket/MensajeInformacion.glade" );
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
			contenido -> establecerTextoEtiqueta( "MensajeError", "Introduce un código de dependencia\nexistente." );
			contenido -> mostrarElemento( "MensajeError" );
		}
	}
	catch( invalid_argument &ia ){
		contenido -> establecerTextoEtiqueta( "MensajeError",ia.what() );
		contenido -> mostrarElemento( "MensajeError" );
	}
	catch( runtime_error &re ){
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
            Widget *widget = new Widget( "resources/interfaces/RegistroTicket/MensajeInformacion.glade" );
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
		string consulta = "update tickets set hora_salida = time( \'now\', \'localtime\' ), peso_tara = " + quitarComa( to_string( ticket -> obtenerPesoTara() ) ) + ", " +
						  "peso_neto = " + quitarComa( to_string( ticket -> obtenerPesoNeto() ) ) + ", pendiente = 0 where folio = " + to_string( ticket -> obtenerFolio() ) + ";";
						
		// Realiza la consulta
		database.query( consulta, NULL );
		
		// Crea la ventana en la que muestra el nombre del departamento
        Widget *widget = new Widget( "resources/interfaces/RegistroTicket/MensajeInformacion.glade" );
		widget -> ocultarElemento( "Elemento" );
		widget -> establecerTextoEtiqueta( "EntradaElemento", "Registro completo.\nImprimiento..." );
		widget -> conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), widget );
		vistaControlBasculista( nullptr, aplicacion );

		imprimirTicket( ticket );
	}
	catch( invalid_argument &ia ){
		cerr << ia.what() << endl;
	}
	catch( runtime_error &re ){
		cerr << re.what() << endl;
	}
}

void imprimirTicket( Ticket *ticket )
{
	// Obtine la hora de salida registrada en la base de datos
	string consulta = "select fecha, hora_entrada, hora_salida from tickets where folio = " + to_string( ticket -> obtenerFolio() ) + ";";
	database.query( consulta, databaseCallback );
	if( results > 0 ){
		ticket -> establecerFecha( rows.at( 0 ) -> campos.at( 0 ) );
		ticket -> establecerHoraEntrada( rows.at( 0 ) -> campos.at( 1 ) );
		ticket -> establecerHoraSalida( rows.at( 0 ) -> campos.at( 2 ) );
	}

	// Stream para construir el ticket
	stringstream str;

	str << "------------------------------------" << endl
		<< "            C A A B S A" 			  << endl
	    << "------------------------------------" << endl
	    << "      * PLANTA TRANSFERENCIA *" 	  << endl
	    << "FECHA: " << ticket -> obtenerFecha() << "     FOLIO: " << setfill( '0' ) << setw( 7 ) << ticket -> obtenerFolio() << endl
	    << "CONSECUTIVO:     " << 1 << endl << endl
	    << "ECONÓMICO NO:    " << ticket -> obtenerNumeroEconomico() << endl 
	    << "PLACAS:          " << ticket -> obtenerNumeroPlacas() << endl
	    << "TIPO DE CAJA:    " << ticket -> obtenerNombreTipoCaja() << endl
	    << "CONDUCTOR:       " << ticket -> obtenerNombreConductor() << endl
	    << "PROCEDENCIA:     " << ticket -> obtenerNombreProcedencia() << endl << endl
	    << "HORA DE ENTRADA: " << ticket -> obtenerHoraEntrada() << endl
	    << "HORA DE SALIDA:  " << ticket -> obtenerHoraSalida() << endl << endl
	    << "PESO BRUTO:      " << ticket -> obtenerPesoBruto() << endl
	    << "PESO TARA:       " << ticket -> obtenerPesoTara() << endl
	    << "------------------------------------" << endl
	    << "PESO NETO:       " << ticket -> obtenerPesoNeto() << endl
	    << "------------------------------------" << endl << setfill( ' ' );
	
	if( ticket -> obtenerClaveProcedencia() == 1 ){
	    str << "ZONA:    " << ticket -> obtenerZona() << endl
	    	<< "SUBZONA: " << ticket -> obtenerSubzona() << endl;
	}
	else{
	   	str  << "DEPARTAMENTO: " << setw( 2 ) << ticket -> obtenerClaveDepartamento() << "-" << ticket -> obtenerNombreDepartamento() << endl;
	}

	// Abre el archivo y lo carga
	ofstream archivoSalida;

	archivoSalida.open( "resources/others/ticket.txt", ios_base::out );
	if( !archivoSalida ){
		throw runtime_error( "Ocurrió un error al abrir el archivo temporal." );
	}

	// Envía el contenido del stream al archivo
	archivoSalida << str.str();

	// Cierra el archivo
	archivoSalida.close();

	// Imprime el archivo creado
	system( "notepad /p resources/others/ticket.txt" );
}

void imprimirReporte( std::string fecha )
{
	string consulta = "select count( folio ), sum( peso_neto ), time( 'now', 'localtime' ) from tickets where fecha = '" + fecha + "';";
	database.query( consulta, databaseCallback );
	if( rows.size() > 0 ){
		int totalTickets = obtenerEntero( rows.at( 0 ) -> campos.at( 0 ) );
		int totalKg = obtenerEntero( rows.at( 0 ) -> campos.at( 1 ) );
		std::string hora = rows.at( 0 ) -> campos.at( 2 );

		// Obtiene las procedencias
		std::vector< Row > procedencias;
		consulta = "select * from procedencias;";
		database.query( consulta, databaseCallback );
		if( rows.size() > 0 ){
			for( Row *row : rows ){
				Row procedencia;
				for( string campo : row -> campos ){
					procedencia.campos.push_back( campo );
				}
				procedencias.push_back( procedencia );
			}
		}

		consulta = "select clave_procedencia, count( folio ), sum( peso_neto ) from tickets join procedencias on tickets.codigo_empresa = procedencias.clave_procedencia where fecha = '" + fecha + "' group by codigo_empresa;";
		database.query( consulta, databaseCallback );
		// Construye el formato del ticket
		stringstream str;
		str << "--------------------------------------------" << endl
	    	<< "                 C A A B S A" << endl
        	<< "               REPORTE GENERAL" << endl
			<< "--------------------------------------------" << endl
			<< "         * PLANTA TRANSFERENCIA *" << endl << endl
			<< "FECHA: " << setw(10) << fecha << "            " << "HORA: " << setw( 8 ) << hora << endl << endl;
			for( Row procedencia : procedencias ){
				double kilogramos = 0;
				int tickets = 0;
				for( Row *row : rows ){
					if( procedencia.campos.at( 0 ) == row -> campos.at( 0 ) ){
						kilogramos = stod( row -> campos.at( 2 ) );
						tickets = obtenerEntero( row -> campos.at( 1 ) );
						break;
					}
				}
				str << setw( 22 ) << procedencia.campos.at( 1 ) << ": " << setw( 7 ) << kilogramos << " Kg "
					<< setw( 3 ) << tickets << " Tick." << endl;
			}
		str	<< "--------------------------------------------\n"
			<< "TOTAL:                  " << setw( 7 ) << totalKg << "Kg " << setw( 3 ) << totalTickets << " TICK." << endl
			<< "-------------------------------------------\n";

		// Abre el archivo y lo carga
		ofstream archivoSalida;

		archivoSalida.open( "resources/others/report.txt", ios_base::out );
		if( !archivoSalida ){
			throw runtime_error( "Ocurrió un error al abrir el archivo temporal." );
		}

		// Envía el contenido del stream al archivo
		archivoSalida << str.str();

		// Cierra el archivo
		archivoSalida.close();

		system( "notepad /p resources/others/report.txt" );
	}
}

void generarReporte( GtkWidget *widget, gpointer ptr )
{
	Widget * ventana = static_cast< Widget * >(ptr);
	stringstream consulta;
	unsigned int aaaa, mm, dd;
	GObject *calendario = ventana -> obtenerObjeto( "EntradaFecha" );
	gtk_calendar_get_date( GTK_CALENDAR( calendario ), &aaaa, &mm, &dd );
	stringstream fecha;
	fecha << setfill( '0' ) << setw(4) << aaaa << "-"  << setw(2) << (mm + 1) << "-" << setw( 2 ) << dd << setfill(' ');

	consulta << "select folio as 'FOLIO'," << endl
	 	     << "numero_economico as 'NUMERO ECONOMICO'," << endl
        	 << "numero_placa as 'PLACA'," << endl
        	 << "nombre_tipo as 'TIPO DE CAJA'," << endl
        	 << "nombre_conductor as 'CONDUCTOR'," << endl
        	 << "procedencias.nombre_procedencia as 'EMPRESA'," << endl
        	 << "zona as 'ZONA'," << endl
        	 << "subzona as 'SUBZONA'," << endl
         	 << "nombre_departamento as 'DEPARTAMENTO'," << endl
        	 << "fecha as 'FECHA'," << endl
        	 << "hora_entrada as 'HORA DE ENTRADA'," << endl
        	 << "hora_salida as 'HORA DE SALIDA'," << endl
        	 << "peso_bruto as 'PESO BRUTO'," << endl
        	 << "peso_tara as 'PESO TARA'," << endl
        	 << "peso_neto as 'PESO NETO' " << endl
        	 << "from tickets " << endl
        	 << "join procedencias on procedencias.clave_procedencia = tickets.codigo_empresa " << endl
        	 << "join departamentos on departamentos.clave_departamento = tickets.codigo_departamento " << endl
        	 << "join tipos_caja on tipos_caja.clave_tipo = tipo_caja " << endl
        	 << "where fecha = '" << fecha.str() << "';";
 
    database.query( consulta.str(), databaseCallback );
    if( rows.size() > 0 ){
    	stringstream str;
    	str 	<< "\"" << rows.at(0) -> columnas.at( 0 ) << "\",\"" << rows.at(0) -> columnas.at( 1 ) << "\",\"" << rows.at(0) -> columnas.at( 2 ) << "\",\"" << rows.at( 0 ) -> columnas.at( 3 )
    		<< "\",\"" << rows.at(0) -> columnas.at( 4 ) << "\",\"" << rows.at(0) -> columnas.at( 5 ) << "\",\"" << rows.at(0) -> columnas.at( 6 ) << "\",\"" << rows.at(0) -> columnas.at( 7 )
    		<< "\",\"" << rows.at(0) -> columnas.at( 8 ) << "\"," << rows.at(0) -> columnas.at( 9 ) << "\",\"" << rows.at(0) -> columnas.at( 10 ) << "\",\"" << rows.at(0) -> columnas.at( 11 )
    		<< "\",\"" << rows.at(0) -> columnas.at( 12 ) << "\",\"" << rows.at(0) -> columnas.at( 13 ) << "\",\"" << rows.at(0) -> columnas.at( 14 ) << "\"" << endl;

   		for( Row * row : rows ){
   			str << row -> campos.at( 0 ) << "," << row -> campos.at( 1 ) << "," << row -> campos.at( 2 ) << ",\"" << row -> campos.at( 3 )
    		<< "\",\"" << row -> campos.at( 4 ) << "\",\"" << row -> campos.at( 5 ) << "\",\"" << row -> campos.at( 6 ) << "\",\"" << row -> campos.at( 7 )
    		<< "\",\"" << row -> campos.at( 8 ) << "\",\"" << row -> campos.at( 9 ) << "\",\"" << row -> campos.at( 10 ) << "\",\"" << row -> campos.at( 11 )
    		<< "\"," << row -> campos.at( 12 ) << "," << row -> campos.at( 13 ) << "," << row -> campos.at( 14 ) << endl;
   		}

   		try{
   			// Abre el archivo y lo carga
			ofstream archivoSalida;
			string nombreReporte = "resources\\reports\\Corte del dia.csv";
			archivoSalida.open( nombreReporte, ios_base::out );
			if( !archivoSalida ){
				throw runtime_error( "Ocurrió un error al abrir el archivo temporal." );
			}

			// Envía el contenido del stream al archivo
			archivoSalida << str.str();

			// Cierra el archivo
			archivoSalida.close();

			imprimirReporte( fecha.str() );

			Widget mensaje( "resources/interfaces/RegistroExitoso.glade" );
    		mensaje.establecerIconoVentana( "RegistroExitoso", "resources/images/icons/logo.png");
    		mensaje.establecerTextoEtiqueta( "Mensaje", "Reporte generado\nespere unos momentos." );
    		mensaje.conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), nullptr );
			ShellExecute(NULL, "open", nombreReporte.c_str(), NULL, NULL, SW_HIDE );
    	}
    	catch( runtime_error &e ){
    		Widget mensaje( "resources/interfaces/RegistroExitoso.glade" );
    		mensaje.establecerIconoVentana( "RegistroExitoso", "resources/images/icons/logo.png");
    		mensaje.establecerTextoEtiqueta( "Mensaje", "Error al obtener el reporte\nasegúrese de que no esté siendo usado\npor otro programa." );
    		mensaje.conectarSenal( "BotonAceptar", "clicked", G_CALLBACK( gtk_window_close ), nullptr );
    	}
    }
}
