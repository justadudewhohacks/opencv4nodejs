export * as cv from './openCV.js';

declare module "./openCV.js" {
  export class DescriptorMatch {
    readonly queryIdx: number;
    readonly trainIdx: number;
    readonly distance: number;
  }
}
