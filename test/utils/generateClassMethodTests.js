const { generateAPITests, getDefaultAPITestOpts } = require('./generateAPITests');

const generateClassMethodTestsFactory = (cv) => (opts) => {
  const {
    getClassInstance,
    classNameSpace,
    methodNameSpace,
    getRequiredArgs,
    methodName
  } = getDefaultAPITestOpts(opts)

  describe(`${classNameSpace}::${methodName}`, () => {
    generateAPITests(Object.assign({}, opts, {
      getDut: getClassInstance,
      methodNameSpace: classNameSpace
    }))
  })

  describe(`${methodNameSpace}::${methodName}`, () => {
    generateAPITests(Object.assign({}, opts, {
      getDut: () => cv,
      getRequiredArgs: () => [getClassInstance(), ...getRequiredArgs()],
      explicitHasRequiredArgs: true
    }))
  })

}

module.exports = generateClassMethodTestsFactory;