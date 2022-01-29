import { TestContext } from '../model';
import ParamGridTests from './ParamGridTests';
import StatModelTests from './StatModelTests';
import SVMTests from './SVMTests';
import TrainDataTests from './TrainDataTests';

export default (args: TestContext) => {
  describe('ParamGrid', () => ParamGridTests(args));
  describe('StatModel', () => StatModelTests(args));
  describe('TrainData', () => TrainDataTests(args));
  describe('SVM', () => SVMTests(args));
};
