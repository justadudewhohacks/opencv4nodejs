const makeDrawUtils = require('./drawUtils')

module.exports = function(cv) {
  const {
    drawTextBox,
    drawDetection
  } = makeDrawUtils(cv)

  cv.drawTextBox = drawTextBox
  cv.drawDetection = drawDetection
  return cv
}