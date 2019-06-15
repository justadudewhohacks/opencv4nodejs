const imgprocTests = require('./imgprocTests');
const MatImgprocTests = require('./MatImgprocTests');
const ContourTests = require('./ContourTests');

module.exports = function (args) {
  describe('imgproc', () => imgprocTests(args));
  describe('MatImgproc', () => MatImgprocTests(args));
  describe('Contour', () => ContourTests(args));
};