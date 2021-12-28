export * as cv from './cv';

declare module "./openCV.js" {
  export class TrackerBoostingParams {
    readonly numClassifiers: number;
    readonly samplerOverlap: number;
    readonly samplerSearchFactor: number;
    readonly iterationInit: number;
    readonly featureSetNumFeatures: number;
    constructor();
  }
}