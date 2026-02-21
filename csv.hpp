#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;
class csv_loader
{
public:
    csv_loader(const string &filename);
    void show();
    void close();
    void readFile();

private:
    vector<vector<double>> table;
    ifstream file;
};