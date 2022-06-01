
import { cv } from "./utils";


try {
  console.log('');
  console.log('1 Dims');
  const mat1 = new cv.Mat([4, 5, 6] as any, cv.CV_8UC3);
  //const mat1 = new cv.Mat([[
  //    [1, 2, 3.3],
  //    [4, 5, 6],
  //  ]], cv.CV_32F);
  //
  console.log(mat1.getDataAsArray());
} catch (e) {
  console.log(e);
}

try {
  console.log('');
  console.log('2 Dims');
  const mat2 = new cv.Mat([[4, 5, 6]] as any, cv.CV_32FC3);
  //const mat1 = new cv.Mat([[
  //    [1, 2, 3.3],
  //    [4, 5, 6],
  //  ]], cv.CV_32F);
  //
  console.log(mat2.getDataAsArray());
} catch (e) {
  console.log(e);
}


try {
  console.log('');
  console.log('3 Dims');
  const mat3 = new cv.Mat([[[4, 5, 6]]] as any, cv.CV_32FC3);
  //const mat1 = new cv.Mat([[
  //    [1, 2, 3.3],
  //    [4, 5, 6],
  //  ]], cv.CV_32F);
  //
  console.log(mat3.getDataAsArray());
} catch (e) {

}


try {
  console.log('');
  console.log('4 Dims');
  const mat4 = new cv.Mat([[[[4, 5, 6]]]] as any, cv.CV_32FC3);
  //const mat1 = new cv.Mat([[
  //    [1, 2, 3.3],
  //    [4, 5, 6],
  //  ]], cv.CV_32F);
  //
  console.log(mat4.getDataAsArray());
} catch (e) {

}
