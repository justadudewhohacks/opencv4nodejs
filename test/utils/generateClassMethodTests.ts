import type openCV from '@u4/opencv4nodejs';
import { generateAPITests, getDefaultAPITestOpts } from './generateAPITests';
import { APITestOpts } from '../tests/model';

const generateClassMethodTestsFactory = (cv: typeof openCV) => (opts: Partial<APITestOpts>) => {
  const {
    getClassInstance,
    classNameSpace,
    methodNameSpace,
    getRequiredArgs,
    methodName,
  } = getDefaultAPITestOpts(opts);

  describe(`${classNameSpace}::${methodName}`, () => {
    generateAPITests({
      ...opts,
      getDut: getClassInstance,
      methodNameSpace: classNameSpace,
    });
  });

  describe(`${methodNameSpace}::${methodName}`, () => {
    generateAPITests({
      ...opts,
      getDut: () => cv,
      getRequiredArgs: () => [getClassInstance()].concat(getRequiredArgs ? getRequiredArgs() : []),
    });
  });
};

export default generateClassMethodTestsFactory;
