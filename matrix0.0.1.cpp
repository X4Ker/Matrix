#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool read_numbers(int a[3][3]) 
{
	bool success = true;
	for (int i = 0; i < 3 && success; ++i) {
		string string;
		getline(cin, string);
		istringstream stream(string);
		for (int j = 0; j < 3; ++j) {
			if (!(stream >> a[j][i])) {
				success = false;
				break;
			}
		}
	}

	return success;
}

int main() {
	int a[3][3];
	int b[3][3];
	int r[3][3];
	char p;

	if (read_numbers(a) && (cin >> p) && (cin.get()) && read_numbers(b)) {
		cout << endl;
		switch (p) {

		case '+':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					cout << a[i][j] + b[i][j];
					cout << " ";
				}
				cout << endl;
			}
			break;
		case '-':
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					cout << a[i][j] - b[i][j];
					cout << " ";
				}
				cout << endl;
			}
			break;
		case '*':
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					int result = 0;
					for (int k = 0; k < 3; ++k) {
						result += a[i][k] * b[k][j];
					}
					r[i][j] = result;
					cout << r[i][j];
					cout << " ";
				}
				cout << endl;
			}
			break;
		}

	}

	else {
		cout << "An error has occured while reading input data";
	}
	system("pause");
	return 0;
}
