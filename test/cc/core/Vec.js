import { Vec } from 'dut';
import { assertError, assertPropsWithValue } from 'utils';
import { expect } from 'chai';

describe('Vec', () => {
  describe('constructor', () => {
    it('should throw if args emvecy', () => {
      assertError(() => new Vec(), 'expected arguments');
    });

    it('should throw if insufficient args', () => {
      assertError(() => new Vec(0), 'expected arguments');
    });

    describe('Vec2', () => {
      describe('constructor', () => {
        it('should have int positions', () => {
          const x = 100;
          const y = 200;
          assertPropsWithValue(new Vec(x, y))({ x, y });
        });

        it('should have double positions', () => {
          const x = 100.12345;
          const y = 200.89764;
          assertPropsWithValue(new Vec(x, y))({ x, y });
        });

        it('should have negative int positions', () => {
          const x = -100;
          const y = -200;
          assertPropsWithValue(new Vec(x, y))({ x, y });
        });

        it('should have negative double positions', () => {
          const x = -100.12345;
          const y = -200.89764;
          assertPropsWithValue(new Vec(x, y))({ x, y });
        });
      });

      describe('at', () => {
        const vec2 = new Vec(10, 20);
        it('should throw index out of bounds', () => {
          assertError(() => vec2.at(-1), 'Index out of bounds: -1');
          assertError(() => vec2.at(2), 'Index out of bounds: 2');
        });

        it('should return values from indices', () => {
          expect(vec2.at(0)).to.equal(10);
          expect(vec2.at(1)).to.equal(20);
        });
      });
    });

    describe('Vec3', () => {
      describe('constructor', () => {
        it('should have int positions', () => {
          const x = 100;
          const y = 200;
          const z = 300;
          assertPropsWithValue(new Vec(x, y, z))({ x, y, z });
        });

        it('should have double positions', () => {
          const x = 100.12345;
          const y = 200.89764;
          const z = 300.034;
          assertPropsWithValue(new Vec(x, y, z))({ x, y, z });
        });

        it('should have negative int positions', () => {
          it('should have int positions', () => {
            const x = -100;
            const y = -200;
            const z = -300;
            assertPropsWithValue(new Vec(x, y, z))({ x, y, z });
          });
        });

        it('should have negative double positions', () => {
          const x = -100.12345;
          const y = -200.89764;
          const z = -300.034;
          assertPropsWithValue(new Vec(x, y, z))({ x, y, z });
        });
      });

      describe('at', () => {
        const vec3 = new Vec(10, 20, 30);
        it('should throw index out of bounds', () => {
          assertError(() => vec3.at(-1), 'Index out of bounds: -1');
          assertError(() => vec3.at(3), 'Index out of bounds: 3');
        });

        it('should return values from indeces', () => {
          expect(vec3.at(0)).to.equal(10);
          expect(vec3.at(1)).to.equal(20);
          expect(vec3.at(2)).to.equal(30);
        });
      });
    });

    describe('Vec4', () => {
      describe('constructor', () => {
        it('should have int positions', () => {
          const w = 50;
          const x = 100;
          const y = 200;
          const z = 300;
          assertPropsWithValue(new Vec(w, x, y, z))({ w, x, y, z });
        });

        it('should have double positions', () => {
          const w = 50.99;
          const x = 100.12345;
          const y = 200.89764;
          const z = 300.034;
          assertPropsWithValue(new Vec(w, x, y, z))({ w, x, y, z });
        });

        it('should have negative int positions', () => {
          it('should have int positions', () => {
            const w = -50;
            const x = -100;
            const y = -200;
            const z = -300;
            assertPropsWithValue(new Vec(w, x, y, z))({ w, x, y, z });
          });
        });

        it('should have negative double positions', () => {
          const w = -50.99;
          const x = -100.12345;
          const y = -200.89764;
          const z = -300.034;
          assertPropsWithValue(new Vec(w, x, y, z))({ w, x, y, z });
        });
      });

      describe('at', () => {
        const vec4 = new Vec(5, 10, 20, 30);
        it('should throw index out of bounds', () => {
          assertError(() => vec4.at(-1), 'Index out of bounds: -1');
          assertError(() => vec4.at(4), 'Index out of bounds: 4');
        });

        it('should return values from indices', () => {
          expect(vec4.at(0)).to.equal(5);
          expect(vec4.at(1)).to.equal(10);
          expect(vec4.at(2)).to.equal(20);
          expect(vec4.at(3)).to.equal(30);
        });
      });
    });
  });
});
