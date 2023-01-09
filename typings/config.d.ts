export const xmodules: {
  core: boolean;
  imgproc: boolean;
  calib3d: boolean;
  features2d: boolean;
  io: boolean;
  dnn: boolean;
  face: boolean;
  text: boolean;
  tracking: boolean;
  xfeatures2d: boolean;
  ximgproc: boolean;
  photo: boolean;
  objdetect: boolean;
  machinelearning: boolean;
  video: boolean;
  img_hash: boolean;
}

export const version: {
  major: number;
  minor: number;
  revision: number;
}

export const modules: typeof xmodules;
