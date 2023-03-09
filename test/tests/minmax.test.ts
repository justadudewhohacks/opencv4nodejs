import { expect } from 'chai';
import cv from '@u4/opencv4nodejs';

describe('static Min/Max methods added on 2023-03-03', () => {
  const mat1 = new cv.Mat([
    [10, 20, 30],
    [40, 50, 60],
  ], cv.CV_8U);
  const mat2 = new cv.Mat([
    [1, 22, 3],
    [4, 55, 66],
  ], cv.CV_8U);

  it('max', () => {
    const dest = new cv.Mat([
      [0, 0, 0],
      [0, 0, 0],
    ], cv.CV_8U);

    const expected = new cv.Mat([
      [10, 22, 30],
      [40, 55, 66],
    ], cv.CV_8U);

    const dest2 = cv.max(mat1, mat2, dest);
    expect(dest2).to.be.deep.equal(expected);
  });

  it('max bad dimension error', () => {
    const badsrc = new cv.Mat([[0, 0, 0]], cv.CV_8U);
    const dest2 = cv.Mat.zeros(2, 3, cv.CV_8U);
    try {
      cv.max(mat1, badsrc, dest2);
    } catch (e) {
      // TODO should throws Error insted of string
      expect(e as string).to.contain('Core::Max - OpenCV Error');
      // Core::Max - OpenCV Error: (The operation is neither 'array op array' (where arrays have the same size and type), nor 'array op scalar', nor 'scalar op array')
      return;
    }
    expect.fail('should not get here');
  });

  it('min', () => {
    // use the zeros method to create a new mat
    const dest = cv.Mat.zeros(2, 3, cv.CV_8U);
    const expected = new cv.Mat([
      [1, 20, 3],
      [4, 50, 60],
    ], cv.CV_8U);

    const dest2 = cv.min(mat1, mat2, dest);
    expect(dest2).to.be.deep.equal(expected);
  });
});
