export class TrackerBoostingParams implements TrackerBoostingParamsI {
  readonly numClassifiers: number;
  readonly samplerOverlap: number;
  readonly samplerSearchFactor: number;
  readonly iterationInit: number;
  readonly featureSetNumFeatures: number;
  constructor();
}
