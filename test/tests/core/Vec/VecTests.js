const { expect } = require('chai');

module.exports = function ({ cv, utils }) {

  const { assertError } = utils;

  describe('at', () => {
    describe('Vec2', () => {
      const vec2 = new cv.Vec(10, 20);
      it('should throw index out of bounds', () => {
        assertError(() => vec2.at(-1), 'Index out of bounds: Vec2 at index -1');
        assertError(() => vec2.at(2), 'Index out of bounds: Vec2 at index 2');
      });

      it('should return values from indices', () => {
        expect(vec2.at(0)).to.equal(10);
        expect(vec2.at(1)).to.equal(20);
      });
    });
    describe('Vec3', () => {
      const vec3 = new cv.Vec(10, 20, 30);
      it('should throw index out of bounds', () => {
        assertError(() => vec3.at(-1), 'Index out of bounds: Vec3 at index -1');
        assertError(() => vec3.at(3), 'Index out of bounds: Vec3 at index 3');
      });

      it('should return values from indeces', () => {
        expect(vec3.at(0)).to.equal(10);
        expect(vec3.at(1)).to.equal(20);
        expect(vec3.at(2)).to.equal(30);
      });
    });

    describe('Vec4', () => {
      const vec4 = new cv.Vec(5, 10, 20, 30);
      it('should throw index out of bounds', () => {
        assertError(() => vec4.at(-1), 'Index out of bounds: Vec4 at index -1');
        assertError(() => vec4.at(4), 'Index out of bounds: Vec4 at index 4');
      });

      it('should return values from indices', () => {
        expect(vec4.at(0)).to.equal(5);
        expect(vec4.at(1)).to.equal(10);
        expect(vec4.at(2)).to.equal(20);
        expect(vec4.at(3)).to.equal(30);
      });
    });

    describe('Vec6', () => {
      const vec6 = new cv.Vec(5, 10, 20, 30, 40, 50);
      it('should throw index out of bounds', () => {
        assertError(() => vec6.at(-1), 'Index out of bounds: Vec6 at index -1');
        assertError(() => vec6.at(6), 'Index out of bounds: Vec6 at index 6');
      });

      it('should return values from indices', () => {
        expect(vec6.at(0)).to.equal(5);
        expect(vec6.at(1)).to.equal(10);
        expect(vec6.at(2)).to.equal(20);
        expect(vec6.at(3)).to.equal(30);
        expect(vec6.at(4)).to.equal(40);
        expect(vec6.at(5)).to.equal(50);
      });
    });
  });

};
