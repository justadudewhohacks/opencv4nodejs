import makeDrawUtils from './drawUtils';
import deprecations from './deprecations';
import * as OpenCV from '../..';
import misc from './misc';

export default function(cv: typeof OpenCV) {
  const {
    drawTextBox,
    drawDetection
  } = makeDrawUtils(cv)

  cv.drawTextBox = drawTextBox;
  cv.drawDetection = drawDetection;

  const { toMatTypeName } = misc(cv);
  cv.toMatTypeName = toMatTypeName;

  deprecations(cv);
  
  return cv;
}