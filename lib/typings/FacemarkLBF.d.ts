import { Facemark } from "./Facemark";
import './openCV.js';

declare module "./openCV.js" {
    export class FacemarkLBF extends Facemark {}
}