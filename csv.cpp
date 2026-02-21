#include "csv.hpp"
csv_loader::csv_loader(const string &filename)
{
    ifstream file(filename);
}

void csv_loader::show()
{
    for (vector<double> x : table)
    {
        for (double y : x)
        {
            cout << y << endl;
        }
    }
}

void csv_loader::close()
{
    file.close();
}

void csv_loader::readFile()
{
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string value;
        vector<double> row;
        while (getline(ss, value, ','))
        {
            row.push_back(stod(value));
        }
        table.push_back(row);
    }
}
