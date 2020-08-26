CC=g++
CFLAGS= `pkg-config --cflags gtk+-3.0 sqlite3`
LIBS=	`pkg-config --libs gtk+-3.0 sqlite3`

../build/aplicacion:  main.cpp Aplicacion.o Widget.o Usuario.o Empresa.o Domicilio.o Database.o Utilidades.o
	$(CC) $(CFLAGS) -o ../build/aplicacion main.cpp Aplicacion.o Widget.o Usuario.o Empresa.o Domicilio.o Database.o Utilidades.o Vistas.o Ticket.o Funciones.o $(LIBS)

Aplicacion.o:	Aplicacion.cpp Utilidades.o Usuario.o Vistas.o Ticket.o Funciones.o
	$(CC) -c Aplicacion.cpp $(CFLAGS) $(LIBS)

Widget.o:	Widget.cpp
	$(CC) -c Widget.cpp $(CFLAGS) $(LIBS)

Usuario.o:	Usuario.cpp
	$(CC) -c Usuario.cpp $(CFLAGS) $(LIBS)

Empresa.o:	Empresa.cpp
	$(CC) -c Empresa.cpp

Domicilio.o:	Domicilio.cpp
	$(CC) -c Domicilio.cpp

Database.o:	Database.cpp Utilidades.o
	$(CC) -c Database.cpp $(CFLAGS) $(LIBS)
Vistas.o: Vistas.cpp Funciones.o Utilidades.o
	$(CC) -c Vistas.cpp $(CFLAGS) $(LIBS)

Utilidades.o:	Utilidades.cpp
	$(CC) -c Utilidades.cpp $(CFLAGS) $(LIBS)

Ticket.o: Ticket.cpp
	$(CC) -c Ticket.cpp $(CFLAGS) $(LIBS)

Funciones.o: Funciones.cpp
	$(CC) -c Funciones.cpp $(CFLAGS) $(LIBS)
