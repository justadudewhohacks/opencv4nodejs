import { TestContext } from '../model';
import dnnTests from './dnnTests';
import NetTests from './NetTests';

export default (args: TestContext) => {
  describe('dnn', () => dnnTests(args));
  describe('Net', () => NetTests(args));
};
