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
SmartFilter::SmartFilter() {
  curr_index = 0;

  order = 3;
  fb_coeff = new double[order];
  ff_coeff = new double[order];

  // Starting values
  fb_coeff[0] = 1.0;
  fb_coeff[1] = -1.98;
  fb_coeff[2] = 1.0;
  ff_coeff[0] = .005;
  ff_coeff[1] = .010;
  ff_coeff[2] = .005;

  // Data storage
  raw_data = new double[order]();
  filt_data = new double[order]();
}

// IIR filter
double SmartFilter::filter(double raw_value) {
  curr_index = indexShift(1);
  raw_data[curr_index] = raw_value;
  filt_data[curr_index] = 0;
  for (int i = 0; i < order; i++) {
    filt_data[curr_index] += raw_data[indexShift(-i)]*ff_coeff[i] - filt_data[indexShift(-i)]*fb_coeff[i];
  }
  return filt_data[curr_index];
}

// Index shifter helper method
int SmartFilter::indexShift(int shift) {
  int temp = curr_index + shift;
  if (0 <= temp && temp < order) {
    return temp;
  } else if (temp >= order) {
    return temp - order;
  } else {
    return temp + order;
  }
}
