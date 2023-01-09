import { assert, expect } from 'chai';
import {
  AGASTDetectorProps,
  BRISKDetectorProps,
  FeatureDetector,
  GFTTDetectorProps,
  KeyPoint,
  MSERDetectorProps,
  SIFTDetectorParams,
  SURFDetectorPrams,
  // KeyPointDetector,
} from '../../../typings';
import { generateAPITests } from '../../utils/generateAPITests';
import { assertPropsWithValue } from '../../utils/testUtils';
import { TestContext } from '../model';

// type AllDetector = SURFDetector | SIFTDetector | AKAZEDetector | BRISKDetector | MSERDetector | ORBDetector;

type DetectorProps = BRISKDetectorProps | GFTTDetectorProps | MSERDetectorProps | AGASTDetectorProps | SIFTDetectorParams | SURFDetectorPrams;

export default function (args: TestContext) {
  const { cv, getTestImg250 } = args;

  // KeyPointDetector | typeof KeyPointDetector
  return (defaults: DetectorProps, customProps: {args: string[], values: Array<number | boolean>}, Detector: any, implementsCompute = true) => {
    const getDut = (): FeatureDetector => (typeof Detector === 'function' ? new Detector() : Detector);

    describe('constructor', () => {
      if (defaults) {
        it('should use default values if no args', () => {
          assertPropsWithValue(new Detector(), defaults);
        });

        it('should use default values if empty args', () => {
          assertPropsWithValue(new Detector({}), defaults);
        });
      }

      if (customProps) {
        it('should be constructable with custom props', () => {
          const props: {[key: string]: number | boolean} = {};
          customProps.args.forEach((arg: string, i) => {
            props[arg] = customProps.values[i];
          });
          /* eslint-disable new-parens */
          const detector = new (Detector.bind.apply(Detector, [null].concat(customProps.values)));
          assertPropsWithValue(detector, props);
        });

        it('should be constructable with custom props object', () => {
          const props: {[key: string]: number | boolean} = {};
          customProps.args.forEach((arg: string, i) => {
            props[arg] = customProps.values[i];
          });
          assertPropsWithValue(new Detector(props), props);
        });
      }

      it('should have function detect', () => {
        const detector = getDut();
        expect(detector).to.have.property('detect').to.be.a('function');
      });

      it('should have function compute', () => {
        const detector = getDut();
        expect(detector).to.have.property('compute').to.be.a('function');
      });
    });

    describe('detect', () => {
      generateAPITests({
        getDut,
        methodName: 'detect',
        methodNameSpace: 'FeatureDetector',
        getRequiredArgs: () => ([
          getTestImg250(),
        ]),
        expectOutput: (keyPoints) => {
          expect(keyPoints).to.be.a('array');
          assert(keyPoints.length > 0, 'no KeyPoints detected');
          keyPoints.forEach((kp) => assert(kp instanceof cv.KeyPoint));
        },
      });
    });

    if (implementsCompute) {
      describe('compute', () => {
        let dut: FeatureDetector;
        let keyPoints : KeyPoint[];
        before(() => {
          dut = getDut();
          keyPoints = dut.detect(getTestImg250());
        });
        generateAPITests({
          getDut,
          methodName: 'compute',
          methodNameSpace: 'FeatureDetector',
          getRequiredArgs: () => ([
            getTestImg250(),
            keyPoints,
          ]),
          expectOutput: (desc) => {
            assertPropsWithValue(desc, { rows: keyPoints.length });
          },
        });
      });
    }
  };
}
