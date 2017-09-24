const { Vec } = global.dut;
const { assertError, assertPropsWithValue } = global.utils;

module.exports = () => {
  describe('constructor', () => {
    it('should throw if args empty', () => {
      assertError(() => new Vec(), 'expected arguments');
    });

    it('should throw if insufficient args', () => {
      assertError(() => new Vec(0), 'expected arguments');
    });

    describe('Vec2', () => {
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

    describe('Vec3', () => {
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

    describe('Vec4', () => {
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
  });
};
