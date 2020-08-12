#ifndef VISTAS_H
#define VISTAS_H

#include <gtk/gtk.h>

void vistaControlBasculista( GtkWidget *widget, gpointer ptr );
void vistaRegistroEmpresa( GtkWidget *widget, gpointer ptr );
void vistaBascula( GtkWidget *widget, gpointer ptr );
void vistaNuevoTicket( GtkWidget *widget, gpointer ptr );
void vistaRegistrarPlacas( GtkWidget *widget, gpointer ptr );
void vistaRegistrarConductor( GtkWidget *widget, gpointer ptr );
void vistaRegistrarTipoCaja( GtkWidget *widget, gpointer ptr );
void vistaRegistrarProcedencia( GtkWidget *widget, gpointer ptr );
void vistaRegistrarZona( GtkWidget *widget, gpointer ptr );
void vistaRegistrarSubzona( GtkWidget *widget, gpointer ptr );
void vistaRegistrarClaveDepartamento( GtkWidget *widget, gpointer ptr );
void vistaRegistrarNombreDepartamento( GtkWidget *widget, gpointer ptr );
void vistaLectorBasculaEntrada( GtkWidget *widget, gpointer ptr );
void vistaSeguimientoTicketPendienteEntrada( GtkWidget *widget, gpointer ptr );
void vistaCierreDia( GtkWidget *widget, gpointer ptr );

#endif
