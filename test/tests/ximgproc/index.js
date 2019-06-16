const ximgprocTests = require('./ximgprocTests');
const MatXImgprocTests = require('./MatXImgprocTests');

module.exports = function (args) {
  describe('ximgproc', () => ximgprocTests(args));
  describe('MatXImgproc', () => MatXImgprocTests(args));
};