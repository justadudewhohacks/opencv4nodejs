const cv = global.dut;
const {
  readTestImage,
  funcShouldRequireArgs
} = global.utils;

const { expect } = require('chai');

const expectImplementsMethods = (tracker) => {
  expect(tracker).to.have.property('clear').to.be.a('function');
  expect(tracker).to.have.property('init').to.be.a('function');
  expect(tracker).to.have.property('update').to.be.a('function');
  expect(tracker).to.have.property('getModel').to.be.a('function');
};

const TrackerTestGenerator = getTestImg => (trackerName) => {
  const newTracker = () => new cv[trackerName]();
  const newTrackerParams = () => new cv[`${trackerName}Params`]();

  describe(trackerName, () => {
    describe('constructor', () => {
      it('can be constructed with default params', () => {
        expectImplementsMethods(newTracker());
      });

      if (['TrackerBoosting', 'TrackerKCF', 'TrackerMIL'].some(name => name === trackerName)) {
        it('can be constructed with params', () => {
          expectImplementsMethods(newTracker(newTrackerParams()));
        });
      } else if (trackerName === 'TrackerMedianFlow') {
        it('can be constructed with params', () => {
          const pointsInGrid = 10;
          expectImplementsMethods(newTracker(pointsInGrid));
        });
      }
    });

    describe('init', () => {
      funcShouldRequireArgs(() => (newTracker()).init());

      it('can be called with frame and initial box', () => {
        const ret = newTracker().init(getTestImg(), new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });
    });

    describe('update', () => {
      funcShouldRequireArgs(() => (newTracker()).update());

      it('returns bounding box', () => {
        const tracker = newTracker();
        tracker.init(getTestImg(), new cv.Rect(0, 0, 10, 10));
        const rect = tracker.update(getTestImg());
        expect(rect).to.be.instanceOf(cv.Rect);
      });
    });

    describe('getModel', () => {

    });
  });
};

module.exports = () => {
  let testImg;

  before(() => {
    testImg = readTestImage();
  });

  const generateTrackerTests = TrackerTestGenerator(() => testImg);


  const trackerNames = [
    'TrackerBoosting',
    'TrackerMedianFlow',
    'TrackerMIL',
    'TrackerTLD'
  ];

  if (cv.version.minor > 0) {
    trackerNames.push('TrackerKCF');
  }

  if (cv.version.minor > 1) {
    // trackerNames.push('TrackerGOTURN'); TODO: sample goturn.prototxt
  }

  trackerNames.forEach((trackerName) => {
    generateTrackerTests(trackerName);
  });

  (cv.version.minor > 0 ? describe : describe.skip)('MultiTracker', () => {
    describe('add', () => {
      it('addMIL', () => {
        const tracker = new cv.MultiTracker();
        const ret = tracker.addMIL(testImg, new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });

      it('addBOOSTING', () => {
        const tracker = new cv.MultiTracker();
        const ret = tracker.addBOOSTING(testImg, new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });

      it('addMEDIANFLOW', () => {
        const tracker = new cv.MultiTracker();
        const ret = tracker.addMEDIANFLOW(testImg, new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });

      it('addTLD', () => {
        const tracker = new cv.MultiTracker();
        const ret = tracker.addTLD(testImg, new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });

      it('addKCF', () => {
        const tracker = new cv.MultiTracker();
        const ret = tracker.addKCF(testImg, new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });
    });

    describe('update', () => {
      funcShouldRequireArgs(() => (new cv.MultiTracker()).update());

      it('returns bounding box', () => {
        const tracker = new cv.MultiTracker();
        ['addMIL', 'addBOOSTING', 'addMEDIANFLOW', 'addTLD', 'addKCF'].forEach((addMethod) => {
          tracker[addMethod](testImg, new cv.Rect(0, 0, 10, 10));
        });
        const rects = tracker.update(testImg);
        expect(rects).to.be.an('array').lengthOf(5);
        rects.forEach((rect) => {
          expect(rect).to.be.instanceOf(cv.Rect);
        });
      });
    });
  });
};
