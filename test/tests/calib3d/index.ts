import { TestContext } from '../model';
import calib3dTests from './calib3dTests';
import MatCalib3dTests from './MatCalib3dTests';

export default function (args: TestContext) {
  describe('calib3d', () => calib3dTests(args));
  describe('MatCalib3d', () => MatCalib3dTests(args));
};