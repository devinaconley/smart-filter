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

class SmartFilter {
 public:
  // Constructor
  SmartFilter();
  
  // Accepts raw value, returns filtered value
  double filter(double raw_value);

 private:
  // Privates...

}


#endif
