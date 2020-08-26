/* Funciones para extraer los datos de los formularios */
#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <gtk/gtk.h>
#include <string>
#include "Ticket.h"

void registrarTicket( GtkWidget *widget, gpointer ptr );
void registrarNumeroEconomico( GtkWidget *widget, gpointer ptr );
void registrarNumeroPlacas( GtkWidget *widget, gpointer ptr );
void registrarNombreConductor( GtkWidget *widget, gpointer ptr );
void registrarTipoCaja( GtkWidget *widget, gpointer ptr );
void registrarProcedencia( GtkWidget *widget, gpointer ptr );
void registrarClaveDepartamento( GtkWidget *widget, gpointer ptr );
void registrarNombreDepartamento( GtkWidget *widget, gpointer ptr );
void registrarZona( GtkWidget *widget, gpointer ptr );
void registrarSubzona( GtkWidget *widget, gpointer ptr );
void registrarPesoBruto( GtkWidget *widget, gpointer ptr );
void registrarPesoTara( GtkWidget *widget, gpointer ptr ); 
void imprimirTicket( Ticket *ticket );
void imprimirReporte( std::string fecha );
void generarReporte( GtkWidget *widget, gpointer ptr );
void hola( GtkWidget *widget, gpointer ptr );

#endif
