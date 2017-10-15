const trackerParamTests = require('./trackerParamTests');
const trackerTests = require('./trackerTests');

describe('tracking', () => {
  trackerParamTests();
  trackerTests();
});
