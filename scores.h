namespace Score_IO
{

/* The user should call add_score first, then top_scores to view the top five
 * scores. 
 * add_score takes a score and adds it to the file if it is in the top five. If
 * it is not in the top five it keeps the file the way it was.
 *
 * Precondition:
 * The file has a list of no more than five scores (in order) with the syntax: 
 * name "space" score "newline"
 *
 * Postcondition:
 * same as precondition
 */
void add_score( string name, int score )
{
	//TODO
}

/* Returns a vector of strings formatted like this:
 * "name            score"
 * "name two        score"
 * etc...
 * where all the names and scores line up in neat columns
 */
vector<string> top_scores()
{
	//TODO
}

};
/* Example of the scores file: (note the spaces in the username)
 *
 * Philip 10315
 * Fatal1ty 815
 * Dr. Daugherty 300
 * 3p1c_Fa1lz lol 0
 * noob -400
 */
