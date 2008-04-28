#pragma once

namespace Score_IO
{
static const string SCORE_FILE = "scores.txt";

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
void add_score( string name, int new_score )
{/*
	fstream fst( SCORE_FILE.c_str() );
	int score, pointer;
	string line;
	do
	{
		pointer = fst.tellg();
		line = fst.getline();
		//atoi returns the first int it finds, isn't affected by the chars after
		score = atoi( line );
	}
	while( score > new_score ); */
}

/* Returns a vector of strings formatted like this:
 * "name            score"
 * "name two        score"
 * etc...
 * where all the names and scores line up in neat columns
 */
vector<string> top_scores()
{
	vector<string> v;
	v.push_back("philip                  18320");
	v.push_back("Dr. Daugherty           2545");
	v.push_back("noob                    100");
	v.push_back("lol_failz               0");
	v.push_back("eric                    -255");
	return v;
}

};
/* Example of the scores file: (note the spaces in the username)
 *
 * 10315 philip
 * 815 Dr. Daugherty
 * 300 eric
 * 0 noob
 * -400 lol_failz
 */
