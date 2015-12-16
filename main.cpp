#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#define P (4)
#define P_POWER (4 * 4)
#define TMIN 0
#define TMAX 1

class Point
{
public:
  double x;
  double y;
  Point(double _x, double _y)
  {
    x = _x;
    y = _y;
  }
};

double f(double t, double y)
{
    return 1;
}


double runge_kutta(double t, double y, double h)
{
  double k1 = f(t,              y);
  double k2 = f(t + (h / 2),    y + ((h / 2) * k1));
  double k3 = f(t + (h / 2),    y + ((h / 2) * k2));
  double k4 = f(t + h,          y + (h * k3));

  return (y + (k1 + (2 * k2) + (2 * k3) + k4) / 6);
}

void plotChart()
{
  system("gnuplot < im");
}

int main(int argc, char* argv[])
{
  double x0, e, h;
  vector <Point*> points;
  cin >> x0 >> e;
  h = 0.1;

  points.push_back(new Point(TMIN, x0));

  for(double tval = x0; x0 < TMAX;)
  {

  }

  plotChart();
}
