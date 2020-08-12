#ifndef UTILIDADES_H
#define UTILIDADES_H
#include <vector>
#include <string>
#include "Database.h"
#include <gtk/gtk.h>

struct Row
{
	std::vector< std::string >campos;
};

extern unsigned int results;
extern std::vector< Row * >rows;
extern Database database;

// Reestablece el vector y el índice de consultas
void queryReset();

// Callback usado para ejecutar la consulta de la base de datos
int databaseCallback( void * noUsado, int numeroColumnas, char **campos, char **nombreColumnas );

// Obtiene el entero de un string
int obtenerEntero( std::string );

// Convierte el texto de minusculas a mayusculas
void insert_text_handler( GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data );

#endif
