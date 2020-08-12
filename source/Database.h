#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database
{
	public:
		Database();
		~Database();
		
		// Connects with the database
		void connect( std::string file );
		
		// It makes the queries to the database
		void query( std::string query, int (* callback)( void*,int,char**,char** ) );
		
		// Close the conection with database
		void close();
	
	private:
		sqlite3 *database;
};

#endif
