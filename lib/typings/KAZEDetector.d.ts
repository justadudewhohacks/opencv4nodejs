import { FeatureDetector } from './FeatureDetector.d';

export class KAZEDetector extends FeatureDetector {
  readonly extended: boolean;
  readonly upright: boolean;
  readonly nOctaves: number;
  readonly nOctaveLayers: number;
  readonly diffusivity: number;
  readonly threshold: number;
  constructor(extended?: boolean, upright?: boolean, threshold?: number, nOctaves?: number, nOctaveLayers?: number, diffusivity?: number);
  constructor(params: { extended?: boolean, upright?: boolean, threshold?: number, nOctaves?: number, nOctaveLayers?: number, diffusivity?: number });
}
