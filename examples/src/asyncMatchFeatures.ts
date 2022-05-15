import { cv, getResourcePath, wait4key } from './utils';
import { FeatureDetector, Mat } from '@u4/opencv4nodejs';

const detectAndComputeAsync = (det: FeatureDetector, img: Mat) =>
  det.detectAsync(img)
    .then(kps => det.computeAsync(img, kps)
      .then(desc => ({ kps, desc }))
    );

const img1 = cv.imread(getResourcePath('s0.jpg'));
const img2 = cv.imread(getResourcePath('s1.jpg'));

const detectorNames = [
  // 'AGAST',
  'AKAZE',
  'BRISK',
  'KAZE',
  'SIFT',
  'SURF',
  'ORB',
] as const;

type detectorType = typeof detectorNames[number];

const createDetectorFromName = (name: detectorType): FeatureDetector => {
  switch (name) {
    // case 'AGAST':
    //   return new cv.AGASTDetector();
    // case 'FAST':
    //   return new cv.FASTDetector();
    case 'SIFT':
      return new cv.SIFTDetector();
    case 'SURF':
      return new cv.SURFDetector();
    case 'AKAZE':
      return new cv.AKAZEDetector();
    case 'BRISK':
      return new cv.BRISKDetector();
    case 'KAZE':
      return new cv.KAZEDetector();
    case 'ORB':
      return new cv.ORBDetector();
  }
  throw Error(`unknown detector: ${name}`);
  // return new cv[`${name}Detector`]()
};

async function asyncMatch() {
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
              kps2: allResults[1].kps,
            }))
        )
    );
  for (let i = 0; i < promises.length; i++) {
    try {
      const result = await promises[i];
      const drawMatchesImg = cv.drawMatches(
        img1,
        img2,
        result.kps1,
        result.kps2,
        result.matches
      );
      const title = `Detector ${detectorNames[i]}`
      cv.imshow(title, drawMatchesImg);
      console.log('Display result for detector:', detectorNames[i]);
      await wait4key();
      cv.destroyWindow(title);
    } catch (err) {
      console.error(err)
    }
  }
}

void asyncMatch().catch(e => console.error(e));