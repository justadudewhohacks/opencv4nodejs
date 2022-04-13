import makeDrawUtils from './drawUtils';
import deprecations from './deprecations';
import * as OpenCV from '../..';

export default function(cv: typeof OpenCV) {
  const {
    drawTextBox,
    drawDetection
  } = makeDrawUtils(cv)

  cv.drawTextBox = drawTextBox;
  cv.drawDetection = drawDetection;

  deprecations(cv);

  return cv;
}