const opencv = require('../');

const { imread } = opencv;

exports.imreadPromised = file => new Promise((resolve, reject) => {
  imread(file, (err, img) => {
    if (err) {
      return reject(err);
    }
    return resolve(img);
  });
});
