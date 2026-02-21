#include <vector>
#include <cmath>
#include <iostream>
#include "csv.cpp"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
class lg
{
public:
    vector<double> x, x1, actual;
    vector<double> weights;
    vector<vector<double>> features;
    double bias = 0.01;
    double w1 = 0.01;
    double w2 = 0.01;
    double b = 0.00;
    double alpha = 0.0001;
    double lambda = 0.1;
    lg(vector<double> x_in, vector<double> x1_in, vector<double> y_in) : x(x_in), actual(y_in), x1(x1_in) {}
    double prediction(int row)
    {
        double pred;
        for (int i = 0; i < weights.size(); i++)
        {
            pred = weights[i] * features[row][i];
        }
        return pred + bias;
    }
    void grad_w(int row)
    {
        int w_size = weights.size();
        double error = 0.00, w_upd;
        double pred = prediction(row);
        error = pred - actual[row];
        for (int i = 0; i < w_size; i++)
        {
            w_upd = 0.00;
            w_upd = error;
            w_upd *= features[row][i];
            w_upd *= (2.0 / w_size);
            w_upd += (lambda / w_size) * weights[i]; // regularization
            weights[i] = weights[i] - (alpha * w_upd);
        }
    }
    void grad_b(int row)
    {
        double error = 0.00, b_upd = 0.00;
        double pred = prediction(row);
        error = pred - actual[row];
        b_upd = error;
        b_upd *= 2.0 / weights.size();
        b_upd += (lambda / weights.size()) * bias;
        bias = bias - (alpha * b_upd);
    }
    void train_test(int cal)
    {
        for (vector<double> &row : features)
        {
            row = normalize(row);
        }
        for (int i = 0; i < features.size(); i++)
        {
            weights.push_back(0.00);
        }
        changegrad();
    }
    void changegrad()
    {

        for (int i = 0; i < features[0].size(); i++)
        {
            grad_w(i);
            grad_b(i);
            cout << "*******" << " i : " << i << endl;
            for (double w : weights)
            {
                cout << w << endl;
            }
            cout << "b : " << bias << endl;
        }
    }
    void train(int epochs)
    {
        x = normalize(x);
        x1 = normalize(x1);
        actual = normalize(actual);
        for (int i = 0; i < epochs; i++)
        {
            double dw1 = 0.00, db = 0.00, dw2 = 0.00;
            int n = x.size();
            for (int j = 0; j < n; j++)
            {
                double prediction = (w1 * x[j]) + (w2 * x1[j]) + b;
                double error = prediction - actual[j];
                dw1 += error * x[j];
                dw2 += error * x1[j];
                db += error;
            }
            dw1 = (2.0 / n) * dw1;
            dw2 = (2.0 / n) * dw2;
            db = (2.0 / n) * db;
            dw1 += (lambda / n) * (w1);
            dw2 += (lambda / n) * (w2);
            db += (lambda / n) * (b);
            double next_w = w1 - (alpha * dw1);
            double next_w2 = w2 - (alpha * dw2);
            double next_b = b - (alpha * db);
            w1 = next_w;
            w2 = next_w2;
            b = next_b;
            cout << "epoch " << i << " w1 " << w1 << " w2 " << w2 << " b: " << b << endl;
        }
    }
    void evaluate(vector<double> test, vector<double> test1, vector<double> y)
    {
        double pred, ss_res = 0, ss_tot = 0, mean = 0;
        for (int j = 0; j < test.size(); j++)
        {
            pred = test[j] * w1 + test[j] * w2 + b;
            ss_res += (y[j] - pred) * (y[j] - pred);
            mean += y[j];
        }
        mean /= test.size();
        for (double val : y)
        {
            ss_tot += (val - mean) * (val - mean);
        }
        cout << 1 - (ss_res / ss_tot);
    }
    vector<double> normalize(vector<double> val)
    {
        int n = val.size();
        double sum = 0, mean, stan_dev;
        for (int i = 0; i < n; i++)
        {
            sum += val[i];
        }
        mean = sum / n;
        double var = 0.00;
        for (int i = 0; i < n; i++)
        {
            var += pow(val[i] - mean, 2);
        }
        stan_dev = sqrt(var / n) + 1e-9;
        for (double &value : val)
        {
            value = (value - mean) / stan_dev;
        }
        return val;
    }
};
void load_csv(const string &filename, vector<double> &x, vector<double> &y)
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
    }
}

int main()
{
    vector<double> x, y;
    load_csv("test.csv", x, y);

    vector<double> x1 = x;
    sort(x1.begin(), x1.end());
    lg l = lg(x, x1, y);

    l.features = {x, x1, x1};
    l.train_test(100);

    l.train(100000);
    l.evaluate({80, 37, 54, 56}, {37, 54, 56, 80}, {79.44769523, 40.03504862, 53.32005764, 54.55446979});
}