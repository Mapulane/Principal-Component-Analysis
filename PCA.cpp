#include <iostream>
#include <exception>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

#include "values.hpp"
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

float XmeanValue(vector<float> Xvector, float observations){
  float xtotal,xm;
  for(float xdata : Xvector){
    xtotal +=xdata;
  }
   xm = (float)(xtotal/observations);
   return xm;
}

float YmeanValue(vector<float> Yvector,float observations){
  float ytotal,ym;
  for(float ydata : Yvector){
    ytotal +=ydata;
  }
    ym= (float)(ytotal/observations);
  return ym;

}

int main(){

  float observations = Xvalues.size();
  float variables = 2 ;

  //data is stored as the Xvalues and Yvalues vectors in the values.hpp file
  /*cout<<Xvalues.size()<< " and "<<Yvalues.size()  <<endl;
  for(float data : Xvalues){
    cout<<data<< " ";
  }*/

  // calculating the mean Xvalues and mean Yvalues
  float Xmean = XmeanValue(Xvalues, observations);
  float Ymean = YmeanValue(Yvalues, observations);

  //cout<< "The mean values: "<<Xmean <<" and "<< Ymean<<endl;

  //subtract mean from original data and calculate the covariance matrix
  float xxcov=0, yycov=0, xycov=0, yxcov=0;
  float x,y,z;


  for(int i=0; i<observations; i++){
    Xvalues[i] = Xvalues[i] - Xmean;
    Yvalues[i] = Yvalues[i] - Ymean;


    x=(Xvalues[i]* Xvalues[i]);
    xxcov += x;

    y = (Yvalues[i]* Yvalues[i]);
    yycov += y;

    z = (Xvalues[i]* Yvalues[i]);
    xycov += z;
  }
  xxcov = xxcov/(observations-1);
  yycov = yycov/(observations-1);
  xycov = xycov/(observations-1);
  yxcov = xycov;

  float totalCov = xxcov + yycov;


  //calcuting the eigenvectors, eigenvalue and the Principal components
  Matrix2d matrix;
  matrix << xxcov, xycov, yxcov, yycov;

  EigenSolver<MatrixXd> eigenThings(matrix);
  cout<< "The Eigenvalues for the principal components 1 and 2: "<<endl<<eigenThings.eigenvalues()<<endl<<endl;

  cout<< "The Eigenvectors for the principal components 1 and 2 in July and January: "<<endl<<eigenThings.eigenvectors()<<endl<<endl;

  cout<< "The covariance matrix is: "<<endl<<matrix<<endl<<endl;

  cout<< "The total variance is: " <<endl<<totalCov<<endl<<endl;

  float PC1=((eigenThings.eigenvalues()[0]).real()/totalCov);
  float PC2=((eigenThings.eigenvalues()[1]).real()/totalCov);

  cout<< "proportion (as a percentage) of total variance do principal components 1: "<<endl<<PC1*100<<"%"<<endl;
  cout<< "proportion (as a percentage) of total variance do principal components 2: "<<endl<<PC2*100<<"%"<<endl;


return 0;
}
