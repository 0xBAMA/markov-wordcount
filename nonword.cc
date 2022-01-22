#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <random>
#include <cctype>

#define modelEntry std::map< char, int >
#define modelType std::map< char, modelEntry >

modelType model;
std::ifstream in;

void CountLetters() {
	char curr, prev = ' ';
	in >> std::noskipws >> curr;
	do { //create the model
		if ( std::isalpha( curr ) || std::isspace( curr ) ) {
			++model[ prev ][ curr ];
			prev = curr;
		}
	} while( in >> std::noskipws >> curr );
}

void Spew( int count ) {
	int num = model.size();
	int run;
	std::random_device rd;
	std::mt19937 gen( rd() );
	std::uniform_int_distribution< int > dis( 0, num - 1 );

	dis.reset();
	run = dis( gen );
	char curr;

	for ( modelType::iterator p = model.begin(); p != model.end() && run > 0; ++p, --run ) {
		curr = p->first;
	}

	std::cout << std::endl << std::endl;

	while ( --count ) {
		//where should you go? very similar to above, but with fewer entries in the map
		std::vector< char > where_to;
		where_to.clear();
		char temp = curr;
		for (modelEntry::iterator p = model[ temp ].begin(); p != model[ temp ].end(); p++ ) {
			for ( int i = 0; i < p->second; i++ ) {
				where_to.push_back( p->first );
			}
		}
		std::uniform_int_distribution< int > inner_dis( 0, where_to.size() - 1 );
		inner_dis.reset();
		curr = where_to[ inner_dis( gen ) ];
		std::cout << curr;
	}
	std::cout << std::endl;
}

int main( int argc, char** argv ) {
	if ( argc < 2 )
		return( EXIT_FAILURE );

	in.open( argv[ 1 ] );
	if ( !in.is_open() ) return( EXIT_FAILURE );
	CountLetters(); //stream is good, read it

	for ( modelType::iterator p = model.begin(); p != model.end(); ++p ) { //report results
		int total_count = 0;
		for ( modelEntry::iterator q = model[ p->first ].begin(); q != model[ p->first ].end(); ++q ) {
			++total_count;
		}
		std::cout << "\'" << p->first << "\' has " << total_count << " occurrence(s)." << std::endl;
		for ( modelEntry::iterator q = model[ p->first ].begin(); q != model[ p->first ].end(); ++q ) {
			std::cout << "\tfollowed by: \'" << q->first << "\' " << q->second << " time(s)." << std::endl;
		}
	}
	Spew( atoi( argv[ 2 ] ) );
}
