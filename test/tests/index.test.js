const cv = require('../requireCv')();
const utils = require('../utils')(cv);

const coreTestSuite = require('./core')

describe('cv', () => {

  const {
    readTestImage
  } = utils

  let testImg = null;
  const getTestImg = () => {
    if (testImg === null) {
      throw new Error('getTestImg not defined, before hook not called yet');

    }
    return testImg;
  };
  before(() => {
    testImg = utils.readTestImage();
  });

  if (cv.modules.core) {
    describe('core', () => coreTestSuite({ cv, utils, getTestImg }));
  }

})
