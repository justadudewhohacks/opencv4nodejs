const { expect } = require('chai');

module.exports = function ({ cv, utils }) {

  const { generateAPITests } = utils;

  describe('constructor', () => {
    it('can be created', () => {
      const x = 10;
      const y = 20;
      const width = 50;
      const height = 50;
      const rect = new cv.Rect(x, y, width, height);
      expect(rect).to.have.property('x').to.equal(x);
      expect(rect).to.have.property('y').to.equal(y);
      expect(rect).to.have.property('width').to.equal(width);
      expect(rect).to.have.property('height').to.equal(height);
    });
  });

  describe('and', () => {
    generateAPITests({
      getDut: () => new cv.Rect(0, 0, 50, 50),
      methodName: 'and',
      methodNameSpace: 'Rect',
      getRequiredArgs: () => [new cv.Rect(0, 0, 50, 20)],
      expectOutput: (res) => {
        expect(res).to.be.instanceOf(cv.Rect);
        expect(res.x).to.equal(0);
        expect(res.y).to.equal(0);
        expect(res.width).to.equal(50);
        expect(res.height).to.equal(20);
      },
      hasAsync: false
    });
  });

  describe('or', () => {
    generateAPITests({
      getDut: () => new cv.Rect(0, 0, 50, 50),
      methodName: 'or',
      methodNameSpace: 'Rect',
      getRequiredArgs: () => [new cv.Rect(0, 0, 50, 20)],
      expectOutput: (res) => {
        expect(res).to.be.instanceOf(cv.Rect);
        expect(res.x).to.equal(0);
        expect(res.y).to.equal(0);
        expect(res.width).to.equal(50);
        expect(res.height).to.equal(50);
      },
      hasAsync: false
    });
  });

  describe('toSquare', () => {
    describe('x < y', () => {
      generateAPITests({
        getDut: () => new cv.Rect(0, 0, 50, 30),
        methodName: 'toSquare',
        methodNameSpace: 'Rect',
        expectOutput: (res) => {
          expect(res.x).to.equal(0);
          expect(res.y).to.equal(-10);
          expect(res.width).to.equal(50);
          expect(res.height).to.equal(50);
        }
      });
    });

    describe('y < x', () => {
      generateAPITests({
        getDut: () => new cv.Rect(0, 0, 30, 50),
        methodName: 'toSquare',
        methodNameSpace: 'Rect',
        expectOutput: (res) => {
          expect(res.x).to.equal(-10);
          expect(res.y).to.equal(0);
          expect(res.width).to.equal(50);
          expect(res.height).to.equal(50);
        }
      });
    });

    describe('x === y', () => {
      generateAPITests({
        getDut: () => new cv.Rect(0, 0, 50, 50),
        methodName: 'toSquare',
        methodNameSpace: 'Rect',
        expectOutput: (res) => {
          expect(res.x).to.equal(0);
          expect(res.y).to.equal(0);
          expect(res.width).to.equal(50);
          expect(res.height).to.equal(50);
        }
      });
    });
  });

  describe('pad', () => {
    describe('by factor', () => {
      describe('pad down', () => {
        generateAPITests({
          getDut: () => new cv.Rect(0, 0, 100, 100),
          methodName: 'pad',
          methodNameSpace: 'Rect',
          getRequiredArgs: () => [0.5],
          expectOutput: (res) => {
            expect(res.x).to.equal(25);
            expect(res.y).to.equal(25);
            expect(res.width).to.equal(50);
            expect(res.height).to.equal(50);
          }
        });
      });

      describe('pad up', () => {
        generateAPITests({
          getDut: () => new cv.Rect(0, 0, 100, 100),
          methodName: 'pad',
          methodNameSpace: 'Rect',
          getRequiredArgs: () => [2],
          expectOutput: (res) => {
            expect(res.x).to.equal(-50);
            expect(res.y).to.equal(-50);
            expect(res.width).to.equal(200);
            expect(res.height).to.equal(200);
          }
        });
      });
    });

    describe('by Size', () => {
      generateAPITests({
        getDut: () => new cv.Rect(0, 0, 100, 100),
        methodName: 'pad',
        methodNameSpace: 'Rect',
        getRequiredArgs: () => [new cv.Size(50, 200)],
        expectOutput: (res) => {
          expect(res.x).to.equal(25);
          expect(res.y).to.equal(-50);
          expect(res.width).to.equal(50);
          expect(res.height).to.equal(200);
        }
      });
    });
  });

  describe('rescale', () => {
    describe('scale down', () => {
      generateAPITests({
        getDut: () => new cv.Rect(50, 50, 100, 100),
        methodName: 'rescale',
        methodNameSpace: 'Rect',
        getRequiredArgs: () => [0.5],
        expectOutput: (res) => {
          expect(res.x).to.equal(25);
          expect(res.y).to.equal(25);
          expect(res.width).to.equal(50);
          expect(res.height).to.equal(50);
        }
      });
    });

    describe('scale up', () => {
      generateAPITests({
        getDut: () => new cv.Rect(50, 50, 100, 100),
        methodName: 'rescale',
        methodNameSpace: 'Rect',
        getRequiredArgs: () => [2],
        expectOutput: (res) => {
          expect(res.x).to.equal(100);
          expect(res.y).to.equal(100);
          expect(res.width).to.equal(200);
          expect(res.height).to.equal(200);
        }
      });
    });
  });

};
