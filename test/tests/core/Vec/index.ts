import VecTests from './VecTests';
import constructorTests from './constructorTests';
import operatorTests from './operatorTests';
import { TestContext } from '../../model';

export default function (args: TestContext) {
  describe('Vec', () => VecTests(args));
  describe('constructor', () => constructorTests(args));
  describe('operators', () => operatorTests(args));
};