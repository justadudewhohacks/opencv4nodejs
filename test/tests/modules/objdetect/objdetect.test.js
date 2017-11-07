const CascadeClassifierTests = require('./CascadeClassifierTests');
const HOGDescriptorTests = require('./HOGDescriptorTests');
const DetectionROITests = require('./DetectionROITests');

describe('objdetect', () => {
  DetectionROITests();
  CascadeClassifierTests();
  HOGDescriptorTests();
});
