#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class matrix_t {

    float ** data;
    unsigned int rows;
    unsigned int columns;

public:

    matrix_t const add(matrix_t const & other);
    matrix_t const sub(matrix_t const & other);
    matrix_t const mul(matrix_t const & other);
    matrix_t trans();
//    matrix_t void write();


    std::ifstream const & read(std::ifstream & stream);
    std::ostream & write(std::ostream & stream);

    matrix_t();
    ~matrix_t();
    matrix_t(matrix_t const & matrix);
    matrix_t & operator = (matrix_t const & matrix);

};

matrix_t::matrix_t() {
    data = nullptr;
    rows = 0;
    columns = 0;
}

matrix_t::~matrix_t() {
    for (unsigned int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

matrix_t::matrix_t(matrix_t const & matrix) {
    rows = matrix.rows;
    columns = matrix.columns;

    data = new float *[rows];
    for (unsigned int i = 0; i < rows; ++i) {
        data[i] = new float[columns];
        for (unsigned int j = 0; j < columns; ++j) {
            data[i][j] = matrix.data[i][j];
        }
    }
}

matrix_t & matrix_t::operator = (matrix_t const & matrix) {
if (this != &matrix) {
    for (unsigned int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;

    rows = matrix.rows;
    columns = matrix.columns;
    data = new float *[rows];
    for (unsigned int i = 0; i < rows; ++i) {
        data[i] = new float[columns];
    }
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < columns; ++j) {
            data[i][j] = matrix.data[i][j];
        }
    }
}

return *this;
}

const matrix_t matrix_t ::add(matrix_t const & other) {
    assert((columns == other.columns) && (rows == other.rows));

    matrix_t result;
    result.columns = columns;
    result.rows = rows;
    result.data = new float *[rows];
    for (unsigned int i = 0; i < rows; i++) {
        result.data[i] = new float [columns];
        for (unsigned int j = 0; j < columns; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

const matrix_t matrix_t::sub(matrix_t const & other) {
    assert((columns == other.columns) && (rows == other.rows));

    matrix_t result;
    result.columns = columns;
    result.rows = rows;
    result.data = new float *[rows];
    for (unsigned int i = 0; i < rows; i++) {
        result.data[i] = new float [columns];
        for (unsigned int j = 0; j < columns; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

const matrix_t matrix_t::mul(matrix_t const & other) {
    assert((columns == other.columns) && (rows == other.rows));

    matrix_t result;
    result.columns = columns;
    result.rows = rows;
    result.data = new float *[rows];
    for (unsigned int i = 0; i < rows; i++) {
        result.data[i] = new float [columns];
        for (unsigned int j = 0; j < columns; j++) {
            result.data[i][j] = 0.0f;
            for (unsigned int r = 0; r < columns; r++) {
                result.data[i][j] += data[i][r] * other.data[r][j];
            }
        }
    }
    return result;
}

matrix_t matrix_t::trans() {
    matrix_t result;
    result.columns = rows;
    result.rows = columns;
    result.data = new float *[result.rows];
    for (unsigned int i = 0; i < result.rows; i++) {
        result.data[i] = new float [result.columns];
        for (unsigned int j = 0; j < result.columns; j++) {
            result.data[i][j] = data[j][i];
        }
    }
    return result;
}

std::ifstream const & matrix_t::read(std::ifstream  & stream) {
        string s;
        int p;
        getline(stream, s);
        p = s.find(',');
        string s1 = s.substr(0,p);
        string s2 = s.substr(p+1,s.length()-p);
        rows = stoi(s1);
        columns = stoi(s2);
        data = new float *[ rows ];
        for( unsigned int i = 0; i < rows; ++i ) {
            data[ i ] = new float[ columns ];
            for( unsigned int j = 0; j < columns; ++j ) {
                data[ i ][ j ] = 0.0f;
                stream >> data[i][j];
            }
        }
    }


std::ostream& matrix_t::write(std::ostream & stream) {
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            if (j > 0) cout << ' ';
            stream << data[i][j];
        }
        stream << endl;
    }

}


int main()
{
    matrix_t inmatr1, inmatr2, outmatr, destroy;
    string str;
    getline(cin, str);
    int opcode = 0;
    int p = -1;

    for(int i = 0; i < str.length(); i++) {
        switch (str[i]) {
            case '+':
            case '-':
            case '*':
            case 'T':
                p = i;
                break;
        }

    }
    if (p > 0) {
        char symbol;
        string str1, str2;
        istringstream stream(str);
        stream >> str1 >> symbol;
        ifstream ifs1;
        ifs1.open("/root/" + str1);
        inmatr1.read(ifs1);
        ifs1.close();
        if (symbol == 'T') {
            outmatr = inmatr1.trans();
        }
        else {
            stream >> str2;
            ifstream ifs2;
            ifs2.open("/root/" + str2);
            inmatr2.read(ifs2);
            ifs2.close();

            switch (symbol) {
                case '+':
                    outmatr=inmatr1.add(inmatr2);
                    break;
                case '-':
                    outmatr=inmatr1.sub(inmatr2);
                    break;
                case '*':
                    outmatr=inmatr1.mul(inmatr2);
                    break;
            }
        }

       outmatr.write(cout);
    } else
        cout << "An error has occured while reading input data";

 //   destroy.~matrix_t();
    cin.get();
    return 0;
}
