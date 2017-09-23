const cv = global.dut;
const CascadeClassifierTests = require('./CascadeClassifierTests');
const HOGDescriptorTests = require('./HOGDescriptorTests');

describe('objdetect', () => {
  CascadeClassifierTests();
  HOGDescriptorTests();
});
