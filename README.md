SmartFilter
============
An Arduino library for intelligently filtering noisy data

_by: Devin Conley_

Using gradient descent to dynamically define the coefficients of an IIR filter

The error function weighs:
*Variance of filtered set
*Average squared difference between raw and filtered samples


**Need to improve stability of filter coefficients**