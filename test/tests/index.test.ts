/* eslint-disable no-console */
import { expect } from 'chai';
import cv from '@u4/opencv4nodejs';
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
import imgHashTestSuite from './img_hash';
import { TestContext } from './model';

const modules = [
  'core', 'imgproc', 'calib3d', 'features2d', 'io',
  'dnn', 'ml', 'objdetect', 'photo', 'video',
];

const xmodules = [
  'face', 'text', 'tracking', 'xfeatures2d', 'ximgproc', 'img_hash',
];

describe('cv', () => {
  const toTest: {[key: string]: boolean} = {
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
    img_hash: true,
  };
  // phash branch only
  // Object.keys(toTest).forEach((m) => { toTest[m] = false; });
  // toTest.img_hash = true;

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

  let builtModules = modules.concat(xmodules);
  if (process.env.APPVEYOR_BUILD) {
    // OpenCV installed via choco does not include contrib modules
    builtModules = modules;
  }
  if (process.env.TEST_MODULE_LIST) {
    builtModules = process.env.TEST_MODULE_LIST.split(',');
  }

  const opencvVersionString = `${cv.version.major}.${cv.version.minor}.${cv.version.revision}`;

  // no more mandatory environement version variable
  // it('OpenCV version should match', () => {
  //   expect((process.env.OPENCV_VERSION || '').substr(0, 5)).to.equal(
  //     // on osx latest opencv package for major version is installed via brew
  //     process.platform === 'darwin' ? `${cv.version.major}` : opencvVersionString
  //   )
  // })

  const ctxt = new TestContext(cv, getTestImg, getPeoplesTestImg);

  before(() => {
    testImg = ctxt.readTestImage();
    peoplesTestImg = ctxt.readPeoplesTestImage();
  });

  // dnn module for OpenCV 3.2 and lower not supported
  if (ctxt.cvVersionLowerThan(3, 3, 0)) {
    builtModules = builtModules.filter((m) => m !== 'dnn');
  }

  console.log('envs are:');
  console.log('OPENCV_VERSION:', process.env.OPENCV_VERSION);
  console.log('TEST_MODULE_LIST:', process.env.TEST_MODULE_LIST);
  console.log('APPVEYOR_BUILD:', process.env.APPVEYOR_BUILD);
  console.log('process.platform:', process.platform);
  console.log();
  console.log('OpenCV version is:', opencvVersionString);
  console.log('compiled with the following modules:', cv.xmodules);
  console.log(`${builtModules.length} expected modules to be built:`, builtModules);
  const liveModules = Object.entries(cv.modules).filter((a) => a[1]).map((a) => a[0]);
  console.log(`${liveModules.length} visible  modules:`, liveModules);

  it('all modules should be built', () => {
    // xfeatures2d is a non free module not available on debian disto
    builtModules.filter((m) => m !== 'xfeatures2d').forEach((m) => expect(cv.modules).to.have.property(m));
  });
  if (toTest.core && cv.modules.core) {
    describe('core', () => coreTestSuite(ctxt));
  }
  if (toTest.imgproc && cv.modules.imgproc) {
    describe('imgproc', () => imgprocTestSuite(ctxt));
  }
  if (toTest.calib3d && cv.modules.calib3d) {
    describe('calib3d', () => calib3dTestSuite(ctxt));
  }
  if (toTest.features2d && cv.modules.features2d) {
    describe('features2d', () => features2dTestSuite(ctxt));
  }
  if (toTest.io && cv.modules.io) {
    describe('io', () => ioTestSuite(ctxt));
  }
  if (toTest.dnn && cv.modules.dnn) {
    describe('dnn', () => dnnTestSuite(ctxt));
  }
  if (toTest.machinelearning && cv.modules.machinelearning) {
    describe('machinelearning', () => machinelearningTestSuite(ctxt));
  }
  if (toTest.objdetect && cv.modules.objdetect) {
    describe('objdetect', () => objdetectTestSuite(ctxt));
  }
  if (toTest.photo && cv.modules.photo) {
    describe('photo', () => photoTestSuite(ctxt));
  }
  if (toTest.video && cv.modules.video) {
    describe('video', () => videoTestSuite(ctxt));
  }
  if (toTest.face && cv.modules.face) {
    describe('face', () => faceTestSuite(ctxt));
  }
  if (toTest.text && cv.modules.text) {
    describe('text', () => textTestSuite(ctxt));
  }
  if (toTest.tracking && cv.modules.tracking) {
    describe('tracking', () => trackingTestSuite(ctxt));
  }
  if (toTest.xfeatures2d && cv.modules.xfeatures2d) {
    describe('xfeatures2d', () => xfeatures2dTestSuite(ctxt));
  }
  if (toTest.ximgproc && cv.modules.ximgproc) {
    describe('ximgproc', () => ximgprocTestSuite(ctxt));
  }
  if (toTest.img_hash && cv.modules.img_hash) {
    describe('img_hash', () => imgHashTestSuite(ctxt));
  }
});
