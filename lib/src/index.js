const makeDrawUtils = require('./drawUtils')
const deprecations  = require('./deprecations')

module.exports = function(cv) {
  const {
    drawTextBox,
    drawDetection
  } = makeDrawUtils(cv)

  cv.drawTextBox = drawTextBox
  cv.drawDetection = drawDetection

  deprecations(cv)

  return cv
}