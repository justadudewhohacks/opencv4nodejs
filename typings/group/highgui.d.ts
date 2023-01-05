import { Mat } from '../Mat';

// int 	cv::createTrackbar (const String &trackbarname, const String &winname, int *value, int count, TrackbarCallback onChange=0, void *userdata=0)
//  	Creates a trackbar and attaches it to the specified window. More...
//  
// void 	cv::destroyAllWindows ()
//  	Destroys all of the HighGUI windows. More...
export function destroyAllWindows(): void;

// void 	cv::destroyWindow (const String &winname)
//  	Destroys the specified window. More...
export function destroyWindow(winName: string): void;

// int 	cv::getMouseWheelDelta (int flags)
//  	Gets the mouse-wheel motion delta, when handling mouse-wheel events cv::EVENT_MOUSEWHEEL and cv::EVENT_MOUSEHWHEEL. More...
//  
// int 	cv::getTrackbarPos (const String &trackbarname, const String &winname)
//  	Returns the trackbar position. More...
//  
// Rect 	cv::getWindowImageRect (const String &winname)
//  	Provides rectangle of image in the window. More...
//  
// double 	cv::getWindowProperty (const String &winname, int prop_id)
//  	Provides parameters of a window. More...
export function setWindowProperty(winName: string, prop_id: number, prop_value: number): void;
export function getWindowProperty(winName: string, prop_id: number): number;

// void 	cv::imshow (const String &winname, InputArray mat)
//  	Displays an image in the specified window. More...
/**
 * Displays an image in the specified window.
 * @param winName Name of the window.
 * @param img Image to be shown.
 */
 export function imshow(winName: string, img: Mat): void;

// void 	cv::moveWindow (const String &winname, int x, int y)
//  	Moves the window to the specified position. More...
/**
 * Moves the window to the specified position.
 * https://docs.opencv.org/3.4/d7/dfc/group__highgui.html#ga8d86b207f7211250dbe6e28f76307ffb
 * @param winname	Name of the window.
 * @param x	The new x-coordinate of the window.
 * @param y	The new y-coordinate of the window.
 */
export 	function moveWindow(winname: string, x: number, y: number): void;
//  
/**
 * Creates a window.
 * 
 * The function namedWindow creates a window that can be used as a placeholder for images and trackbars. Created windows are referred to by their names.
 * If a window with the same name already exists, the function does nothing.
 * 
 * https://docs.opencv.org/4.x/d7/dfc/group__highgui.html#ga5afdf8410934fd099df85c75b2e0888b
 * 
 * @param winname Name of the window in the window caption that may be used as a window identifier. default: cv.WINDOW_AUTOSIZE
 * @param flags Flags of the window. The supported flags are: (cv::WindowFlags)
 */
export 	function namedWindow(winname: string, flags?: number): void;


// int 	cv::pollKey ()
//  	Polls for a pressed key. More...

/**
 * Resize a window.
 * https://docs.opencv.org/4.0.0/d7/dfc/group__highgui.html#gab4e70200bf54be967129cf08ac5e18bc
 * @param winname	Name of the window.
 * @param width	The new width of the window.
 * @param height	The new height of the window.
 */
 export 	function resizeWindow(winname: string, width: number, height: number): void;

/**
 * Start a background thread that services windows events and updates
 * without relying on waitKey(), e.g., imshow().
 * @returns The return value;
 */
export function startWindowThread(): number;

// Rect 	cv::selectROI (const String &windowName, InputArray img, bool showCrosshair=true, bool fromCenter=false)
//  	Allows users to select a ROI on the given image. More...
//  
// Rect 	cv::selectROI (InputArray img, bool showCrosshair=true, bool fromCenter=false)
//  
// void 	cv::selectROIs (const String &windowName, InputArray img, std::vector< Rect > &boundingBoxes, bool showCrosshair=true, bool fromCenter=false)
//  	Allows users to select multiple ROIs on the given image. More...
//  
// void 	cv::setMouseCallback (const String &winname, MouseCallback onMouse, void *userdata=0)
//  	Sets mouse handler for the specified window. More...
//  
// void 	cv::setTrackbarMax (const String &trackbarname, const String &winname, int maxval)
//  	Sets the trackbar maximum position. More...
//  
// void 	cv::setTrackbarMin (const String &trackbarname, const String &winname, int minval)
//  	Sets the trackbar minimum position. More...
//  
// void 	cv::setTrackbarPos (const String &trackbarname, const String &winname, int pos)
//  	Sets the trackbar position. More...
//  
// void 	cv::setWindowProperty (const String &winname, int prop_id, double prop_value)
//  	Changes parameters of a window dynamically. More...
//  
// void 	cv::setWindowTitle (const String &winname, const String &title)
//  	Updates window title. More...
export function setWindowTitle(winName: string, title: string): void;

// int 	cv::waitKey (int delay=0)
//  	Waits for a pressed key. More...
export function waitKey(delay?: number): number;

// int 	cv::waitKeyEx (int delay=0)
//  	Similar to waitKey, but returns full key code. More...
export function waitKeyEx(delay?: number): number;
