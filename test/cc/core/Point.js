import { Point } from 'dut';
import { assertError, assertPropsWithValue } from 'utils';
import { expect } from 'chai';

describe('Point', () => {
  describe('constructor', () => {
    it('should throw if args empty', () => {
      assertError(() => new Point(), 'expected arguments');
    });

    it('should throw if insufficient args', () => {
      assertError(() => new Point(0), 'expected arguments');
    });

    describe('Point2', () => {
      describe('constructor', () => {
        it('should have int positions', () => {
          const x = 100;
          const y = 200;
          assertPropsWithValue(new Point(x, y))({ x, y });
        });

        it('should have double positions', () => {
          const x = 100.12345;
          const y = 200.89764;
          assertPropsWithValue(new Point(x, y))({ x, y });
        });

        it('should have negative int positions', () => {
          const x = -100;
          const y = -200;
          assertPropsWithValue(new Point(x, y))({ x, y });
        });

        it('should have negative double positions', () => {
          const x = -100.12345;
          const y = -200.89764;
          assertPropsWithValue(new Point(x, y))({ x, y });
        });
      });

      describe('at', () => {
        const pt2 = new Point(10, 20);
        it('should throw index out of bounds', () => {
          assertError(() => pt2.at(-1), 'Index out of bounds: -1');
          assertError(() => pt2.at(2), 'Index out of bounds: 2');
        });

        it('should return values from indices', () => {
          expect(pt2.at(0)).to.equal(10);
          expect(pt2.at(1)).to.equal(20);
        });
      });
    });

    describe('Point3', () => {
      describe('constructor', () => {
        it('should have int positions', () => {
          const x = 100;
          const y = 200;
          const z = 300;
          assertPropsWithValue(new Point(x, y, z))({ x, y, z });
        });

        it('should have double positions', () => {
          const x = 100.12345;
          const y = 200.89764;
          const z = 300.034;
          assertPropsWithValue(new Point(x, y, z))({ x, y, z });
        });

        it('should have negative int positions', () => {
          it('should have int positions', () => {
            const x = -100;
            const y = -200;
            const z = -300;
            assertPropsWithValue(new Point(x, y, z))({ x, y, z });
          });
        });

        it('should have negative double positions', () => {
          const x = -100.12345;
          const y = -200.89764;
          const z = -300.034;
          assertPropsWithValue(new Point(x, y, z))({ x, y, z });
        });
      });

      describe('at', () => {
        const pt3 = new Point(10, 20, 30);
        it('should throw index out of bounds', () => {
          assertError(() => pt3.at(-1), 'Index out of bounds: -1');
          assertError(() => pt3.at(3), 'Index out of bounds: 3');
        });

        it('should return values from indeces', () => {
          expect(pt3.at(0)).to.equal(10);
          expect(pt3.at(1)).to.equal(20);
          expect(pt3.at(2)).to.equal(30);
        });
      });
    });
  });
});
