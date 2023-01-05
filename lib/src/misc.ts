import type * as openCV from '../..';
import { Mat, Rect } from '../..';

export const allTypes = ['CV_8U', 'CV_8S', 'CV_16U', 'CV_16S', 'CV_32S', 'CV_32F', 'CV_64F', 'CV_8UC1', 'CV_8UC2', 'CV_8UC3', 'CV_8UC4', 'CV_8SC1', 'CV_8SC2', 'CV_8SC3', 'CV_8SC4', 'CV_16UC1', 'CV_16UC2', 'CV_16UC3', 'CV_16UC4', 'CV_16SC1', 'CV_16SC2', 'CV_16SC3', 'CV_16SC4', 'CV_32SC1', 'CV_32SC2', 'CV_32SC3', 'CV_32SC4', 'CV_32FC1', 'CV_32FC2', 'CV_32FC3', 'CV_32FC4', 'CV_64FC1', 'CV_64FC2', 'CV_64FC3', 'CV_64FC4'] as const;
export type MatTypes = typeof allTypes[number];
/**
 * register new functions
 * @param cv 
 */
export default function (cv: typeof openCV): void {
    /**
     * Convert a Mat type to string for easy read
     * non Natif code
     * @param type Mat type as int value
     */
    cv.toMatTypeName = (type: number): MatTypes | undefined => {
        for (const t of allTypes) {
            if (cv[t] === type) return t;
        }
    };
    /**
     * Find values greater than threshold in a 32bit float matrix and return a list of matchs formated as [[x1, y1, score1]. [x2, y2, score2], [x3, y3, score3]]
     * add to be used with matchTemplate
     * non Natif code
     * @param scoreMat Matric containing scores as 32Bit float (CV_32F)
     * @param threshold Minimal score to collect
     * @param region search region
     * @returns a list of matchs
     */
    cv.getScoreMax = (scoreMat: Mat, threshold: number, region?: Rect): Array<[number, number, number]> => {
        if (scoreMat.type !== cv.CV_32F)
            throw Error('this method can only be call on a CV_32F Mat');
        if (scoreMat.dims !== 2)
            throw Error('this method can only be call on a 2 dimmention Mat');

        const out: Array<[number, number, number]> = [];
        const { cols, rows } = scoreMat;
        const raw = scoreMat.getData();

        let x1: number, x2: number, y1: number, y2: number;
        if (region) {
            x1 = region.x;
            y1 = region.y;
            x2 = x1 + region.width;
            y2 = y1 + region.height;
        } else {
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
    }

    /**
     * Drop overlaping zones, keeping best one
     * @param template template Matrix used to get dimentions.
     * @param matches list of matches as a list in [x,y,score]. (this data will be altered)
     * @returns best match without colisions
     */
    cv.dropOverlappingZone = (template: Mat, matches: Array<[number, number, number]>): Array<[number, number, number]> => {
        const total = matches.length;
        const width = template.cols / 2;
        const height = template.rows / 2;
        for (let i = 0; i < total; i++) {
            const cur = matches[i];
            if (!cur[2]) continue;
            for (let j = i + 1; j < total; j++) {
                const sec = matches[j];
                if (!sec[2]) continue;
                if (Math.abs(cur[1] - sec[1]) > height) continue;
                if (Math.abs(cur[0] - sec[0]) > width) continue;
                if (cur[2] > sec[2]) {
                    sec[2] = 0;
                } else {
                    cur[2] = 0;
                    break;
                }
            }
        }
        return matches.filter(m => m[2]);
    }


}
