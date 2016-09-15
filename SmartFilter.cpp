/*
  ============================================================================================
  Smart Filter is an Arduino library that automatically configures itself to your data.
  --------------------------------------------------------------------------------------------

  --------------------------------------------------------------------------------------------
  SmartFilter
  v0.0.0
  http://...
  by Devin Conley
  ============================================================================================
 */

#include "SmartFilter.h"

// Constructor
SmartFilter::SmartFilter(int order /* = 3 */ ) : order( order ) 
{
  currIndex = 0;

  fbCoeff = new double[order + 1];
  ffCoeff = new double[order + 1];

  // Starting values
  fbCoeff[0] = 1.0;
  fbCoeff[1] = -1.98;
  fbCoeff[2] = 1.0;
  ffCoeff[0] = .005;
  ffCoeff[1] = .010;
  ffCoeff[2] = .005;

  // Data storage
  rawData = new double[order + 1]();
  filtData = new double[order + 1]();
}

// IIR filter
double SmartFilter::Filter( double rawValue )
{
  currIndex = IndexShift(1);

  rawData[currIndex] = rawValue;

  filtData[currIndex] = 0;

  for ( int i = 0; i < order + 1; ++i )
    {
      filtData[currIndex] += rawData[IndexShift(-i)]*ffCoeff[i] - 
	filtData[IndexShift(-i)]*fbCoeff[i];
    }

  DoGradientDescent();
  
  return filtData[currIndex];
}

// Index shifter helper method
int SmartFilter::IndexShift(int shift) {
  int sz = order + 1;
  int temp = currIndex + shift;
  if ( 0 <= temp && temp < sz )
    {
      return temp;
    } 
  else if ( temp >= sz ) 
    {
      return temp - sz;
    } 
  else 
    {
      return temp + sz;
    }
}

// Error Function
double SmartFilter::ErrorFx()
{
 double yMean = 0;
  for ( int i = 0; i < order + 1; ++i )
    {
      yMean += filtData[i];
    }
  yMean /= ( order + 1 );
  
  // Sum 2*(y_i - x_i)
  double sumDiff = 0;
  for ( int i = 0; i < order + 1; ++i )
    {
      sumDiff += 2*( filtData[i] - rawData[i] );
    }

  // Sum 2*(y_i - y_mean)
  double sumVarD = 0;
  for ( int i = 0; i < order + 1; ++i )
    {
      sumVarD += 2*( filtData[i] - yMean );
    }
  
  double c = 0.8; // weighting coefficient

  return ( c * sumDiff + (1-c) * sumVarD );
}

// Do gradient descent
void SmartFilter::DoGradientDescent()
{
  double error =  ErrorFx();
  double learnCoeff = 0.000001;

  for ( int i = 0; i < order + 1; ++i )
    {
      ffCoeff[i] -= learnCoeff * ffCoeff[i] * error;
      fbCoeff[i] -= learnCoeff * fbCoeff[i] * error;
    }
}
