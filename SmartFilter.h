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

#ifndef SMARTFILTER_H
#define SMARTFILTER_H

#include "Arduino.h"

class SmartFilter 
{
public:
    // Constructor
    SmartFilter();

    // Accepts raw value, returns filtered value
    double Filter( double rawValue );

private:
    // Data
    double * ffCoeff;
    double * fbCoeff;
    double * rawData;
    double * filtData;
    size_t currIndex;
  
    // Settings
    size_t order;
    size_t window;
    double learningRate;
    double weightCoeff;
  
    // Internal methods
    int IndexShift( int shift );
    void GetLossGradient( double * ffGrad, double * fbGrad );
    void GetVarGradient( double * ffGrad, double * fbGrad );
    void DoGradientDescent();
};



#endif
