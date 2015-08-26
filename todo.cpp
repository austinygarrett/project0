#include <iostream> 
#include <fstream>
#include <string>

using namespace std;
int todoLength = 0;

static int getLineCount(char* fname) {
	ifstream f(fname);
	string line;
	int i = 0;
	while (getline(f, line)) {
		i++;
	}
	return i;
}

static void add_cmd(char* fname, char* task) {
	ofstream f (fname, ios_base::app);
	
	if (f.is_open())
	{
		f << (todoLength + 1) << ":[ ] " << task <<endl;
		f.close();
	}
	else cout << "Unable to open file.\n" << endl;
}

static void list_cmd(char* fname) {
	ifstream f(fname);
	string line;
	while (getline(f, line)) {
		if (line[4] != 'x')
			cout << line << endl;
	}
	
	f.clear();
	f.seekg(0, ios::beg);
	
	while (getline(f, line)) {
		if (line[4] == 'x')
			cout << line << endl;
	}
}
//multi-digit handling
//create seperate completed and uncompleted files.. pull together into one list.
static void do_cmd(char* fname, char* tasknum) {
	fstream f;
	f.open(fname, fstream::in | fstream::out | fstream::app);
	string line;
	string l = to_string(todoLength);
	const char* s = l.c_str();
	string temp;
	if (f.is_open()) {
		
		for (int linenum = 0; getline(f, line); linenum++) {
			if (line[0] == s[0]) {
				line[0] = tasknum[0];
			}		
			if (line[0] == tasknum[0] && line[3] != 'x') {
				line[3] = 'x';
				line[0] = s[0];
				temp = line;
				cout << line[3] <<endl;
			}	
			f << line << endl;
		}
		f.close();
	}
	else 
		cout << "Unabled to open file." << endl;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " [-f file] command" << std::endl;
       
        return 1;
    }
	if (argv[1] == string("-f")) {
		todoLength = getLineCount(argv[2]);
		if (argv[3] == string("add")) {
			add_cmd(argv[2], argv[4]);
		}
		else if (argv[3] == string("list")) {
			list_cmd(argv[2]);
		}
		else if (argv[3] == string("do")) {
			do_cmd(argv[2], argv[4]);
		}
	}
	else {
		
		todoLength = getLineCount("todo.txt");

		if (argv[1] == string("add")) {
			add_cmd("todo.txt", argv[2]);
		}
		else if (argv[1] == string("list")) {
			list_cmd("todo.txt");
		}
		else if (argv[1] == string("do")) {
			do_cmd("todo.txt", argv[2]);
		}
	}
    return 0;
}
