export * as cv from './cv';

declare module "./cv.js" {
  export class TrackerMILParams {
    readonly samplerInitInRadius: number;
    readonly samplerSearchWinSize: number;
    readonly samplerTrackInRadius: number;
    readonly samplerInitMaxNegNum: number;
    readonly samplerTrackMaxPosNum: number;
    readonly samplerTrackMaxNegNum: number;
    readonly featureSetNumFeatures: number;
    constructor();
  }
}