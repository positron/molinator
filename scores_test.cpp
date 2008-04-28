#include "../../std_lib_facilities.h"
#include "scores.h"

using namespace Score_IO;

void print_vect( vector<string> );

/////////TESTING STUFF////////////////
int main()
{
	cout << "First game: nothing in file" << endl;
	print_vect( top_scores() );
	cout << "add_score( \"first\", 555 )" << endl;
	add_score( "first", 555 );
	print_vect( top_scores() );
}

void print_vect( vector<string> v )
{
	for( int i = 0; i < v.size(); i++ )
	{
		cout << v[i];
	}
}
