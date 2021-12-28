import { Facemark } from "./Facemark";

export * as cv from './cv';

declare module "./cv.js" {
    export class FacemarkLBF extends Facemark {}
}