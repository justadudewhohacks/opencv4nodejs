const { expect } = require('chai');

module.exports = ({ cv }) => {

  describe('constructor', () => {
    it('should be constructable without args', () => {
      expect(new cv.ParamGrid()).to.be.instanceOf(cv.ParamGrid);
    });

    it('should be constructable from paramId', () => {
      const paramGrid = new cv.ParamGrid(cv.ml.SVM.C);
      expect(paramGrid).to.be.instanceOf(cv.ParamGrid);
    });

    it('should be constructable from required args', () => {
      const paramGrid = new cv.ParamGrid(0.5, 1.0, 1.5);
      expect(paramGrid).to.be.instanceOf(cv.ParamGrid);
      expect(paramGrid).to.have.property('minVal').to.equal(0.5);
      expect(paramGrid).to.have.property('maxVal').to.equal(1.0);
      expect(paramGrid).to.have.property('logStep').to.equal(1.5);
    });
  });

};
