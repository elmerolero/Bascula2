#include "Utilidades.h"
#include <gtk/gtk.h>
#include "Aplicacion.h"
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

// Vector de renglones
unsigned int results;
std::vector< Row * >rows;
Database database;

void queryReset()
{
	results = 0;
	for( Row *row : rows ){
		row -> campos.clear();
	}
	
	rows.clear();
}

int databaseCallback( void * noUsado, int numeroColumnas, char **campos, char **nombreColumnas )
{
	// Elemento a insertar
	Row *row = new Row();
	
	
	for( unsigned int i = 0; i < numeroColumnas; ++i ){
		if( campos[ i ] != NULL ){
			row -> campos.push_back( campos[ i ] );
		}
		else{
			string campoVacio = "";
			row -> campos.push_back( campoVacio );
		}
	}
	
	// Incrementa el número de resultados
	results++;
	
	// Agrega el elemento al arreglo
	rows.push_back( row );

	return 0;
}

// Devuelve -1 en caso de error
int obtenerEntero( string str )
{
	// El número que retornará
	int numero;
	
	// Intenta...
	try{
		numero = stoi( str );
	}
	catch( invalid_argument &e ){
		numero = -1;
	}
	
	return numero;
}


void insert_text_handler( GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data )
{
	gchar *result = g_utf8_strup (text, length);

	g_signal_handlers_block_by_func (editable, (gpointer) insert_text_handler, data);
	gtk_editable_insert_text (editable, result, length, position);
	g_signal_handlers_unblock_by_func (editable, (gpointer) insert_text_handler, data);
	g_signal_stop_emission_by_name (editable, "insert_text");

	g_free (result);
}
