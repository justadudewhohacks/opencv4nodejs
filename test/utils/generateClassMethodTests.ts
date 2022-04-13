import { generateAPITests, getDefaultAPITestOpts } from './generateAPITests';
import type openCV from '../../typings';
import { APITestOpts } from '../tests/model';

const generateClassMethodTestsFactory = (cv: typeof openCV) => (opts: Partial<APITestOpts>) => {
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