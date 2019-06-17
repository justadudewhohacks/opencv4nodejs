const { assert, expect } = require('chai');

module.exports = function ({ cv, utils, getPeoplesTestImg }) {

  const {
    generateAPITests,
    assertError,
    cvVersionGreaterEqual,
    clearTmpData,
    getTmpDataFilePath
  } = utils;

  const HISTOGRAM_NORM_TYPE = cvVersionGreaterEqual(4, 0, 0) ? cv.HOGHistogramNormType.L2Hys : 0

  const peopleDetectorHog = new cv.HOGDescriptor();
  peopleDetectorHog.setSVMDetector(cv.HOGDescriptor.getDefaultPeopleDetector());

  const getTestHOG = () => peopleDetectorHog;
  const getTestMatC1 = () => new cv.Mat(40, 40, cv.CV_8U);

  describe('constructor', () => {
    it('should be constructable with default args', () => {
      const hog = new cv.HOGDescriptor();
      ['winSize', 'blockSize', 'blockStride', 'cellSize'].forEach(
        prop => expect(hog).to.have.property(prop).instanceOf(cv.Size)
      );
    });

    it('should be constructable with custom args', () => {
      const hog = new cv.HOGDescriptor(
        new cv.Size(40, 40),
        new cv.Size(20, 20),
        new cv.Size(10, 10),
        new cv.Size(30, 30),
        18,
        2,
        1.8,
        HISTOGRAM_NORM_TYPE,
        0.4,
        true,
        64,
        true
      );
      [{ p: 'winSize', dim: 40 }, { p: 'blockSize', dim: 20 }, { p: 'blockStride', dim: 10 }, { p: 'cellSize', dim: 30 }].forEach(
        (pv) => {
          expect(hog).to.have.property(pv.p).instanceOf(cv.Size);
          const { width, height } = hog[pv.p];
          expect(width).to.equal(pv.dim);
          expect(height).to.equal(pv.dim);
        }
      );
      expect(hog).to.have.property('nbins').to.equal(18);
      expect(hog).to.have.property('derivAperture').to.equal(2);
      expect(hog).to.have.property('winSigma').to.equal(1.8);
      expect(hog).to.have.property('L2HysThreshold').to.equal(0.4);
      expect(hog).to.have.property('gammaCorrection').to.be.true;
      expect(hog).to.have.property('signedGradient').to.be.true;
    });

    it('should be constructable with custom args object', () => {
      const hog = new cv.HOGDescriptor({
        winSize: new cv.Size(40, 40),
        blockSize: new cv.Size(20, 20),
        blockStride: new cv.Size(10, 10),
        cellSize: new cv.Size(30, 30),
        nbins: 18,
        derivAperture: 2,
        winSigma: 1.8,
        histogramNormType: HISTOGRAM_NORM_TYPE,
        L2HysThreshold: 0.4,
        gammaCorrection: true,
        numLevels: 64,
        signedGradient: true
      });
      [{ p: 'winSize', dim: 40 }, { p: 'blockSize', dim: 20 }, { p: 'blockStride', dim: 10 }, { p: 'cellSize', dim: 30 }].forEach(
        (pv) => {
          expect(hog).to.have.property(pv.p).instanceOf(cv.Size);
          const { width, height } = hog[pv.p];
          expect(width).to.equal(pv.dim);
          expect(height).to.equal(pv.dim);
        }
      );
      expect(hog).to.have.property('nbins').to.equal(18);
      expect(hog).to.have.property('derivAperture').to.equal(2);
      expect(hog).to.have.property('winSigma').to.equal(1.8);
      expect(hog).to.have.property('L2HysThreshold').to.equal(0.4);
      expect(hog).to.have.property('gammaCorrection').to.be.true;
      expect(hog).to.have.property('signedGradient').to.be.true;
    });

    it('should implement compute', () => {
      const hog = new cv.HOGDescriptor();
      expect(hog).to.have.property('compute').to.be.a('function');
    });

    it('should implement computeAsync', () => {
      const hog = new cv.HOGDescriptor();
      expect(hog).to.have.property('computeAsync').to.be.a('function');
    });
  });

  it('getDaimlerPeopleDetector', () => {
    expect(cv.HOGDescriptor.getDaimlerPeopleDetector()).to.be.an('array');
  });

  it('getDefaultPeopleDetector', () => {
    expect(cv.HOGDescriptor.getDefaultPeopleDetector()).to.be.an('array');
  });

  it('setSVMDetector', () => {
    expect(() => new cv.HOGDescriptor().setSVMDetector(cv.HOGDescriptor.getDefaultPeopleDetector())).to.not.throw();
  });

  it('checkDetectorSize', () => {
    expect(getTestHOG().checkDetectorSize()).to.be.a('boolean');
  });

  describe('save and load', () => {
    beforeEach(() => { clearTmpData(); });
    afterEach(() => { clearTmpData(); });

    it('should save and load from xml', () => {
      const hog = new cv.HOGDescriptor({
        winSize: new cv.Size(40, 40),
        blockSize: new cv.Size(20, 20),
        blockStride: new cv.Size(10, 10),
        cellSize: new cv.Size(30, 30),
        nbins: 18,
        derivAperture: 2,
        winSigma: 1.8,
        histogramNormType: HISTOGRAM_NORM_TYPE,
        L2HysThreshold: 0.4,
        gammaCorrection: true,
        numLevels: 64,
        signedGradient: true
      });
      const file = getTmpDataFilePath('testHOG.xml');
      hog.save(file);
      const hogNew = new cv.HOGDescriptor();
      hogNew.load(file);
      expect(hog).to.deep.equal(hogNew);
    });
  });

  describe('compute', () => {
    const expectOutput = (desc) => {
      expect(desc).to.be.an('array');
      expect(desc.length).to.be.above(0);
    };

    const expectOutputCallbacked = done => (err, desc) => {
      expectOutput(desc);
      done();
    };

    const expectOutputPromisified = done => (desc) => {
      expectOutput(desc);
      done();
    };

    const hog = new cv.HOGDescriptor({
      winSize: new cv.Size(40, 40),
      blockSize: new cv.Size(20, 20),
      blockStride: new cv.Size(10, 10),
      cellSize: new cv.Size(10, 10),
      nbins: 9
    });

    const winStride = new cv.Size(3, 3);
    const padding = new cv.Size(3, 3);
    const invalidLocations = [new cv.Point(50, 50), undefined, new cv.Point(50, 150)];

    const otherSyncTests = () => {
      it('should be callable with single channel img', () => {
        expectOutput(hog.compute(
          getPeoplesTestImg()
        ));
      });

      it('should throw if locations invalid', () => {
        assertError(
          () => hog.compute(
            getPeoplesTestImg(),
            winStride,
            padding,
            invalidLocations
          ),
          'expected array element at index 1 to be of type Point2'
        );
      });

      it('should throw if locations invalid for opt arg object', () => {
        assertError(
          () => hog.compute(
            getPeoplesTestImg(),
            { locations: invalidLocations }
          ),
          'expected array element at index 1 to be of type Point2'
        );
      });
    };

    const otherAsyncCallbackedTests = () => {
      it('should be callable with single channel img', (done) => {
        hog.computeAsync(
          getTestMatC1(),
          expectOutputCallbacked(done)
        );
      });

      it('should throw if locations invalid', (done) => {
        hog.computeAsync(
          getPeoplesTestImg(),
          winStride,
          padding,
          invalidLocations,
          (err) => {
            try {
              expect(err).to.be.an('error');
              assert.include(err.toString(), 'expected array element at index 1 to be of type Point2');
              done();
            } catch (e) {
              done(e);
            }
          }
        );
      });

      it('should throw if locations invalid for opt arg object', (done) => {
        hog.computeAsync(
          getPeoplesTestImg(),
          { locations: invalidLocations },
          (err) => {
            try {
              expect(err).to.be.an('error');
              assert.include(err.toString(), 'expected array element at index 1 to be of type Point2');
              done();
            } catch (e) {
              done(e);
            }
          }
        );
      });
    };

    const otherAsyncPromisedTests = () => {
      it('should be callable with single channel img', (done) => {
        hog.computeAsync(
          getTestMatC1()
        ).then(expectOutputPromisified(done)).catch(done);
      });
    };

    generateAPITests({
      getDut: () => hog,
      methodName: 'compute',
      methodNameSpace: 'HOGDescriptor',
      getRequiredArgs: () => ([
        getPeoplesTestImg()
      ]),
      getOptionalArgsMap: () => ([
        ['winStride', new cv.Size(3, 3)],
        ['padding', new cv.Size(3, 3)],
        ['locations', [new cv.Point(50, 50), new cv.Point(150, 50), new cv.Point(50, 150)]]
      ]),
      expectOutput,
      otherSyncTests,
      otherAsyncCallbackedTests,
      otherAsyncPromisedTests
    });
  });

  describe('computeGradient', () => {
    const expectOutput = (result) => {
      expect(result).to.have.property('grad').instanceOf(cv.Mat);
      expect(result).to.have.property('angleOfs').instanceOf(cv.Mat);
    };

    generateAPITests({
      getDut: () => getTestHOG(),
      methodName: 'computeGradient',
      methodNameSpace: 'HOGDescriptor',
      getRequiredArgs: () => ([
        getPeoplesTestImg()
      ]),
      getOptionalArgsMap: () => ([
        ['paddingTL', new cv.Size(3, 3)],
        ['paddingBr', new cv.Size(3, 3)]
      ]),
      expectOutput
    });
  });

  describe('detect', () => {
    const hitThreshold = 0.5;
    const winStride = new cv.Size(8, 8);
    const padding = new cv.Size(4, 4);

    const searchLocations = [];

    describe('detect', () => {
      const expectOutput = (result) => {
        expect(result).to.have.property('foundLocations').be.an('array');
        expect(result).to.have.property('weights').be.an('array');
        expect(result.foundLocations.length).to.be.above(0);
        expect(result.weights.length).to.be.above(0);
      };

      generateAPITests({
        getDut: () => getTestHOG(),
        methodName: 'detect',
        methodNameSpace: 'HOGDescriptor',
        getRequiredArgs: () => ([
          getPeoplesTestImg()
        ]),
        getOptionalArgsMap: () => ([
          ['hitThreshold', hitThreshold],
          ['winStride', winStride],
          ['padding', padding],
          ['searchLocations', searchLocations]
        ]),
        expectOutput
      });
    });

    describe('detectROI', () => {
      const expectOutput = (result) => {
        expect(result).to.have.property('foundLocations').be.an('array');
        expect(result).to.have.property('confidences').be.an('array');
      };

      const locations = searchLocations;
      generateAPITests({
        getDut: () => getTestHOG(),
        methodName: 'detectROI',
        methodNameSpace: 'HOGDescriptor',
        getRequiredArgs: () => ([
          getPeoplesTestImg(),
          locations
        ]),
        getOptionalArgsMap: () => ([
          ['hitThreshold', hitThreshold],
          ['winStride', winStride],
          ['padding', padding]
        ]),
        expectOutput
      });
    });

    describe('detectMultiScale', () => {
      const expectOutput = (result) => {
        expect(result).to.have.property('foundLocations').be.an('array');
        expect(result).to.have.property('foundWeights').be.an('array');
        expect(result.foundLocations.length).to.be.above(0);
        expect(result.foundWeights.length).to.be.above(0);
        result.foundLocations.forEach(loc => expect(loc).instanceOf(cv.Rect));
        result.foundWeights.forEach(loc => expect(loc).to.be.a('number'));
      };

      generateAPITests({
        getDut: () => getTestHOG(),
        methodName: 'detectMultiScale',
        methodNameSpace: 'HOGDescriptor',
        getRequiredArgs: () => ([
          getPeoplesTestImg()
        ]),
        getOptionalArgsMap: () => ([
          ['hitThreshold', hitThreshold],
          ['winStride', winStride],
          ['padding', padding],
          ['scale', 1.1],
          ['finalThreshold', 0.1],
          ['useMeanshiftGrouping', true]
        ]),
        expectOutput
      });
    });

    describe('detectMultiScaleROI', () => {
      const expectOutput = (result) => {
        expect(result).be.an('array');
      };

      const makeDetectionROI = (scale, locations, confidences) => {
        const detectionROI = new cv.DetectionROI();
        detectionROI.scale = scale;
        detectionROI.locations = locations;
        detectionROI.confidences = confidences;
        return detectionROI;
      };

      const locations = [makeDetectionROI(0.5, searchLocations, [0.3, 0.3, 0.4]), makeDetectionROI(0.8, searchLocations, [0.3, 0.3, 0.4])];
      generateAPITests({
        getDut: () => getTestHOG(),
        methodName: 'detectMultiScaleROI',
        methodNameSpace: 'HOGDescriptor',
        getRequiredArgs: () => ([
          getPeoplesTestImg(),
          locations
        ]),
        getOptionalArgsMap: () => ([
          ['hitThreshold', hitThreshold],
          ['groupThreshold', 1]
        ]),
        expectOutput
      });
    });
  });

  describe('groupRectangles', () => {
    const expectOutput = (result) => {
      expect(result).to.be.an('array');
      result.forEach(rect => expect(rect).instanceOf(cv.Rect));
    };
    const rectList = [new cv.Rect(0, 0, 10, 10), new cv.Rect(0, 0, 20, 20)];
    const weights = [0.5, 1.0];
    const groupThreshold = 1;
    const eps = 2.0;

    generateAPITests({
      getDut: () => getTestHOG(),
      methodName: 'groupRectangles',
      methodNameSpace: 'HOGDescriptor',
      getRequiredArgs: () => ([
        rectList,
        weights,
        groupThreshold,
        eps
      ]),
      expectOutput
    });
  });

};
