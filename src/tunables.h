/*
 * ### TUNABLES ###
 */

#ifndef TUNABLES_H
#define TUNABLES_H

/*
 * Boxiness is the area of the fitted rectangle divided through
 * the area of the actual contour.
 * A low boxiness value (near 1.0) indicates a very box-like shape.
 * A high boxiness value (greater than 2.0) indicates a very chaotic
 * shape that we are not interested in.
 */
#define BOXINESS_CUTOFF_LO 1.18
#define BOXINESS_CUTOFF_HI 1.8
/*
 * The minimum area occupied by a possible mollusc.
 */
#define MINIMUM_AREA 1e5
/*
 * The minimum smoothnes required of a potential molluscoid shape.
 * A smoothness of 1.0 implies a shape without any convexity defects.
 */
#define CONTOUR_SMOOTHNESS_CUTOFF 1.08
/*
 * Perform thresholding on the image.
 * The threshold is determined by considering the image's histogram.
 */
#define THRESHOLD
/*
 * Constant added to the threshold prior to scaling, i.e. it should
 * lie in [0;1].
 */
#define THRESHOLD_BIAS 0.06
/*
 * Perform a single Gaussian blur prefiltering step.
 * NOTE: This is not known to noticeably improve contour detection
 * performance, however it is not known to harm either.
 */
#define PREFILTER_GAUSSIAN
/*
 * Perform just one morphological open/close operation using a
 * fixed structuring element.
 */
#define MORPH_SINGLE
/*
 * Perform n morphological open/close operations using structuring
 * elements of order [1;n).
 */
#define MORPH_MULTIPLE
/*
 * Number of open/close iterations to use with a fixed
 * structuring element.
 */
#define MORPH_SINGLE_OPEN_ITERATIONS 5
#define MORPH_SINGLE_CLOSE_ITERATIONS 0
/*
 * Number of buckets to use for the histogram as a power of two.
 */
#define HIST_BUCKETS 6

#endif
