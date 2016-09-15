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
  SmartFilter( int order = 2 );

  // Accepts raw value, returns filtered value
  double Filter( double rawValue );

 private:
  // Fields
  int order;
  double * ffCoeff;
  double * fbCoeff;
  double * rawData;
  double * filtData;
  int currIndex;
  
  // Internal methods
  int IndexShift( int shift );
  double ErrorFx();
  void DoGradientDescent();
};



#endif
