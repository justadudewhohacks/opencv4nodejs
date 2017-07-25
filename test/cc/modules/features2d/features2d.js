const { features2d } = require('../../../../');

describe('features2d', () => {
  describe('GFTTDetector', () => { 
    it.only('', () => {
      console.log(features2d.GFTTDetector);
      const det0 = new features2d.GFTTDetector(true);
      console.log("test");
      console.log(det0);

    });
  });
});
