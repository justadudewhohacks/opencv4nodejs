import { FeatureDetector } from './FeatureDetector.d';

export class AKAZEDetector extends FeatureDetector {
  readonly descriptorType: number;
  readonly descriptorSize: number;
  readonly descriptorChannels: number;
  readonly nOctaves: number;
  readonly nOctaveLayers: number;
  readonly diffusivity: number;
  readonly threshold: number;
  constructor(descriptorType?: number, descriptorSize?: number, descriptorChannels?: number, threshold?: number, nOctaves?: number, nOctaveLayers?: number, diffusivity?: number);
  constructor(params: { descriptorType?: number, descriptorSize?: number, descriptorChannels?: number, threshold?: number, nOctaves?: number, nOctaveLayers?: number, diffusivity?: number });
}
