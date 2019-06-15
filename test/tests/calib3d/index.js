const calib3dTests = require('./calib3dTests');
const MatCalib3dTests = require('./MatCalib3dTests');

module.exports = function (args) {
  describe('calib3d', () => calib3dTests(args));
  describe('MatCalib3d', () => MatCalib3dTests(args));
};