"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const assert_1 = __importDefault(require("assert"));
function default_1(cv) {
    // deprecate wrapper for the old calcHist API
    const _calcHist = cv.calcHist;
    cv.calcHist = function calcHist(img, histAxes, mask) {
        (0, assert_1.default)(img instanceof cv.Mat, 'Imgproc::CalcHist - Error: expected argument 0 to be of type Mat');
        (0, assert_1.default)(Array.isArray(histAxes), 'Imgproc::CalcHist - Error: expected argument 1 to be of type array of HistAxes');
        histAxes = histAxes.slice();
        let warningThrown = false;
        const len = histAxes.length;
        for (let i = 0; i < len; ++i) {
            const entry = histAxes[i];
            if (!(entry instanceof cv.HistAxes)) {
                if (!warningThrown) {
                    warningThrown = true;
                    console.warn(`Imgproc::CalcHist - Deprecated support for object in argument 1 at index ${i}. Please switch to using HistAxes instances.`);
                }
                histAxes[i] = new cv.HistAxes(entry);
            }
        }
        if (mask) {
            return _calcHist(img, histAxes, mask);
        }
        return _calcHist(img, histAxes);
    };
}
exports.default = default_1;
