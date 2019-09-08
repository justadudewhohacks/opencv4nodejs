const cv = require('opencv4nodejs')

if (!cv) {
  throw new Error('failed to require opencv4nodejs')
}