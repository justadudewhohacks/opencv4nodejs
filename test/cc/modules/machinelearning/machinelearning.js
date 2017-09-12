import cv from 'dut';
import paramGridTests from './paramGridTests';
import statModelTests from './statModelTests';
import SVMTests from './SVMTests';
import trainDataTests from './trainDataTests';

describe('machinelearning', () => {
  paramGridTests();
  statModelTests();
  SVMTests();
  trainDataTests();
});
