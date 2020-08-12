CC=g++
LINKER_FLAGS= `pkg-config --cflags --libs gtk+-3.0 sqlite3`

../build/aplicacion:  main.cpp Aplicacion.o Widget.o Usuario.o Empresa.o Domicilio.o Database.o Utilidades.o
	$(CC) main.cpp $(LINKER_FLAGS) -g -o ../build/aplicacion Aplicacion.o Widget.o Usuario.o Empresa.o Domicilio.o Database.o Utilidades.o Vistas.o Ticket.o Funciones.o

Aplicacion.o:	Aplicacion.cpp Utilidades.o Usuario.o Vistas.o Ticket.o Funciones.o
	$(CC) $(LINKER_FLAGS) -c Aplicacion.cpp 

Widget.o:	Widget.cpp
	$(CC) $(LINKER_FLAGS) -c Widget.cpp

Usuario.o:	Usuario.cpp
	$(CC) $(LINKER_FLAGS) -c Usuario.cpp

Empresa.o:	Empresa.cpp
	$(CC) -c Empresa.cpp

Domicilio.o:	Domicilio.cpp
	$(CC) -c Domicilio.cpp

Database.o:	Database.cpp Utilidades.o
	$(CC) $(LINKER_FLAGS) -c Database.cpp

Vistas.o: Vistas.cpp Funciones.o Utilidades.o
	$(CC) $(LINKER_FLAGS) -c Vistas.cpp

Utilidades.o:	Utilidades.cpp
	$(CC) $(LINKER_FLAGS) -c Utilidades.cpp

Ticket.o: Ticket.cpp
	$(CC) $(LINKER_FLAGS) -c Ticket.cpp

Funciones.o: Funciones.cpp
	$(CC) $(LINKER_FLAGS) -c Funciones.cpp

