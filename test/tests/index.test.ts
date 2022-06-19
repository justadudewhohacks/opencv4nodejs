/* eslint-disable no-console */
import { expect } from 'chai';
import cv from '@u4/opencv4nodejs';
import Utils from '../utils';
import coreTestSuite from './core';
import imgprocTestSuite from './imgproc';
import calib3dTestSuite from './calib3d';
import features2dTestSuite from './features2d';
import ioTestSuite from './io';
import dnnTestSuite from './dnn';
import machinelearningTestSuite from './machinelearning';
import faceTestSuite from './face';
import objdetectTestSuite from './objdetect';
import photoTestSuite from './photo';
import textTestSuite from './text';
import trackingTestSuite from './tracking';
import videoTestSuite from './video';
import xfeatures2dTestSuite from './xfeatures2d';
import ximgprocTestSuite from './ximgproc';

const utils = Utils(cv);

const modules = [
  'core', 'imgproc', 'calib3d', 'features2d', 'io',
  'dnn', 'ml', 'objdetect', 'photo', 'video',
];

const xmodules = [
  'face', 'text', 'tracking', 'xfeatures2d', 'ximgproc',
];

describe('cv', () => {
  const toTest = {
    core: true,
    imgproc: false, // to fix
    calib3d: true,
    features2d: true,
    io: true,
    dnn: true,
    machinelearning: true,
    objdetect: false, // to fix
    photo: true,
    video: true,
    face: true,
    text: true,
    tracking: true,
    xfeatures2d: true,
    ximgproc: true,
  };
  // Object.keys(toTest).forEach(m => toTest[m] =  false);
  // toTest.core = true;

  let testImg = null;
  let peoplesTestImg = null;

  const getTestImg = () => {
    if (testImg === null) {
      throw new Error('getTestImg not defined, before hook not called yet');
    }
    return testImg;
  };

  const getPeoplesTestImg = () => {
    if (peoplesTestImg === null) {
      throw new Error('getPeoplesTestImg not defined, before hook not called yet');
    }
    return peoplesTestImg;
  };

  before(() => {
    testImg = utils.readTestImage();
    peoplesTestImg = utils.readPeoplesTestImage();
  });

  let builtModules = modules.concat(xmodules);
  if (process.env.APPVEYOR_BUILD) {
    // OpenCV installed via choco does not include contrib modules
    builtModules = modules;
  }
  if (process.env.TEST_MODULE_LIST) {
    builtModules = process.env.TEST_MODULE_LIST.split(',');
  }
  // dnn module for OpenCV 3.2 and lower not supported
  if (utils.cvVersionLowerThan(3, 3, 0)) {
    builtModules = builtModules.filter((m) => m !== 'dnn');
  }

  const opencvVersionString = `${cv.version.major}.${cv.version.minor}.${cv.version.revision}`;

  console.log('envs are:');
  console.log('OPENCV_VERSION:', process.env.OPENCV_VERSION);
  console.log('TEST_MODULE_LIST:', process.env.TEST_MODULE_LIST);
  console.log('APPVEYOR_BUILD:', process.env.APPVEYOR_BUILD);
  console.log('process.platform:', process.platform);
  console.log();
  console.log('OpenCV version is:', opencvVersionString);
  console.log('compiled with the following modules:', cv.xmodules);
  console.log('expected modules to be built:', builtModules);

  // no more mandatory environement version variable
  // it('OpenCV version should match', () => {
  //   expect((process.env.OPENCV_VERSION || '').substr(0, 5)).to.equal(
  //     // on osx latest opencv package for major version is installed via brew
  //     process.platform === 'darwin' ? `${cv.version.major}` : opencvVersionString
  //   )
  // })

  it('all modules should be built', () => {
    // xfeatures2d is a non free module not available on debian disto
    builtModules.filter((m) => m !== 'xfeatures2d').forEach((m) => expect(cv.modules).to.have.property(m));
  });
  if (toTest.core && cv.modules.core) {
    describe('core', () => coreTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.imgproc && cv.modules.imgproc) {
    describe('imgproc', () => imgprocTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.calib3d && cv.modules.calib3d) {
    describe('calib3d', () => calib3dTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.features2d && cv.modules.features2d) {
    describe('features2d', () => features2dTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.io && cv.modules.io) {
    describe('io', () => ioTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.dnn && cv.modules.dnn) {
    describe('dnn', () => dnnTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.machinelearning && cv.modules.machinelearning) {
    describe('machinelearning', () => machinelearningTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.objdetect && cv.modules.objdetect) {
    describe('objdetect', () => objdetectTestSuite({
      cv, utils, getTestImg, getPeoplesTestImg,
    }));
  }
  if (toTest.photo && cv.modules.photo) {
    describe('photo', () => photoTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.video && cv.modules.video) {
    describe('video', () => videoTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.face && cv.modules.face) {
    describe('face', () => faceTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.text && cv.modules.text) {
    describe('text', () => textTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.tracking && cv.modules.tracking) {
    describe('tracking', () => trackingTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.xfeatures2d && cv.modules.xfeatures2d) {
    describe('xfeatures2d', () => xfeatures2dTestSuite({ cv, utils, getTestImg }));
  }
  if (toTest.ximgproc && cv.modules.ximgproc) {
    describe('ximgproc', () => ximgprocTestSuite({ cv, utils, getTestImg }));
  }
});
