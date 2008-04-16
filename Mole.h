
class Mole
{
	public:
		Mole()
		{

		}
		
		inline int points() { return points; }
		inline int row() { return row; }
		inline int column() { return column; }
		inline int color() { return color; }
		inline int center() { return center; }
	private:
		//points user gets when "whacked"
		int points;
		//position on grid
		int row;
		int column;
		//Color of mole
		Color color;
		//center of circle.  idea=make more points have smaller circles?
		Point center;
}
