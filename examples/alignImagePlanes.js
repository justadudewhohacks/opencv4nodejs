const opencv = require('../');

const { Mat, matTypes, features2d, xfeatures2d, imgproc, io } = opencv;
const { interpolationFlags } = imgproc;

const hData = [
  [0.5, 0, 0],
  [0, 0.5, 0],
  [0, 0, 1]
];
const homography = new Mat(hData, matTypes.CV_64F);

io.imread('../data/Lenna.png', (err, img) => {
  if (err) {
    console.error(err);
    return;
  }
  console.log(img)
  console.log(homography)
  let warped;
  try {
    warped = img.warpPerspective({
      transformationMatrix: homography,
      flags: interpolationFlags.INTER_CUBIC
    });
  } catch (err) {
    console.error(err);
    return;
  }

console.log(warped)
  io.imshow('original image', img);
  io.imshow('warped image', warped);
});
