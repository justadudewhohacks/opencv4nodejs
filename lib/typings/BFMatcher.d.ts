import {Mat} from "./Mat";
import {DescriptorMatch} from "./DescriptorMatch";

export class BFMatcher {
    constructor(normType: number, crossCheck?: boolean);
    constructor(params: { normType: number, crossCheck?: boolean });
    match(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
    matchAsync(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
    knnMatch(descriptors1: Mat, descriptors2: Mat, k: number): Array<[DescriptorMatch]|[any]>;
    knnMatchAsync(descriptors1: Mat, descriptors2: Mat, k: number): Promise<Array<[DescriptorMatch]|[any]>>;
}
