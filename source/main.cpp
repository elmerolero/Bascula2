#include <gtk/gtk.h>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>
#include "Aplicacion.h"
#include "Database.h"
using namespace std;

const std::array< std::string, 12 > meses{ "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre" };
void actualizarTiempo( GtkWidget *widget, gpointer ptr );

Aplicacion aplicacion;

int main( int argc, char * argv[] )
{
    // Inicializa gtk
    gtk_init( &argc, &argv );
    
    // Inicia la ventana principal
    aplicacion.iniciar();
	
    // Establece la hora
    actualizarTiempo( nullptr, nullptr );
	
    // Habilita actulizar la hora
    g_timeout_add( 1000, G_SOURCE_FUNC( actualizarTiempo ), aplicacion.obtenerWidget() );
    
    // Bucle principal
    gtk_main();

    return 0; 
}

void actualizarTiempo( GtkWidget *widget, gpointer ptr )
{
    stringstream stringTiempo;
    string saludo;

    // Captura el momento
    auto momento = std::chrono::system_clock::now();
    
    // Convierte el momento obtenido en una estructura time_t
    time_t t  = std::chrono::system_clock::to_time_t( momento );

    // Obtiene en un estructura tm el tiempo local
    tm *tiempo = localtime( &t );

    // Establece la hora
    stringTiempo << "Hora: " << setfill( '0' ) << setw( 2 ) << ( ( tiempo -> tm_hour == 0 || tiempo -> tm_hour == 12 ) ? 12 : tiempo -> tm_hour % 12 ) 
				 << ":" << setw( 2 ) << to_string( tiempo -> tm_min ) << ":" << setw( 2 ) << to_string( tiempo -> tm_sec )
				 << ( ( tiempo -> tm_hour < 12 ) ? " am" : " pm" ) << setfill( ' ' );
    aplicacion.obtenerWidget()->establecerTextoEtiqueta( "Hora", stringTiempo.str() );
	
    // Limpia el buffer
    stringTiempo.str( "" );
	
    // Establece la fecha
    stringTiempo << "Fecha: " << setfill( '0' ) << setw( 2 ) << to_string( tiempo -> tm_mday ) << setfill( ' ' ) << " de " << meses.at( tiempo -> tm_mon ) << " de " << to_string( ( 1900 + tiempo -> tm_year ) );
	aplicacion.obtenerWidget()->establecerTextoEtiqueta( "Fecha", stringTiempo.str() );
    
    // ¿La hora oscila entre las 12 y 11 de la mañana?
    if( tiempo -> tm_hour > 1 && tiempo -> tm_hour < 12 ){
        // Establece el saludo a los buenos días
        saludo = "¡Buenos días! ¿Qué desea hacer hoy?";
    }
    // ¿La hora oscila entre las 12 y 8 de la tarde?
    else if( tiempo -> tm_hour > 11 && tiempo -> tm_hour < 18 ){
        saludo = "¡Buenas tardes! ¿Qué desea hacer hoy?";
    }
    // La hora oscila entre las 9 de la noche y 4 de la mañana
    else{
        saludo = "¡Buenas noches! ¿Qué desea hacer hoy?";
    }
    
    // Establece el saludo
    aplicacion.obtenerVistaContenido() -> establecerTextoEtiqueta( "Saludo", saludo );
    
    
    // Establece la fecha en formato sring para la base de datos 
    stringTiempo.str("");
    stringTiempo << setfill( '0' ) << setw( 2 ) << tiempo -> tm_mday << "/" << setw( 2 ) << ( tiempo -> tm_mon + 1 )<< "/" << ( tiempo -> tm_year + 1900 );
    aplicacion.establecerFecha( stringTiempo.str() );
}
