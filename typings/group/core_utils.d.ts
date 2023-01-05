
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

/**
 * Returns major library version.
 * https://docs.opencv.org/4.x/db/de0/group__core__utils.html#gaebca81a0853cd9dff3d6fd88dad25ad0
 * @since 3.4.2
 */
export function getVersionMajor(): number;

/**
 * Returns minor library version.
 * https://docs.opencv.org/4.x/db/de0/group__core__utils.html#gaf76d1e4fd9562ae058abfea4891b8b0d
 * @since 3.4.2
 */
export function getVersionMinor(): number;

/**
* Returns revision field of the library version.
* https://docs.opencv.org/4.x/db/de0/group__core__utils.html#ga2d7ae9f1e3fb51d5a62c5cde4626bfcd
* @since 3.4.2
*/
export function getVersionRevision(): number;
