const { generateAPITests, getDefaultAPITestOpts } = require('./generateAPITests');

exports.generateClassMethodTests = (opts) => {
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
      getDut: () => global.dut,
      getRequiredArgs: () => [getClassInstance(), ...getRequiredArgs()],
      explicitHasRequiredArgs: true
    }))
  })

}