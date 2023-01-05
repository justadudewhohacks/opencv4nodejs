import { assert, expect } from 'chai';
import fs from 'fs';
import { Vec2, Vec3, Vec4 } from '@u4/opencv4nodejs';

export const assertError = (func: () => any, msg: string): void => {
  let errMsg = '';
  try {
    func();
  } catch (err) {
    errMsg = err.toString();
  }
  assert.include(errMsg, msg);
};

const assertErrorAsyncPromised = (func: () => any, msg: string): Promise<any> => {
  const ret = func();

  if (!ret.then || !ret.catch) {
    assert(false, 'func does not return a promise');
    return Promise.reject(ret);
  }

  return ret.then(() => {
    assert(false, 'no error was thrown');
  })
    .catch((err: any) => {
      assert.include(err.toString(), msg);
    });
};

const makeCompareValues = (floatSafe: boolean) => (val1: number | object | boolean | string, val2: number | object | boolean | string) => {
  if (floatSafe && typeof val1 === 'number' && typeof val2 === 'number') {
    return Math.abs(val1 - val2) < 0.001;
  } if (typeof val1 === 'object' && typeof val2 === 'object') {
    return JSON.stringify(val1) === JSON.stringify(val2);
  }

  return val1 === val2;
};

export const assertPropsWithValue = (obj: {[key: string]: number | object | boolean | string} & any, props: {[key: string]: number | object | boolean | string}, floatSafe = false) => {
  const compareValues = makeCompareValues(floatSafe);
  Object.keys(props).forEach((key) => assert(compareValues(props[key], obj[key]), `${key} - expected: ${props[key]}, have: ${obj[key]}`));
};

export const funcShouldRequireArgs = (func: (...args: any[]) => any): void => {
  it('should throw if no args', () => {
    assertError(func, 'expected arg 0 to be');
  });
};

export const _funcShouldRequireArgs = (func: (...args: any[]) => any) : void => {
  it('should throw if no args', () => {
    assertError(func, 'expected argument 0 to be');
  });
};

export const asyncFuncShouldRequireArgs = (func: (...args: any[]) => any): void => {
  it('should throw if no args', (done) => {
    assertErrorAsyncPromised(func, 'expected argument 0 to be')
      .then(() => done());
  });
};

export const _asyncFuncShouldRequireArgs = (func: (...args: any[]) => any): void => {
  it('should throw if no args', (done) => {
    assertErrorAsyncPromised(func, 'expected arg 0 to be')
      .then(() => done());
  });
};

export const expectFloat = (val: number, expected: number): Chai.Assertion => expect(val).to.be.a('number').above(expected - 0.01).below(expected + 0.01);

const tmpdataDir = './tmpdata';

const ensureTmpdataDirExists = (): void => {
  if (!fs.existsSync(tmpdataDir)) {
    fs.mkdirSync(tmpdataDir);
  }
};

export const clearTmpData = (): void => {
  ensureTmpdataDirExists();

  const files = fs.readdirSync(tmpdataDir);
  files.forEach((file) => {
    fs.unlinkSync(`${tmpdataDir}/${file}`);
  });
};

export const getTmpDataFilePath = (file: string): string => {
  ensureTmpdataDirExists();

  const filePath = `${tmpdataDir}/${file}`;
  if (fs.existsSync(filePath)) {
    fs.unlinkSync(filePath);
  }
  return filePath;
};

export const fileExists = (filePath: string) => fs.existsSync(filePath);

export const expectToBeVec2 = (vec: Vec2): void => {
  expect(vec).to.have.property('x');
  expect(vec).to.have.property('y');
  expect(vec).to.not.have.property('z');
  expect(vec).to.not.have.property('w');
};

export const expectToBeVec3 = (vec: Vec3): void => {
  expect(vec).to.have.property('x');
  expect(vec).to.have.property('y');
  expect(vec).to.have.property('z');
  expect(vec).to.not.have.property('w');
};

export const expectToBeVec4 = (vec: Vec4): void => {
  expect(vec).to.have.property('x');
  expect(vec).to.have.property('y');
  expect(vec).to.have.property('z');
  expect(vec).to.have.property('w');
};
