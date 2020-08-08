#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

// Everything showed up really nice on my computer so fingures crossed

int Nbox;
vector<vector<double> > potential;

double getV(int i, int j)
{
  return potential.at(j+Nbox).at(i+Nbox);
}

void setV(int i, int j, double value)
{
  potential.at(j+Nbox).at(i+Nbox) = value;
}

double trace()
{
  double sum=0;
  for(int j=-Nbox; j<=Nbox; j++)
  {
      sum = sum + pow(getV(j,j),2);
  }
  return sum;
}

int main(int argc, char** argv)
{
  double V, Delta, a, b, c=1.0, Ex, Ey;
  int Nplate, L, Lbox, NLplate, count=0;

  std::ifstream dataIn("params.txt");
  if(dataIn.is_open())
  {
    dataIn >> L;
    dataIn >> Lbox;
    dataIn >> Nplate;
  }
  else std::cout << "Error while opening the file" << std::endl;
  dataIn.close();

  Delta = 1./Nplate;
  NLplate = L*Nplate;
  Nbox = Lbox*Nplate;

  potential.resize(2*Nbox+1,vector<double>(2*Nbox+1,0));

  for(int i=-NLplate; i<=NLplate; i++)
  {
    setV(i,Nplate,1);
    setV(i,-Nplate,-1);
  }

  while(c > 0.001)
  {
    a = trace();
    for(int j=-Nbox+1; j<Nbox; j++)
    {
      for(int i=-Nbox+1; i<Nbox; i++)
      {
        if(!(abs(i) <= NLplate && abs(j) == Nplate))
        {
          V = 0.25*(getV(i+1,j) + getV(i-1,j) + getV(i,j+1) + getV(i,j-1));
          setV(i,j,V);
        }
      }
    }
    count = count + 1;
    cout << count << endl;
    b = trace();
    c = std::abs((b-a)/a);
  }

  std::ofstream sol("potential.txt");
  if(!sol.is_open())
  {
    cout << "sol stream failed to open!" << endl;
    return EXIT_FAILURE;
  }

  for(int j=-Nbox; j<=Nbox; j++)
  {
    for(int i=-Nbox; i<=Nbox; i++)
    {
        sol << i*Delta << '\t' << j*Delta << '\t' << getV(i,j) << endl;
    }
  }
  sol.close();

  std::ofstream Esol("efield.txt");
  if(!Esol.is_open())
  {
    cout << "Esol stream failed to open!" << endl;
    return EXIT_FAILURE;
  }

  for(int j=-Nbox+1; j<Nbox; j++)
  {
    for(int i=-Nbox+1; i<Nbox; i++)
    {
      Ex = -(getV(i+1,j)-getV(i-1,j))/(2*Delta);
      Ey = -(getV(i,j+1)-getV(i,j-1))/(2*Delta);
      Esol << i*Delta << '\t' << j*Delta << '\t' << Ex << '\t' << Ey << endl;
    }
  }
  Esol.close();

  return EXIT_SUCCESS;
}
