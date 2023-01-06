const imgHashTestsFactory = require('./imgHashTests')

module.exports = ({ cv, utils, getTestImg }) => {

  const {
    cvVersionGreaterEqual
  } = utils

  const imgHashTests = imgHashTestsFactory({ cv, utils, getTestImg })

  describe('ImgHash', () => {

    describe('PHash', () => {
      imgHashTests(cv.PHash);
    });

  });

};
