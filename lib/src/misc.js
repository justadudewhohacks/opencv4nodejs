"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.allTypes = void 0;
exports.allTypes = ['CV_8U', 'CV_8S', 'CV_16U', 'CV_16S', 'CV_32S', 'CV_32F', 'CV_64F', 'CV_8UC1', 'CV_8UC2', 'CV_8UC3', 'CV_8UC4', 'CV_8SC1', 'CV_8SC2', 'CV_8SC3', 'CV_8SC4', 'CV_16UC1', 'CV_16UC2', 'CV_16UC3', 'CV_16UC4', 'CV_16SC1', 'CV_16SC2', 'CV_16SC3', 'CV_16SC4', 'CV_32SC1', 'CV_32SC2', 'CV_32SC3', 'CV_32SC4', 'CV_32FC1', 'CV_32FC2', 'CV_32FC3', 'CV_32FC4', 'CV_64FC1', 'CV_64FC2', 'CV_64FC3', 'CV_64FC4'];
/**
 * register new functions
 * @param cv
 */
function default_1(cv) {
    cv.toMatTypeName = (type) => {
        for (const t of exports.allTypes) {
            if (cv[t] === type)
                return t;
        }
    };
    cv.getScoreMax = (scoreMat, threshold, region) => {
        if (scoreMat.type !== cv.CV_32F)
            throw Error('this method can only be call on a CV_32F Mat');
        if (scoreMat.dims !== 2)
            throw Error('this method can only be call on a 2 dimmention Mat');
        const out = [];
        const { cols, rows } = scoreMat;
        const raw = scoreMat.getData();
        let x1, x2, y1, y2;
        if (region) {
            x1 = region.x;
            y1 = region.y;
            x2 = x1 + region.width;
            y2 = y1 + region.height;
        }
        else {
            x1 = y1 = 0;
            x2 = cols;
            y2 = rows;
        }
        for (let y = y1; y < y2; y++) {
            let offset = (x1 + y * cols) * 4;
            for (let x = x1; x < x2; x++) {
                const value = raw.readFloatLE(offset);
                if (value > threshold) {
                    out.push([x, y, value]);
                }
                offset += 4;
            }
        }
        return out;
    };
}
exports.default = default_1;
