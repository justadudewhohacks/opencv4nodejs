
/**
 * Returns the number of ticks per second.
 * 
 * The function returns the number of ticks per second. That is, the following code computes the execution time in seconds:
 * 
 * https://docs.opencv.org/4.x/db/de0/group__core__utils.html#ga705441a9ef01f47acdc55d87fbe5090c
 */
export function getTickFrequency(): number;
 
/**
 * Returns the number of ticks.
 * 
 * The function returns the number of ticks after the certain event (for example, when the machine was turned on). It can be used to initialize RNG or to measure a function execution time by reading the tick count before and after the function call.
 * WARNING, return a int64, which can overflow nodejs number
 * 
 * https://docs.opencv.org/4.x/db/de0/group__core__utils.html#gae73f58000611a1af25dd36d496bf4487
 */
export function getTickCount(): number;

// int 	cv::getVersionMajor ()
//  	Returns major library version. More...
//  
// int 	cv::getVersionMinor ()
//  	Returns minor library version. More...
//  
// int 	cv::getVersionRevision ()
//  	Returns revision field of the library version. More...