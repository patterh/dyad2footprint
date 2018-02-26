//============================================================================
// Name        : dyad_to_footprint.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "main.h"

using namespace std;

int main() {
	int nucleosome_width = 146;
	HP_ReadTextFile* text_file = new HP_ReadTextFile();
	char* file_name = new char[1024];
	strcpy(file_name, "C:\\Users\\hpatterton\\Documents\\T_brucei\\427\\Genome_sequence\\kinetoplastid\\TRBKPGEN_dyads.txt");
	float* dyad_values;
	int number_of_dyads = text_file->ReadNucleosomeDyadFile(dyad_values, file_name);
	float* footprint_array = new float[number_of_dyads];
	float value;
	int minimum;
	int maximum;
	for(int x = 0; x < number_of_dyads; x++)
		{
		value = dyad_values[x];
		if(value > 0)
			{
			minimum = x-(nucleosome_width/2);
			minimum = minimum<0?0:minimum;
			maximum = x+(nucleosome_width/2);
			maximum = maximum>(number_of_dyads-1)?(number_of_dyads-1):maximum;
			for(int y = minimum; y <= maximum; y++)
				{
				footprint_array[y] = footprint_array[y]+value;
				}
			}
		}
	char* stripped_filename;
	char* out_filename = new char[1024];
	text_file->StripFileExtension(stripped_filename, file_name);
	strcpy(out_filename, stripped_filename);
	strcat(out_filename, "_footprint.txt");
	char* temp = new char[1024];
	fstream out_file;
	out_file.open(out_filename, fstream::out);
	for(int x = 0; x < number_of_dyads; x++)
		{
		sprintf(temp, "%f", footprint_array[x]);
		out_file << temp << endl;
		}
	out_file.close();

cout << "Written " << number_of_dyads << " values to " << out_filename << endl;

	delete [] temp;
	delete [] footprint_array;
	delete [] dyad_values;
	delete [] file_name;
	delete [] out_filename ;
	delete [] stripped_filename;

cout << "done." << endl;

return 0;
}
