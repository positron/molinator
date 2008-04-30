#pragma once

namespace Score_IO
{
//the high scores file resides in the same directory as the game executable
static const string SCORE_FILE = "scores.txt";

/* This function returns a vector of strings containing the contents of every
 * line of the file. Each string is a line.
 */
vector<string> read_lines()
{
	vector<string> v;
	fstream file( SCORE_FILE.c_str(), ios_base::in );
	//if there is no file return an empty vector
	if( !file.is_open() ) return v;
	string line;
	while( !file.eof() )
	{
		getline( file, line );
		if( line != "" )
			v.push_back( line );
	}
	//whatever happened to Java's good ol' String_Tokenizer?? :(
	return v;
}

/* This function returns a vector of high score strings formatted like this:
 * name                 score
 * name two             score two
 * ... etc
 */
vector<string> top_scores()
{
	vector<string> v;
	vector<string> lines = read_lines();
	for( int i = 0; i < lines.size(); i+= 2 )
	{
		stringstream ss;
		//format the scores
		ss << setw(30) << left << lines[i+1] << lines[i];
		v.push_back( ss.str() );
	}
	return v;
}

/* This function takes a new score and name and adds it in order to the high
 * scores file. It reads the data currently in the file, decides where to
 * insert the new name and score, and then truncates the file and writes back
 * all the data. It will never leave the file with more than 5 scores or out
 * of order scores.
 */
void add_score( string name, int new_score )
{
	//get lines in file before we truncate it
	vector<string> lines = read_lines();
	//open file for writing, erase anything currently in file
	fstream fst( SCORE_FILE.c_str(), ios_base::out | ios_base::trunc );
	if( lines.size() == 0 )
	{
		//file doesn't exist so create it
		ofstream fst( SCORE_FILE.c_str() );
		fst << new_score << endl << name << endl;
		return;
	}
	//loop to determine where to place score
	int insert;
	for( insert = 0; insert < lines.size(); insert+= 2 )
	{
		// <= so the newest score will be at the top (to make users happy)
		if( atoi( lines[insert].c_str() ) <= new_score )
			break;
	}
	//now insert is the place where we want to insert into the file
	int added = 0; //num of scores added so we don't go over 5 accidentally
	for( int i = 0; i < lines.size() && i < 10; i+= 2 )
	{
		//place to add the new name and score
		if( insert == i && added < 5 )
		{
			added++;
			fst << new_score << endl << name << endl;
		}
		//add all the old data (unless we're already at 5 scores)
		if( added < 5 )
		{
			added++;
			fst << lines[i] << endl << lines[i+1] << endl;
		}
	}
	//if insert == size() we "forgot" to add it to the end of the file in loop
	if( insert == lines.size() && added < 5 )
	{
		fst << new_score << endl << name << endl;
	}
}

};
