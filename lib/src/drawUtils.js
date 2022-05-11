"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
function default_1(cv) {
    const DefaultTextParams = { fontType: cv.FONT_HERSHEY_SIMPLEX, fontSize: 0.8, thickness: 2, lineType: cv.LINE_4 };
    function reshapeRectAtBorders(rect, imgDim) {
        const x = Math.min(Math.max(0, rect.x), imgDim.cols);
        const y = Math.min(Math.max(0, rect.y), imgDim.rows);
        const width = Math.min(rect.width, imgDim.cols - x);
        const height = Math.min(rect.height, imgDim.rows - y);
        return new cv.Rect(x, y, width, height);
    }
    function insertText(boxImg, text, origin, opts) {
        const fontType = opts.fontType || DefaultTextParams.fontType;
        const fontSize = opts.fontSize || DefaultTextParams.fontSize;
        const color = opts.color || new cv.Vec3(255, 255, 255);
        const thickness = opts.thickness || DefaultTextParams.thickness;
        const lineType = opts.lineType || DefaultTextParams.lineType;
        const originPt = new cv.Point2(origin.x, origin.y);
        boxImg.putText(text, originPt, fontType, fontSize, color, thickness, lineType, 0);
        return boxImg;
    }
    /**
     * get text block contour
     */
    function getTextSize(text, opts) {
        opts = opts || {};
        const fontType = opts.fontSize || DefaultTextParams.fontType;
        const fontSize = opts.fontSize || DefaultTextParams.fontSize;
        const thickness = opts.thickness || DefaultTextParams.thickness;
        const { size, baseLine } = cv.getTextSize(text, fontType, fontSize, thickness);
        return { width: size.width, height: size.height, baseLine };
    }
    /**
    * get text block width in pixel
    * @param textLines lined to write
    * @param opts draw params
    * @returns text total width
    */
    function getMaxWidth(textLines, opts) {
        const getTextWidth = (text, opts) => getTextSize(text, opts).width;
        return textLines.reduce((maxWidth, textLine) => {
            const w = getTextWidth(textLine.text, opts);
            return (maxWidth < w ? w : maxWidth);
        }, 0);
    }
    // function getBaseLine(textLine: TextLines, opts?: Partial<TextParams>): number {
    //   return getTextSize(textLine.text, opts).baseLine
    // }
    /**
     * get single text line height in pixel
     * @param textLine line to write
     * @param opts draw params
     * @returns text total height
     */
    function getLineHeight(textLine, opts) {
        return getTextSize(textLine.text, opts).height;
    }
    /**
     * get text block height in pixel
     * @param textLines lined to write
     * @param opts draw params
     * @returns text total height
     */
    function getTextHeight(textLines, opts) {
        return textLines.reduce((height, textLine) => height + getLineHeight(textLine, opts), 0);
    }
    cv.drawTextBox = (img, upperLeft, textLines, alpha) => {
        const padding = 10;
        const linePadding = 10;
        const { x, y } = upperLeft;
        const width = getMaxWidth(textLines) + (2 * padding);
        const height = getTextHeight(textLines) + (2 * padding) + ((textLines.length - 1) * linePadding);
        const rect = reshapeRectAtBorders(new cv.Rect(x, y, width, height), img);
        const boxImg = img.getRegion(rect).mul(alpha);
        let pt = new cv.Point2(padding, padding);
        textLines.forEach((textLine /*, lineNumber*/) => {
            const opts = Object.assign({}, DefaultTextParams, textLine);
            pt = pt.add(new cv.Point2(0, getLineHeight(textLine)));
            insertText(boxImg, textLine.text, pt, opts);
            pt = pt.add(new cv.Point2(0, linePadding));
        });
        boxImg.copyTo(img.getRegion(rect));
        return img;
    };
    cv.drawDetection = (img, inputRect, opts = {}) => {
        const rect = inputRect.toSquare();
        const { x, y, width, height } = rect;
        const segmentLength = width / (opts.segmentFraction || 6);
        const upperLeft = new cv.Point2(x, y);
        const bottomLeft = new cv.Point2(x, y + height);
        const upperRight = new cv.Point2(x + width, y);
        const bottomRight = new cv.Point2(x + width, y + height);
        const drawParams = Object.assign({ thickness: 2 }, opts);
        img.drawLine(upperLeft, upperLeft.add(new cv.Point2(0, segmentLength)), drawParams);
        img.drawLine(upperLeft, upperLeft.add(new cv.Point2(segmentLength, 0)), drawParams);
        img.drawLine(bottomLeft, bottomLeft.add(new cv.Point2(0, -segmentLength)), drawParams);
        img.drawLine(bottomLeft, bottomLeft.add(new cv.Point2(segmentLength, 0)), drawParams);
        img.drawLine(upperRight, upperRight.add(new cv.Point2(0, segmentLength)), drawParams);
        img.drawLine(upperRight, upperRight.add(new cv.Point2(-segmentLength, 0)), drawParams);
        img.drawLine(bottomRight, bottomRight.add(new cv.Point2(0, -segmentLength)), drawParams);
        img.drawLine(bottomRight, bottomRight.add(new cv.Point2(-segmentLength, 0)), drawParams);
        return rect;
    };
}
exports.default = default_1;
