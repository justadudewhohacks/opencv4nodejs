const fs = require('fs')
const path = require('path')

function resolvePath(filePath, file) {
  if (!filePath) {
    return undefined
  }
  return (file ? path.resolve(filePath, file) : path.resolve(filePath)).replace(/\\/g, '/')
}

module.exports = {
  resolvePath
}
