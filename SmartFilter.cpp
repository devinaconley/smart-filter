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
SmartFilter::SmartFilter() :
    order( 2 ), learningRate( 0.0005 ), weightCoeff( 0.2 )
{
    window = 2 * ( order + 1 );
    
    currIndex = 0;
    
    fbCoeff = new double[order + 1];
    ffCoeff = new double[order + 1];

    // Starting values
    fbCoeff[0] = 1.0;
    fbCoeff[1] = -1.4;
    fbCoeff[2] = 0.50;

    ffCoeff[0] = 0.20;
    ffCoeff[1] = -0.30;
    ffCoeff[2] = 0.20;
    
    // Data storage
    rawData = new double[window]();
    filtData = new double[window]();
}

// IIR filter
double SmartFilter::Filter( double rawValue )
{
    currIndex = IndexShift( 1 );

    rawData[currIndex] = rawValue;

    filtData[currIndex] = 0;
    for ( size_t i = 0; i < order + 1; ++i )
    {
	filtData[currIndex] += rawData[IndexShift(-i)]*ffCoeff[i] - filtData[IndexShift(-i)]*fbCoeff[i];
    }

    DoGradientDescent();
    
    return filtData[currIndex];
}
    

// Index shifter helper method
int SmartFilter::IndexShift( int shift )
{
    int sz = window;
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

// Gradient from error due to signal loss
void SmartFilter::GetLossGradient( double * ffGrad, double * fbGrad )
{
    for ( size_t i = 0; i < order + 1; ++i )
    {
	ffGrad[i] = 0;
	fbGrad[i] = 0;
    }
    for ( size_t i = 0; i < order + 1; ++i )
    {
	double temp = ( 2.0 / double( order+1 ) ) * ( filtData[IndexShift( -i )] - rawData[IndexShift( -i )] );

	for ( size_t j = 0; j < order + 1; ++j )
	{
	    ffGrad[j] += temp*rawData[IndexShift( -j )];
	    if ( j != 0 )
	    {
		fbGrad[j] -= temp*filtData[IndexShift( -j )];
	    }
	}
    }

}

void SmartFilter::GetVarGradient( double * ffGrad, double * fbGrad )
{}

// Do gradient descent
void SmartFilter::DoGradientDescent()
{
    // Get gradient from signal loss error
    double * ffDiffGrad = new double[order+1]();
    double * fbDiffGrad = new double[order+1]();
    GetLossGradient( ffDiffGrad, fbDiffGrad );
    
    for ( size_t i = 0; i < order + 1; ++i )
    {	
	ffCoeff[i] -= learningRate * ffDiffGrad[i];
	if ( i != 0 )
	{	    
	    fbCoeff[i] -= learningRate * fbDiffGrad[i];
	}
    }
    
    delete[] ffDiffGrad;
    delete[] fbDiffGrad;
}
