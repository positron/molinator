#include "../../std_lib_facilities.h"
#include "scores.h"

using namespace Score_IO;

void print_vect( vector<string> );

/////////TESTING STUFF////////////////
int main()
{
	cout << "First game: nothing in file" << endl;
	print_vect( top_scores() );

	cout << "\n\nadd_score( \"first\", 555 )" << endl;
	add_score( "first", 555 );
	print_vect( top_scores() );

	cout << "\n\nadd_score( \"second\", 25 )" << endl;
	add_score( "second", 25 );
	print_vect( top_scores() );

	cout << "\n\nadd_score( \"asdf woot sauce!\", 600 )" << endl;
	add_score( "asdf woot sauce!", 600 );
	print_vect( top_scores() );

	cout << "\n\nadd_score( \"blarg\", 40 )" << endl;
	add_score( "blarg", 40 );
	print_vect( top_scores() );

	cout << "\n\nadd_score( \"blarg\", 40 )" << endl;
	add_score( "blarg", 40 );
	print_vect( top_scores() );

	cout << "\n\nadd_score( \"asdfasd\", 40 )" << endl;
	add_score( "asdfasd", 40 );
	print_vect( top_scores() );

	cout << "\n\nadd_score( \"philip\", 1000 )" << endl;
	add_score( "philip", 1000 );
	print_vect( top_scores() );

	cout << "\n\nadd_score( \"noob\", 0 )" << endl;
	add_score( "noob", 0 );
	print_vect( top_scores() );
}

void print_vect( vector<string> v )
{
	cout << endl;
	for( int i = 0; i < v.size(); i++ )
	{
		cout << v[i] << endl;
	}
}
