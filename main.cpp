#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> cells(30000, 0);
int cell = 0;
int line = 1;

int run(string v, size_t begin = 0)
{
	string buf;
	int counter;
	int new_i;

	int i;
	for (i = begin; i < (int)v.size(); i++)
	{
		// cout << v[i];
		if (v[i] == '+')
			cells[cell]++;
		else if (v[i] == '-')
			cells[cell]--;
		else if (v[i] == '>') {
			// cout << cell << ": " << cells[cell] << " (" << (char)cells[cell] << ")" << endl;
			cell++;
		} else if (v[i] == '<') {
			// cout << cell << ": " << cells[cell] << " (" << (char)cells[cell] << ")" << endl;
			cell--;
		} else if (v[i] == '.') {
			// cout << (char)cells[cell] << " " << cells[cell] << endl;
			cout << (char)cells[cell];
		}
		else if (v[i] == ',')
		{
			getline(cin, buf);
			cells[cell] = (int)buf[0];
		} else if (v[i] == '[')
		{
			counter = cell;
			i++;
			while (cells[counter] != 0) {
				new_i = run(v, i);
				if (new_i == (int)v.size() || new_i == -1) {
					return -1;
				}
			}

			i = new_i;
		} else if (v[i] == ']') {
			return i;
		} else if (v[i] == '\n')
			line++;
	}

	return i;
}

int main(int argc, char **argv)
{
	if (argc < 1) {
		cerr << "no file name" << endl;
		return -1;
	}

	ifstream file_in(argv[1]);
	string in;
	int ret;

	for (char c = file_in.get(); !file_in.eof(); c = file_in.get())
		in.push_back(c);

	ret = run(in);
	if (ret != (int)in.size()) {
		if (ret >= 0) {
			cerr << ret << ":" << line << " -- ";
		}
		cerr << "Unbalanced brackets" << endl;
	}

	return 0;
}
