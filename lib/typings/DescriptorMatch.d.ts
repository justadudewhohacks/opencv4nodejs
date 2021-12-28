export * as cv from './cv';

declare module "./openCV.js" {
  export class DescriptorMatch {
    readonly queryIdx: number;
    readonly trainIdx: number;
    readonly distance: number;
  }
}
