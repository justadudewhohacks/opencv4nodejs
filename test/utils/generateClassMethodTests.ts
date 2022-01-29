import { generateAPITests, getDefaultAPITestOpts } from './generateAPITests';
import type openCV from '../../typings';

const generateClassMethodTestsFactory = (cv: typeof openCV) => (opts) => {
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
      getRequiredArgs: () => [getClassInstance()].concat(getRequiredArgs ? getRequiredArgs() : [])
    }))
  })
}

export default generateClassMethodTestsFactory;