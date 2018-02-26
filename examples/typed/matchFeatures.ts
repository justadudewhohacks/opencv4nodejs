import * as cv from '../../';

const matchFeatures = (
  img1: cv.Mat,
  img2: cv.Mat,
  detector: cv.FeatureDetector,
  matchFunc: (descs1: cv.Mat, descs2: cv.Mat) => cv.DescriptorMatch[]
) => {
  // detect keypoints
  const keyPoints1 = detector.detect(img1);
  const keyPoints2 = detector.detect(img2);

  // compute feature descriptors
  const descriptors1 = detector.compute(img1, keyPoints1);
  const descriptors2 = detector.compute(img2, keyPoints2);

  // match the feature descriptors
  const matches = matchFunc(descriptors1, descriptors2);

  // only keep good matches
  const bestN = 40;
  const bestMatches = matches.sort(
    (match1, match2) => match1.distance - match2.distance
  ).slice(0, bestN);

  return cv.drawMatches(
    img1,
    img2,
    keyPoints1,
    keyPoints2,
    bestMatches
  );
};

const img1 = cv.imread('../../data/s0.jpg');
const img2 = cv.imread('../../data/s1.jpg');

// check if opencv compiled with extra modules and nonfree
if (cv.xmodules.xfeatures2d) {
  const siftMatchesImg = matchFeatures(
    img1,
    img2,
    new cv.SIFTDetector({ nFeatures: 2000 }),
    cv.matchFlannBased
  );
  cv.imshowWait('SIFT matches', siftMatchesImg);
} else {
  console.log('skipping SIFT matches');
}

const orbMatchesImg = matchFeatures(
  img1,
  img2,
  new cv.ORBDetector(),
  cv.matchBruteForceHamming
);
cv.imshowWait('ORB matches', orbMatchesImg);

