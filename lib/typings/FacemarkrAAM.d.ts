import { Facemark } from "./Facemark";
export * as cv from './cv';

declare module "./openCV.js" {
    export class FacemarkAAM extends Facemark { }
}