import { FeatureDetector } from './FeatureDetector.d';

export interface AKAZEDetectorProps {
  descriptorType?: number;
  descriptorSize?: number;
  descriptorChannels?: number;
  threshold?: number;
  nOctaves?: number;
  nOctaveLayers?: number;
  diffusivity?: number;
}

export class AKAZEDetector extends FeatureDetector {
  readonly descriptorType: number;
  readonly descriptorSize: number;
  readonly descriptorChannels: number;
  readonly nOctaves: number;
  readonly nOctaveLayers: number;
  readonly diffusivity: number;
  readonly threshold: number;
  constructor(descriptorType?: number, descriptorSize?: number, descriptorChannels?: number, threshold?: number, nOctaves?: number, nOctaveLayers?: number, diffusivity?: number);
  constructor(params: AKAZEDetectorProps);
}

export class AKAZEDescriptorType {
  static DESCRIPTOR_MLDB: number;
  static DESCRIPTOR_KAZE_UPRIGHT: number;
}

export class KAZEDiffusivityType {
  static DIFF_PM_G2: number;
  static DIFF_WEICKERT: number;
}