#include "Database.h"
#include "Utilidades.h"
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

Database::Database(): 
	database( nullptr )
{
	// Nada que hacer 
}

Database::~Database()
{
	close();
}

void Database::connect( string file )
{
	// Connects to the database
	int status = sqlite3_open( file.c_str(), &database );
	if( status ){
		throw runtime_error( "Error trying to open database \'" + file + "\'."  );
	}
}

void Database::query( std::string query, int( * callback )( void *, int, char **, char ** ) )
{
	char *errorMessage;
	queryReset();
	int status = sqlite3_exec( database, query.c_str(), callback, nullptr, &errorMessage );
	if( status != SQLITE_OK ){
		throw runtime_error( "Error querying." );
	}
}

void Database::close()
{
	sqlite3_close( database );
}
