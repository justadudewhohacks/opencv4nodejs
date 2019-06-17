const { expect } = require('chai');

const expectImplementsMethods = (tracker) => {
  expect(tracker).to.have.property('clear').to.be.a('function');
  expect(tracker).to.have.property('init').to.be.a('function');
  expect(tracker).to.have.property('update').to.be.a('function');
  expect(tracker).to.have.property('getModel').to.be.a('function');
};

module.exports = ({ cv, utils, getTestImg }) => {

  const {
    cvVersionGreaterEqual,
    cvVersionEqual,
    funcShouldRequireArgs
  } = utils

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
        it('should throw if no args', () => {
          expect(() => newTracker().init()).to.throw('Tracker::Init - Error: expected argument 0 to be of type');
        });

        it('can be called with frame and initial box', () => {
          const ret = newTracker().init(getTestImg(), new cv.Rect(0, 0, 10, 10));
          expect(ret).to.true;
        });
      });

      describe('update', () => {
        it('should throw if no args', () => {
          expect(() => newTracker().update()).to.throw('Tracker::Update - Error: expected argument 0 to be of type');
        });

        // update test for TrackerTLD for 3.1.0 and 3.2.0 seem to not finish
        if (!(
          (cvVersionEqual(3, 1, 0) || cvVersionEqual(3, 2, 0))
          && trackerName === 'TrackerTLD'
        )) {
          it('returns bounding box', () => {
            const tracker = newTracker();
            tracker.init(getTestImg(), new cv.Rect(0, 0, 10, 10));
            const rect = tracker.update(getTestImg());
            if (rect !== null) {
              expect(rect).to.be.instanceOf(cv.Rect);
            }
          });
        }
      });

      describe('getModel', () => {

      });
    });
  };

  const generateTrackerTests = TrackerTestGenerator(getTestImg);

  const trackerNames = [
    'TrackerBoosting',
    'TrackerMedianFlow',
    'TrackerMIL',
    'TrackerTLD'
  ];

  const hasCSRT = cvVersionGreaterEqual(3, 4, 1);
  const hasMOSSE = cvVersionGreaterEqual(3, 4, 0);
  const hasKCF = cvVersionGreaterEqual(3, 1, 0);

  if (hasKCF) {
    trackerNames.push('TrackerKCF');
  }

  if (cvVersionGreaterEqual(3, 2, 0)) {
    // trackerNames.push('TrackerGOTURN'); TODO: sample goturn.prototxt
  }
  if (hasCSRT) {
    trackerNames.push('TrackerCSRT');
  }
  if (hasMOSSE) {
    trackerNames.push('TrackerMOSSE');
  }
  trackerNames.forEach((trackerName) => {
    generateTrackerTests(trackerName);
  });

  (cvVersionGreaterEqual(3, 1, 0) ? describe : describe.skip)('MultiTracker', () => {
    describe('add', () => {
      it('addMIL', () => {
        const tracker = new cv.MultiTracker();
        const ret = tracker.addMIL(getTestImg(), new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });

      it('addBOOSTING', () => {
        const tracker = new cv.MultiTracker();
        const ret = tracker.addBOOSTING(getTestImg(), new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });

      it('addMEDIANFLOW', () => {
        const tracker = new cv.MultiTracker();
        const ret = tracker.addMEDIANFLOW(getTestImg(), new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });

      it('addTLD', () => {
        const tracker = new cv.MultiTracker();
        const ret = tracker.addTLD(getTestImg(), new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });

      it('addKCF', () => {
        const tracker = new cv.MultiTracker();
        const ret = tracker.addKCF(getTestImg(), new cv.Rect(0, 0, 10, 10));
        expect(ret).to.true;
      });
      if(hasCSRT){
        it('addCSRT', () => {
          const tracker = new cv.MultiTracker();
          const ret = tracker.addCSRT(getTestImg(), new cv.Rect(0, 0, 10, 10));
          expect(ret).to.true;
        });
      }

      if(hasMOSSE){
        it('addMOSSE', () => {
          const tracker = new cv.MultiTracker();
          const ret = tracker.addMOSSE(getTestImg(), new cv.Rect(0, 0, 10, 10));
          expect(ret).to.true;
        });
      }
    });

    describe('update', () => {
      it('should throw if no args', () => {
        expect(() => (new cv.MultiTracker()).update()).to.throw('MultiTracker::Update - Error: expected argument 0 to be of type');
      });

      it('returns bounding box', () => {
        const tracker = new cv.MultiTracker();
        const methods = ['addMIL', 'addBOOSTING', 'addMEDIANFLOW', 'addTLD', 'addKCF'];
        if (hasKCF) {
          methods.push('addKCF');
        }

        // if (cvVersionGreaterEqual(3, 2, 0)) {
        //   methods.push('addGOTURN');
        // }
        if (hasCSRT) {
          methods.push('addCSRT');
        }
        if (hasMOSSE) {
          methods.push('addMOSSE');
        }

        methods.forEach((addMethod) => {
          tracker[addMethod](getTestImg(), new cv.Rect(0, 0, 10, 10));
        });
        const rects = tracker.update(getTestImg());
        expect(rects).to.be.an('array').lengthOf(methods.length);
        rects.forEach((rect) => {
          expect(rect).to.be.instanceOf(cv.Rect);
        });
      });
    });
  });

};
