import makeDrawUtils from './drawUtils'
import deprecations from './deprecations'

export default function(cv) {
  const {
    drawTextBox,
    drawDetection
  } = makeDrawUtils(cv)

  cv.drawTextBox = drawTextBox
  cv.drawDetection = drawDetection

  deprecations(cv)

  return cv
}