import { expect } from 'chai';
import cv from '@u4/opencv4nodejs';

describe('static Mat methods', () => {
  it('zeros', () => {
    const expected = Buffer.alloc(4, 0).fill(0);
    const mat = cv.Mat.zeros(2, 2, cv.CV_8U);
    expect(mat.cols).to.be.equal(2);
    expect(mat.rows).to.be.equal(2);
    const buf: Buffer = mat.getData();
    expect(buf).to.be.deep.equal(expected);
  });

  it('ones', () => {
    const expected = Buffer.alloc(4, 0).fill(1);
    const mat = cv.Mat.ones(2, 2, cv.CV_8U);
    expect(mat.cols).to.be.equal(2);
    expect(mat.rows).to.be.equal(2);
    const buf: Buffer = mat.getData();
    expect(buf).to.be.deep.equal(expected);
  });

  it('ones CV_8UC3', () => {
    const expected = Buffer.from([1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0]);
    const mat = cv.Mat.ones(2, 2, cv.CV_8UC3);
    expect(mat.cols).to.be.equal(2);
    expect(mat.rows).to.be.equal(2);
    const buf: Buffer = mat.getData();
    expect(buf).to.be.deep.equal(expected);
  });

  it('ones CV_16F', () => {
    const expected = Buffer.from([0, 60, 0, 60, 0, 60, 0, 60]);
    const mat = cv.Mat.ones(2, 2, cv.CV_16F);
    expect(mat.cols).to.be.equal(2);
    expect(mat.rows).to.be.equal(2);
    const buf: Buffer = mat.getData();
    expect(buf).to.be.deep.equal(expected);
  });

  it('eye', () => {
    const expected = Buffer.from([1, 0, 0, 1]);
    const mat = cv.Mat.eye(2, 2, cv.CV_8U);
    expect(mat.cols).to.be.equal(2);
    expect(mat.rows).to.be.equal(2);
    const buf: Buffer = mat.getData();
    expect(buf).to.be.deep.equal(expected);
  });
});
