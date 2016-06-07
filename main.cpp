/* to run build with the following source code files:
    SSS.cpp
*/

#include "SSS.hpp"

void read_from_file(vector<string>&, string);
void convert_to_int(string&, vector<int>&);

int main() {
	try {
	    vector<string> strElems;
		read_from_file(strElems, "p105_sets.txt");
		
		ofstream output_file("output_file.txt");
	    
		vector<int> intElems;
		int result = 0;
		for (int i = 0; i < strElems.size(); ++i) {
			convert_to_int(strElems[i], intElems);
			sort(intElems.begin(), intElems.end());
			SSS sss = SSS(intElems);
			if (sss.isSpecialSumSet()) {
				result += sss.sum();
				output_file << strElems[i];
				output_file << '\t';
				output_file << sss.sum();
				output_file << '\n';
			}
		}
		cout << result << endl;
	}
	catch (exception) {
		cerr << "error with 'main'";
	}
}

void read_from_file(vector<string>& strElems, string file_to_read) {
	try {
		// define file to read input data from
		ifstream sets(file_to_read);

		// store input data in a vector of strings
		while (!sets.eof()) {
			strElems.push_back("");
			getline(sets, strElems[strElems.size() - 1]);
	  	}
		sets.close();
	}
	catch (exception) {
		cerr << "error with 'read_from_file'";
	}
}

void convert_to_int(string& strElem, vector<int>& intElems) {
	try {
		intElems.clear();
		int e = 0, s = 0;
		while (s < strElem.size()) {
			while (strElem[s] != ',' && s < strElem.size()) {
				++s;
			}
			string substrElem = strElem.substr(e, s - e);
			intElems.push_back(stoi(substrElem));
			++s;
			e = s;
		}
	}
	catch (exception) {
		cerr << "error with 'convert_to_int'";
	}
}