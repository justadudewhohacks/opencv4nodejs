import { OpenCVBuildEnvParams } from '@u4/opencv-build';
import promisify from './promisify';
import extendWithJsSources from './src';
import raw from './cvloader';
import type * as openCV from '..';

function loadOpenCV(opt?: OpenCVBuildEnvParams): typeof openCV {
  const cvBase = raw(opt);
  if (!cvBase.accumulate) {
    throw Error('failed to load opencv basic accumulate not found.')
  }
  if (!cvBase.blur) {
    throw Error('failed to load opencv basic blur not found.')
  }
  
  // promisify async methods
  let cvObj = promisify(cvBase);
  cvObj = extendWithJsSources(cvObj);
  // add xmodules alias if not present (moved to C++ part)
  // if (!cvObj.xmodules && cvObj.modules)
  //  cvObj.xmodules = cvObj.modules
  return cvObj;
}

const cv = loadOpenCV({ prebuild: 'latestBuild' });
const defExport = { cv };
// duplicate all export for retro-compatibility
for (const key in cv) {
  defExport[key] = cv[key];
}
defExport['cv'] = cv;

export = defExport;
