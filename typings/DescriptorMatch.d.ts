export class DescriptorMatch {
  readonly queryIdx: number;
  readonly trainIdx: number;
  readonly distance: number;

  constructor(queryIdx?: number, trainIdx?: number, distance?: number);
}
