import makeDrawUtils from './drawUtils';
import deprecations from './deprecations';
import * as OpenCV from '../..';
import misc from './misc';

export default function(cv: typeof OpenCV) {
  // add functions  
  makeDrawUtils(cv)
  // add functions  
  misc(cv);
  deprecations(cv);
  return cv;
}