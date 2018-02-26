import * as cv from '../../';

const detectAndComputeAsync = (det: cv.FeatureDetector, img: cv.Mat) =>
  det.detectAsync(img)
    .then(kps => det.computeAsync(img, kps)
                      .then(desc => ({ kps, desc }))
    );

const img1 = cv.imread('../../data/s0.jpg');
const img2 = cv.imread('../../data/s1.jpg');

const detectorNames = [
  'AKAZE',
  'BRISK',
  'KAZE',
  'ORB'
];

const createDetectorFromName = (name: string) => new cv[`${name}Detector`]();

// create 4 promises -> each detector detects and computes descriptors for img1 and img2
const promises = detectorNames
  .map(createDetectorFromName)
  .map(det =>
    // also detect and compute descriptors for img1 and img2 async
    Promise.all([detectAndComputeAsync(det, img1), detectAndComputeAsync(det, img2)])
      .then(allResults =>
        cv.matchBruteForceAsync(
          allResults[0].desc,
          allResults[1].desc
        )
        .then(matches => ({
          matches,
          kps1: allResults[0].kps,
          kps2: allResults[1].kps
        }))
      )
);

Promise.all(promises)
  .then((allResults) => {
    allResults.forEach((result, i) => {
      const drawMatchesImg = cv.drawMatches(
        img1,
        img2,
        result.kps1,
        result.kps2,
        result.matches
      );
      cv.imshowWait(detectorNames[i], drawMatchesImg);
      cv.destroyAllWindows();
    });
  })
  .catch(err => console.error(err));
