#include <vector>
#include <cmath>
#include <iostream>
#include "csv.cpp"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
class log_reg
{
public:
    vector<double> weights;
    double alpha = 0.0001;
    double lambda = 0.01;
    double bias = 0.01;
    vector<vector<double>> features;
    vector<vector<double>> features_test;
    vector<double> test;
    vector<double> actual;
    log_reg(vector<vector<double>> features) : features(features) {}
    void loss()
    {
        double res = 0.00, loss = 0.00;
        for (int row = 0; row < 20; row++)
        {
            loss = -(test[row] * log(sigmoid(prediction(row))) + (1 - test[row]) * log(1 - sigmoid(prediction(row))));
            res += loss;
        }
        res /= 20.00;
        cout << "loss : " << res << endl;
    }
    void train(int epochs)
    {
        for (vector<double> feature : features)
        {
            normalize(feature);
        }
        for (int i = 0; i < features.size(); i++)
        {
            weights.push_back(0.00);
        }
        for (int j = 0; j < epochs; j++)
        {
            cout << "epoch : " << j << "************************" << endl;
            for (int i = 0; i < features[0].size(); i++)
            {
                update_w(i);
                update_b(i);
            }
            loss();
        }
    }
    double sigmoid(double val)
    {
        return (1 / (1 + exp(-val)));
    }
    void update_w(int row)
    {
        int n = weights.size();
        double error = sigmoid(prediction(row)) - actual[row], w_upd;
        for (int i = 0; i < weights.size(); i++)
        {
            w_upd = 0.00;
            w_upd = error;
            w_upd *= features[i][row];
            w_upd += (lambda / n) * weights[i];
            weights[i] = weights[i] - (alpha * w_upd);
            // if (row % 50 == 0)
            // {
            //     cout << " i " << i << " =>  " << "weights : " << weights[i] << endl;
            // }
        }
    }
    void update_b(int row)
    {
        double error = 1 / (1 + exp(-prediction(row))) - actual[row], b_upd;
        b_upd = 0.00;
        b_upd = error;
        bias -= alpha * b_upd;
        // if (row % 50 == 0)
        // {
        //     cout << " i " << row << " => " << "bias : " << bias << endl;
        // }
    }

    double prediction(int row)
    {
        double pred = 0.00;
        for (int i = 0; i < weights.size(); i++)
        {
            pred += features[i][row] * weights[i];
        }
        return pred + bias;
    }
    double prediction_test(int row)
    {
        double pred = 0.00;
        for (int i = 0; i < weights.size(); i++)
        {
            pred += features_test[i][row] * weights[i];
        }
        return pred + bias;
    }

    void normalize(vector<double> column)
    {
        int n = column.size();
        double sum = 0.00, mean, std_dev, var = 0.00;
        for (double c : column)
        {
            sum += c;
        }
        mean = sum / n;
        for (int i = 0; i < n; i++)
        {
            var += pow(column[i] - mean, 2);
        }
        std_dev = sqrt(var / n) + 1e-9;
        for (double &col : column)
        {
            col = (col - mean) / std_dev;
        }
    }
};
void load_csv(const string &filename,
              vector<double> &x, vector<double> &y,
              vector<double> &f, vector<double> &f1,
              vector<double> &f2, vector<double> &f3,
              vector<double> &f4, vector<double> &f5,
              vector<double> &f6, vector<double> &f7,
              vector<double> &f8, vector<double> &f9,
              vector<double> &f10, vector<double> &f11)
{
    ifstream file(filename);
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;
        getline(ss, cell, ',');
        x.push_back(stod(cell));
        getline(ss, cell, ',');
        y.push_back(stod(cell));
        getline(ss, cell, ',');
        f.push_back(stod(cell));
        getline(ss, cell, ',');
        f1.push_back(stod(cell));
        getline(ss, cell, ',');
        f2.push_back(stod(cell));
        getline(ss, cell, ',');
        f3.push_back(stod(cell));
        getline(ss, cell, ',');
        f4.push_back(stod(cell));
        getline(ss, cell, ',');
        f5.push_back(stod(cell));
        getline(ss, cell, ',');
        f6.push_back(stod(cell));
        getline(ss, cell, ',');
        f7.push_back(stod(cell));
        getline(ss, cell, ',');
        f8.push_back(stod(cell));
        getline(ss, cell, ',');
        f9.push_back(stod(cell));
        getline(ss, cell, ',');
        f10.push_back(stod(cell));
        getline(ss, cell, ',');
        f11.push_back(stod(cell));
    }
}
vector<double> slice(vector<double> input)
{
    return {input.begin() + 50, input.begin() + 70};
}
int main()
{
    vector<double> f1;
    vector<double> f2;
    vector<double> f3;
    vector<double> f4;
    vector<double> f5;
    vector<double> f6;
    vector<double> f7;
    vector<double> f8;
    vector<double> f9;
    vector<double> f10;
    vector<double> f11;
    vector<double> f12;
    vector<double> f13;
    vector<double> f14;

    load_csv("Heart_Disease_Prediction.csv", f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14);
    vector<vector<double>> feat = {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13};
    log_reg l = log_reg(feat);
    l.actual = f14;

    l.features_test = {slice(f1), slice(f2), slice(f3), slice(f4), slice(f5), slice(f6), slice(f7), slice(f8), slice(f9), slice(f10), slice(f11), slice(f12), slice(f13)};
    l.test = slice(f14);

    l.train(100);
}