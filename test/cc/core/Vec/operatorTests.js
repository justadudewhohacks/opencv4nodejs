import { Vec } from 'dut';
import { assertError, assertPropsWithValue } from 'utils';

const OperatorRequiresArg = vec => (func, isScalar) => {
  it('should throw if no args', () => {
    assertError(
      () => vec[func].bind(vec)(),
      `expected arg to be a ${isScalar ? 'Scalar' : 'Vec'}`
    );
  });
};

module.exports = () => {
  describe('operators', () => {
    describe('Vec2', () => {
      const vec2 = new Vec(100, 200);
      const otherVec2 = new Vec(25, 50);
      const operatorRequiresArg = OperatorRequiresArg(vec2);
      describe('add', () => {
        operatorRequiresArg('add');

        it('add vectors', async () => {
          assertPropsWithValue(vec2.add(otherVec2))({ x: 125, y: 250 });
        });
      });

      describe('sub', () => {
        operatorRequiresArg('sub');

        it('subtract vectors', async () => {
          assertPropsWithValue(vec2.sub(otherVec2))({ x: 75, y: 150 });
        });
      });

      describe('mul', () => {
        operatorRequiresArg('mul', true);

        it('multiply vector by scalar', async () => {
          assertPropsWithValue(vec2.mul(2))({ x: 200, y: 400 });
        });
      });

      describe('div', () => {
        operatorRequiresArg('div', true);

        it('divide vector by scalar', async () => {
          assertPropsWithValue(vec2.div(2))({ x: 50, y: 100 });
        });
      });
    });

    describe('Vec3', () => {
      const vec3 = new Vec(100, 200, 300);
      const otherVec3 = new Vec(25, 50, 75);
      const operatorRequiresArg = OperatorRequiresArg(vec3);
      describe('add', () => {
        operatorRequiresArg('add');

        it('add vectors', async () => {
          assertPropsWithValue(vec3.add(otherVec3))({ x: 125, y: 250, z: 375 });
        });
      });

      describe('sub', () => {
        operatorRequiresArg('sub');

        it('subtract vectors', async () => {
          assertPropsWithValue(vec3.sub(otherVec3))({ x: 75, y: 150, z: 225 });
        });
      });

      describe('mul', () => {
        operatorRequiresArg('mul', true);

        it('multiply vector by scalar', async () => {
          assertPropsWithValue(vec3.mul(2))({ x: 200, y: 400, z: 600 });
        });
      });

      describe('div', () => {
        operatorRequiresArg('div', true);

        it('divide vector by scalar', async () => {
          assertPropsWithValue(vec3.div(2))({ x: 50, y: 100, z: 150 });
        });
      });
    });

    describe('Vec4', () => {
      const vec4 = new Vec(50, 100, 200, 300);
      const otherVec4 = new Vec(10, 25, 50, 75);
      const operatorRequiresArg = OperatorRequiresArg(vec4);
      describe('add', () => {
        operatorRequiresArg('add');

        it('add vectors', async () => {
          assertPropsWithValue(vec4.add(otherVec4))({ w: 60, x: 125, y: 250, z: 375 });
        });
      });

      describe('sub', () => {
        operatorRequiresArg('sub');

        it('subtract vectors', async () => {
          assertPropsWithValue(vec4.sub(otherVec4))({ w: 40, x: 75, y: 150, z: 225 });
        });
      });

      describe('mul', () => {
        operatorRequiresArg('mul', true);

        it('multiply vector by scalar', async () => {
          assertPropsWithValue(vec4.mul(2))({ w: 100, x: 200, y: 400, z: 600 });
        });
      });

      describe('div', () => {
        operatorRequiresArg('div', true);

        it('divide vector by scalar', async () => {
          assertPropsWithValue(vec4.div(2))({ w: 25, x: 50, y: 100, z: 150 });
        });
      });
    });
  });
};
