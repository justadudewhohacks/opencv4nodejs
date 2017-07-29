import { expect } from 'chai';

// TODO: proper deepEquals
exports.deepEquals = (obj0, obj1) => JSON.stringify(obj0) === JSON.stringify(obj1);

exports.expectMetaData = mat => (type, cols, rows) => {
  expect(mat).to.have.property('type').equal(type);
  expect(mat).to.have.property('cols').equal(cols);
  expect(mat).to.have.property('rows').equal(rows);
};
