const { expect } = require('chai');

module.exports = function ({ cv, utils }) {

  const {
    assertError,
    assertPropsWithValue
  } = utils;

  const OperatorRequiresArg = pt => (func, isScalar) => {
    it('should throw if no args', () => {
      assertError(
        () => pt[func].bind(pt)(),
        `expected arg to be ${isScalar ? 'a Scalar' : 'an instance of Point'}`
      );
    });
  };

  describe('constructor', () => {
    it('should throw if args empty', () => {
      assertError(() => new cv.Point(), 'expected arguments');
    });

    it('should throw if insufficient args', () => {
      assertError(() => new cv.Point(0), 'expected arguments');
    });

    describe('Point2', () => {
      describe('constructor', () => {
        it('should have int positions', () => {
          const x = 100;
          const y = 200;
          assertPropsWithValue(new cv.Point(x, y))({ x, y });
        });

        it('should have double positions', () => {
          const x = 100.12345;
          const y = 200.89764;
          assertPropsWithValue(new cv.Point(x, y))({ x, y });
        });

        it('should have negative int positions', () => {
          const x = -100;
          const y = -200;
          assertPropsWithValue(new cv.Point(x, y))({ x, y });
        });

        it('should have negative double positions', () => {
          const x = -100.12345;
          const y = -200.89764;
          assertPropsWithValue(new cv.Point(x, y))({ x, y });
        });
      });

      describe('at', () => {
        const pt2 = new cv.Point(10, 20);
        it('should throw index out of bounds', () => {
          assertError(() => pt2.at(-1), 'Index out of bounds: Point2 at index -1');
          assertError(() => pt2.at(2), 'Index out of bounds: Point2 at index 2');
        });

        it('should return values from indices', () => {
          expect(pt2.at(0)).to.equal(10);
          expect(pt2.at(1)).to.equal(20);
        });
      });

      describe('operators', () => {
        const pt0 = new cv.Point(1, 1);
        const pt1 = new cv.Point(2, 3);
        const operatorRequiresArg = OperatorRequiresArg(pt0);

        describe('add', () => {
          operatorRequiresArg('add');

          it('add points', () => {
            assertPropsWithValue(pt0.add(pt1))({ x: 3, y: 4 });
          });
        });

        describe('sub', () => {
          operatorRequiresArg('sub');

          it('subtract points', () => {
            assertPropsWithValue(pt0.sub(pt1))({ x: -1, y: -2 });
          });
        });

        describe('mul', () => {
          operatorRequiresArg('mul', true);

          it('multiply point by scalar', () => {
            assertPropsWithValue(pt1.mul(2))({ x: 4, y: 6 });
          });
        });

        describe('div', () => {
          operatorRequiresArg('div', true);

          it('divide point by scalar', () => {
            assertPropsWithValue(pt1.div(2))({ x: 1.0, y: 1.5 });
          });
        });

        describe('norm', () => {
          it('should return magnitude', () => {
            expect(new cv.Point(Math.sqrt(8), Math.sqrt(8)).norm()).to.equal(4);
          });
        });
      });
    });

    describe('Point3', () => {
      describe('constructor', () => {
        it('should have int positions', () => {
          const x = 100;
          const y = 200;
          const z = 300;
          assertPropsWithValue(new cv.Point(x, y, z))({ x, y, z });
        });

        it('should have double positions', () => {
          const x = 100.12345;
          const y = 200.89764;
          const z = 300.034;
          assertPropsWithValue(new cv.Point(x, y, z))({ x, y, z });
        });

        it('should have negative int positions', () => {
          it('should have int positions', () => {
            const x = -100;
            const y = -200;
            const z = -300;
            assertPropsWithValue(new cv.Point(x, y, z))({ x, y, z });
          });
        });

        it('should have negative double positions', () => {
          const x = -100.12345;
          const y = -200.89764;
          const z = -300.034;
          assertPropsWithValue(new cv.Point(x, y, z))({ x, y, z });
        });
      });

      describe('at', () => {
        const pt3 = new cv.Point(10, 20, 30);
        it('should throw index out of bounds', () => {
          assertError(() => pt3.at(-1), 'Index out of bounds: Point3 at index -1');
          assertError(() => pt3.at(3), 'Index out of bounds: Point3 at index 3');
        });

        it('should return values from indeces', () => {
          expect(pt3.at(0)).to.equal(10);
          expect(pt3.at(1)).to.equal(20);
          expect(pt3.at(2)).to.equal(30);
        });
      });

      describe('operators', () => {
        const pt0 = new cv.Point(1, 1, 1);
        const pt1 = new cv.Point(2, 3, 4);
        const operatorRequiresArg = OperatorRequiresArg(pt0);
        describe('add', () => {
          operatorRequiresArg('add');

          it('add points', () => {
            assertPropsWithValue(pt0.add(pt1))({ x: 3, y: 4, z: 5 });
          });
        });

        describe('sub', () => {
          operatorRequiresArg('sub');

          it('subtract points', () => {
            assertPropsWithValue(pt0.sub(pt1))({ x: -1, y: -2, z: -3 });
          });
        });

        describe('mul', () => {
          operatorRequiresArg('mul', true);

          it('multiply point by scalar', () => {
            assertPropsWithValue(pt1.mul(2))({ x: 4, y: 6, z: 8 });
          });
        });

        describe('div', () => {
          operatorRequiresArg('div', true);

          it('divide point by scalar', () => {
            assertPropsWithValue(pt1.div(2))({ x: 1.0, y: 1.5, z: 2 });
          });
        });

        describe('norm', () => {
          it('should return magnitude', () => {
            expect(new cv.Point(Math.sqrt(4), Math.sqrt(4), Math.sqrt(8)).norm()).to.equal(4);
          });
        });
      });
    });
  });

};
