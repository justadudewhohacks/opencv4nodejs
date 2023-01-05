import makeDrawUtils from './drawUtils.js';
import deprecations from './deprecations.js';
import * as OpenCV from '../..';
import misc from './misc.js';

export default function(cv: typeof OpenCV) {
  // add functions  
  makeDrawUtils(cv)
  // add functions  
  misc(cv);
  deprecations(cv);
  return cv;
}