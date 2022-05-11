import { DescriptorMatch, FeatureDetector, Mat } from '@u4/opencv4nodejs';
import { cv, getResourcePath, wait4key } from './utils';

const matchFeatures = ({ img1, img2, detector, matchFunc }: { img1: Mat, img2: Mat, detector: FeatureDetector, matchFunc: (descs1: Mat, descs2: Mat) => DescriptorMatch[] }) => {
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


export async function test() {
  const img1 = cv.imread(getResourcePath('s0.jpg'));
  const img2 = cv.imread(getResourcePath('s1.jpg'));

  // check if opencv compiled with extra modules and nonfree
  if (cv.xmodules && cv.xmodules.xfeatures2d) {
    const siftMatchesImg = matchFeatures({
      img1,
      img2,
      detector: new cv.SIFTDetector({ nFeatures: 2000 }),
      matchFunc: cv.matchFlannBased
    });
    cv.imshow('SIFT matches', siftMatchesImg);
    await wait4key();
  } else {
    console.log('skipping SIFT matches');
  }

  const orbMatchesImg = matchFeatures({
    img1,
    img2,
    detector: new cv.ORBDetector(),
    matchFunc: cv.matchBruteForceHamming
  });
  cv.imshow('ORB matches', orbMatchesImg);
  await wait4key();

  // Match using the BFMatcher with crossCheck true
  const bf = new cv.BFMatcher(cv.NORM_L2, true);
  const orbBFMatchIMG = matchFeatures({
    img1,
    img2,
    detector: new cv.ORBDetector(),
    matchFunc: (desc1, desc2) => bf.match(desc1, desc2)
  });
  cv.imshow('ORB with BFMatcher - crossCheck true', orbBFMatchIMG);
  await wait4key();
}
test();