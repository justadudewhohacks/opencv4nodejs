import cv from 'dut';
import paramGridTests from './paramGridTests';
import statModelTests from './statModelTests';
import SVMTests from './SVMTests';
import trainDataTests from './trainDataTests';

describe('objdetect', () => {
  paramGridTests();
  statModelTests();
  SVMTests();
  trainDataTests();
});
