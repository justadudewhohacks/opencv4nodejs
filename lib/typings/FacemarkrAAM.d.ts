import { Facemark } from "./Facemark";
export * as cv from './openCV.js';

declare module "./openCV.js" {
    export class FacemarkAAM extends Facemark { }
}