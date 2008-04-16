/* This class keeps track of where moles are in the grid. It is kind of
 * useless in the basic version of our game but will be useful when we go
 * for extra credit.
 */
class Grid
{
	public:
		Grid( Molinator_Window );
		bool is_empty( int, int );
		Mole contains( int, int );
		bool add( Mole, int, int );
		Mole remove( int, int );
	private:
		Molinator_Window win;
		//creates a vector of size 10.  Each of the 10 objects has an initial value
		//of vector<Mole>(10).  To access what is in the vector write grid[i][j]
		vector<vector<Mole>> grid( 10, vector<Mole>( 10 ) );
}
