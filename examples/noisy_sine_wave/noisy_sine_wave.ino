/*                                                                                                                  
  ===========================================================================================                       
  Example to demonstrate use SmartFilter on intentionally noisy data                                                
  -------------------------------------------------------------------------------------------                       
  SmartFilter                                                                                                       
  v0.0.0                                                                                                            
  https://github.com/devinconley/SmartFilter                                                                        
  by Devin Conley                                                                                                   
  ===========================================================================================                       
*/

#include "Plotter.h"
#include "SmartFilter.h"

// Globals                                                                                                          
Plotter p;
SmartFilter sf;
double raw;
double filtered;

void setup() {
  p = Plotter();
  p.addTimeGraph("SmartFilter Demo", 1000, "Raw data", &raw, "Filtered data", &filtered);
  sf = SmartFilter();
}

void loop() {
  // Update with abitrary sine data that we add intentional noise to
  raw = 10.0*sin( (millis()/5000.0) * (2.0*M_PI) );
  raw += random(-100, 100)/100.0;

  // Filter with SmartFilter
  filtered = sf.filter(raw);
  
  // Plot both for comparison
  p.plot();
}