#pragma once

namespace Score_IO
{
static const string SCORE_FILE = "scores.txt";

//whatever happened to Java's good ol' String_Tokenizer?? :(
vector<string> read_lines()
{
	vector<string> v;
	fstream file( SCORE_FILE.c_str(), ios_base::in );
	if( !file.is_open() ) return v;
	string line;
	while( !file.eof() )
	{
		getline( file, line );
		if( line != "" )
			v.push_back( line );
	}
	return v;
}

vector<string> top_scores()
{
	vector<string> v;
	vector<string> lines = read_lines();
	for( int i = 0; i < lines.size(); i+= 2 )
	{
		stringstream ss;
		ss << setw(30) << left << lines[i+1] << lines[i];
		v.push_back( ss.str() );
	}
	return v;
}

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
		// <= so the new score will be at the top (to make users happy)
		if( atoi( lines[insert].c_str() ) <= new_score )
			break;
	}
	//now insert is the place where we want to insert into the file
	cout << "lines size " << lines.size() << " " << insert << endl;
	int added = 0;
	for( int i = 0; i < lines.size() && i < 10; i+= 2 )
	{
		cout << "|" << insert << " " << i << " ";
		if( insert == i && added < 5 )
		{
			added++;
			fst << new_score << endl << name << endl;
		}
		//check if i != 8 so we don't add two entries even though we're on the
		//fifth and final score to add to the file already
		//OR if we're going to add another score to the end
		if( added < 5 )
		{
			cout << "a";
			added++;
			fst << lines[i] << endl << lines[i+1] << endl;
		}
		cout << "|";
	}
	//if insert == lines.size() we "forgot" to add it to the end of the file
	if( insert == lines.size() && added < 5 )
	{
		cout << " adding to end ";
		fst << new_score << endl << name << endl;
	}
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
