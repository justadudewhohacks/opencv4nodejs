const cv = global.dut;
const paramGridTests = require('./paramGridTests');
const statModelTests = require('./statModelTests');
const SVMTests = require('./SVMTests');
const trainDataTests = require('./trainDataTests');

describe('machinelearning', () => {
  paramGridTests();
  statModelTests();
  SVMTests();
  trainDataTests();
});
