#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define P         (double)(4)
#define P_POWER   (double)(4 * 4)
#define TMIN      (double)(0)
#define TMAX      (double)(1)
#define H_VALUE   (double)(0.01)

class Point
{
public:
  double t;
  double y;
  Point(double _t, double _y)
  {
    t = _t;
    y = _y;
  }
};

double f(double y, double x)
{
  return sin(20*y);
}


double runge_kutta(double t, double y, double h)
{
  double k1 = f(t,              y);
  double k2 = f(t + (h / 2),    y + ((h / 2) * k1));
  double k3 = f(t + (h / 2),    y + ((h / 2) * k2));
  double k4 = f(t + h,          y + (h * k3));

  return (y + h * (k1 + (2 * k2) + (2 * k3) + k4) / 6);
}

void plotChart(vector <Point*> points)
{
  ofstream file;
  file.open ("func.txt", ios::out);
  for(int ii = 0; ii < points.size(); ++ii)
  {
    file << points[ii]->t << " " << points[ii]->y << endl;
  }
  file.close();
  system("gnuplot < im");
}

int main(int argc, char* argv[])
{
  double x0, e, h0, c;
  vector <Point*> points;
  cin >> x0 >> e;
  h0 = H_VALUE;
  c = e;

  points.push_back(new Point(TMIN, x0));

  for(double tval = TMIN; tval < TMAX;)
  {
    if(tval + (h0 * 2) > TMAX)
    {
        h0 = (TMAX - tval) / 2;
    }
    double xk1 = runge_kutta(tval, points.back()->y, h0);
    double xk2 = runge_kutta(tval + h0, xk1, h0);
    double wk2 = runge_kutta(tval, points.back()->y, 2 * h0);
    double gamma = pow(((e * h0) / (TMAX - TMIN)) * ((P_POWER - 1) / fabs(wk2 - xk2)), (1 / P));
    double h1 = c * gamma * h0;

    if(h1 > 5 * h0)
    {
      h1 = 5 * h0;
    }
    else if(h1 < h0 / 5)
    {
      h1 = h0 / 5;
    }

    if(h1 < h0)
    {
      double part1 = (e * h0) / (TMAX - TMIN);
      double part2 = fabs(wk2 - xk2) / (P_POWER - 1);
      if(part1 >= part2)
      {
        points.push_back(new Point(tval + h0,      xk1));
        points.push_back(new Point(tval + 2 * h0,  xk2));
        tval += (h0 * 2);
      }
      else // part1 < part2
      {
        h0 = h1;
      }
    }
    else // h1 >= h0
    {
      points.push_back(new Point(tval + h0,      xk1));
      points.push_back(new Point(tval + 2 * h0,  xk2));
      tval += (h0 * 2);
      h0 = h1;
    }
  }

  plotChart(points);
}
