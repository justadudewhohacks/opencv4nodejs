import { Mat } from "./Mat";
import { DescriptorMatch } from "./DescriptorMatch";

export interface BFMatcherProps {
    normType: number;
    crossCheck?: boolean;
}

export class BFMatcher {
    constructor(normType: number, crossCheck?: boolean);
    constructor(params: BFMatcherProps);
    match(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
    matchAsync(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
    matchAsync(descriptors1: Mat, descriptors2: Mat, callback: (err: unknown, ret: Array<DescriptorMatch>) => void): void;
    // TODO replace unknown by the proper type.
    knnMatch(descriptors1: Mat, descriptors2: Mat, k: number): Array<[DescriptorMatch] | [unknown]>;
    // TODO replace unknown by the proper type.
    knnMatchAsync(descriptors1: Mat, descriptors2: Mat, k: number): Promise<Array<[DescriptorMatch] | [unknown]>>;
    knnMatchAsync(descriptors1: Mat, descriptors2: Mat, k: number, callback: (err: unknown, ret: Array<[DescriptorMatch] | [unknown]>) => void): void;
}
