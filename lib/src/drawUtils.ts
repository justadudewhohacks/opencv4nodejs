// import { cv as OpenCV } from '../..';
import * as openCV from '../..';

export default function(cv: typeof openCV) {
  function reshapeRectAtBorders(rect, imgDim) {
    const newX = Math.min(Math.max(0, rect.x), imgDim.cols)
    const newY = Math.min(Math.max(0, rect.y), imgDim.rows)
    return new cv.Rect(
      newX,
      newY,
      Math.min(rect.width, imgDim.cols - newX),
      Math.min(rect.height, imgDim.rows - newY)
    )
  }

  function getDefaultTextParams() {
    return ({
      fontType: cv.FONT_HERSHEY_SIMPLEX,
      fontSize: 0.8,
      thickness: 2,
      lineType: cv.LINE_4
    })
  }

  function insertText(boxImg: openCV.Mat, text: string, { x, y }, opts) {
    const {
      fontType,
      fontSize,
      color,
      thickness,
      lineType
    } = Object.assign(
      {},
      getDefaultTextParams(),
      { color: new cv.Vec3(255, 255, 255) },
      opts
    )

    boxImg.putText(
      text,
      new cv.Point2(x, y),
      fontType,
      fontSize,
      color,
      thickness,
      lineType,
      0
    )
    return boxImg
  }

  function getTextSize(text: string, opts) {
    const {
      fontType,
      fontSize,
      thickness
    } = Object.assign({}, getDefaultTextParams(), opts)

    const { size, baseLine } = cv.getTextSize(text, fontType, fontSize, thickness)
    return { width: size.width, height: size.height, baseLine }
  }

  function getMaxWidth(textLines) {
    const getTextWidth = (text, opts) => getTextSize(text, opts).width
    return textLines.reduce((maxWidth, t) => {
      const w = getTextWidth(t.text, t)
      return (maxWidth < w ? w : maxWidth)
    }, 0)
  }

  function getBaseLine(textLine) {
    return getTextSize(textLine.text, textLine).baseLine
  }

  function getLineHeight(textLine) {
    return getTextSize(textLine.text, textLine).height
  }

  function getTextHeight(textLines) {
    return textLines.reduce(
      (height: number, t) => height + getLineHeight(t),
      0
    )
  }

  function drawTextBox(img, upperLeft, textLines, alpha) {
    const padding = 10
    const linePadding = 10

    const { x, y } = upperLeft
    const rect = reshapeRectAtBorders(
      new cv.Rect(
        x,
        y,
        getMaxWidth(textLines) + (2 * padding),
        getTextHeight(textLines) + (2 * padding) + ((textLines.length - 1) * linePadding)
      ),
      img
    )

    const boxImg = img.getRegion(rect).mul(alpha)
    let pt = new cv.Point2(padding, padding)
    textLines.forEach(
      (textLine, lineNumber) => {
        const opts = Object.assign(
          {},
          getDefaultTextParams(),
          textLine
        )

        pt = pt.add(new cv.Point2(0, getLineHeight(textLine)))

        insertText(
          boxImg,
          textLine.text,
          pt,
          opts
        )

        pt = pt.add(new cv.Point2(0, linePadding))
      }
    )
    boxImg.copyTo(img.getRegion(rect))
    return img
  }

  function drawDetection(img, inputRect, opts = {} as any) {
    const rect = inputRect.toSquare()

    const { x, y, width, height } = rect

    const segmentLength = width / (opts.segmentFraction || 6);
    const upperLeft = new cv.Point2(x, y)
    const bottomLeft = new cv.Point2(x, y + height)
    const upperRight = new cv.Point2(x + width, y)
    const bottomRight = new cv.Point2(x + width, y + height)

    const drawParams = Object.assign(
      {},
      { thickness: 2 },
      opts
    )

    img.drawLine(
      upperLeft,
      upperLeft.add(new cv.Point2(0, segmentLength)),
      drawParams
    )
    img.drawLine(
      upperLeft,
      upperLeft.add(new cv.Point2(segmentLength, 0)),
      drawParams
    )

    img.drawLine(
      bottomLeft,
      bottomLeft.add(new cv.Point2(0, -segmentLength)),
      drawParams
    )
    img.drawLine(
      bottomLeft,
      bottomLeft.add(new cv.Point2(segmentLength, 0)),
      drawParams
    )

    img.drawLine(
      upperRight,
      upperRight.add(new cv.Point2(0, segmentLength)),
      drawParams
    )
    img.drawLine(
      upperRight,
      upperRight.add(new cv.Point2(-segmentLength, 0)),
      drawParams
    )

    img.drawLine(
      bottomRight,
      bottomRight.add(new cv.Point2(0, -segmentLength)),
      drawParams
    )
    img.drawLine(
      bottomRight,
      bottomRight.add(new cv.Point2(-segmentLength, 0)),
      drawParams
    )
    return rect
  }

  return ({
    drawTextBox,
    drawDetection
  })

}