import { Point } from 'dut';
import { assertPropsWithValue } from 'utils';
import { assert } from 'chai';

describe('Point', () => {
  describe('constructor', () => {
    it('should throw if args empty', () => {
      let errMsg = '';
      try {
        new Point();
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, 'expected arguments');
    });

    it('should throw if insufficient args', () => {
      let errMsg = '';
      try {
        new Point(0);
      } catch (err) {
        errMsg = err.toString();
      }
      assert.include(errMsg, 'expected arguments');
    });

    describe('Point2 constructor', () => {
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
        it('should have int positions', () => {
          const x = -100;
          const y = -200;
          assertPropsWithValue(new Point(x, y))({ x, y });
        });
      });

      it('should have negative double positions', () => {
        const x = -100.12345;
        const y = -200.89764;
        assertPropsWithValue(new Point(x, y))({ x, y });
      });
    });

    describe('Point3 constructor', () => {
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
  });
});
