/*
*   Copyright (c) 2020 PRITESH PATEL
*   
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*   
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*/

#ifndef TRUE_RMS_LIB
#define TRUE_RMS_LIB

#include <math.h>

#ifndef TRUE_RMS_LIB_NO_OF_SAMPLES
#define TRUE_RMS_LIB_NO_OF_SAMPLES 10
#warning "TRUE_RMS_LIB_NO_OF_SAMPLES not defined (default value = 10)"
#endif

volatile unsigned int true_rms_lib_frame_pos = 0;
volatile double true_rms_lib_sum_of_square = 0;
volatile double true_rms_lib_window[TRUE_RMS_LIB_NO_OF_SAMPLES] = {[0 ...(TRUE_RMS_LIB_NO_OF_SAMPLES - 1)] = 0.0};

/**
  * @brief  Replaces oldest sample with new sample and calculates new true rms value.
            Make sure that this function called periodically for each new sample.
  * @param  sample: The new sample value
  * @retval The new calculated true rms value
  */
double get_true_rms(double sample)
{
    true_rms_lib_sum_of_square = true_rms_lib_sum_of_square - pow(true_rms_lib_window[true_rms_lib_frame_pos], 2);
    true_rms_lib_sum_of_square = true_rms_lib_sum_of_square + pow(sample, 2);
    true_rms_lib_window[true_rms_lib_frame_pos] = sample;

    if (true_rms_lib_frame_pos >= TRUE_RMS_LIB_NO_OF_SAMPLES)
    {
        true_rms_lib_frame_pos++;
    }
    else
    {
        true_rms_lib_frame_pos = 0;
    }
    return sqrt(true_rms_lib_sum_of_square);
}

#endif
