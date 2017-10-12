const cv = require('../');

const detectPromised = (det, img) => new Promise((resolve, reject) => {
  det.detectAsync(img, (err, kps) => {
    if (err) {
      return reject(err);
    }
    return resolve(kps);
  });
});

const computePromised = (det, img, kps) => new Promise((resolve, reject) => {
  det.computeAsync(img, kps, (err, desc) => {
    if (err) {
      return reject(err);
    }
    return resolve({ kps, desc });
  });
});

const matchPromised = (desc1, desc2, kps1, kps2) => new Promise((resolve, reject) => {
  cv.matchBruteForceAsync(desc1, desc2, (err, matches) => {
    if (err) {
      return reject(err);
    }
    return resolve({ matches, kps1, kps2 });
  });
});

const detectAndComputePromised = (det, img) =>
  detectPromised(det, img).then(kps => computePromised(det, img, kps));

const img1 = cv.imread('../data/s0.jpg');
const img2 = cv.imread('../data/s1.jpg');

const detectorNames = [
  'AKAZE',
  'BRISK',
  'KAZE',
  'ORB'
];

const createDetectorFromName = name => new cv[`${name}Detector`]();

// create 4 promises -> each detector detects and computes descriptors for img1 and img2
const promises = detectorNames
  .map(createDetectorFromName)
  .map(det =>
  // also detect and compute descriptors for img1 and img2 async
  Promise.all([detectAndComputePromised(det, img1), detectAndComputePromised(det, img2)])
    .then(allResults =>
      matchPromised(
        allResults[0].desc,
        allResults[1].desc,
        allResults[0].kps,
        allResults[1].kps
      ))
);

Promise.all(promises)
  .then((allResults) => {
    allResults.forEach((result) => {
      const drawMatchesImg = cv.drawMatches(
        img1,
        img2,
        result.kps1,
        result.kps2,
        result.matches
      );
      cv.imshowWait('matches', drawMatchesImg);
    });
  })
  .catch(err => console.error(err));
