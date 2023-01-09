import { expect } from "chai";
import { PHash } from "../../../typings";
import { generateAPITests } from "../../utils/generateAPITests";
import { TestContext } from "../model";

export default (args: TestContext) => (ImgHash: typeof PHash) => {
  const { getTestImg } = args;

  describe("constructor", () => {
    it("is constructable without args", () => {
      expect(() => new ImgHash()).to.not.throw();
    });
  });

  describe("api tests", () => {
    let imgHash: PHash;

    before(() => {
      imgHash = new ImgHash();
    });

    describe("compute", () => {
      const expectOutput = (res) => {
        expect(res).to.be.an("array");
      };

      generateAPITests({
        getDut: () => imgHash,
        methodName: "compute",
        methodNameSpace: "ImgHashBase",
        getRequiredArgs: () => [getTestImg().bgrToGray()],
        expectOutput,
      });

      it("should compute pHash", () => {
        const imageData = getTestImg();

        const pHashValue = imgHash.compute(imageData);

        expect(pHashValue).to.be.array();
        expect(pHashValue).to.be.ofSize(8);
        expect(pHashValue).to.be.equalTo([
          152, 99, 43, 180, 174, 196, 101, 105,
        ]);
      });

      it("should compute pHash in async", async () => {
        const imageData = getTestImg();

        const pHashValue = await imgHash.computeAsync(imageData);

        expect(pHashValue).to.be.array();
        expect(pHashValue).to.be.ofSize(8);
        expect(pHashValue).to.be.equalTo([
          152, 99, 43, 180, 174, 196, 101, 105,
        ]);
      });

      it("should compare pHashes", () => {
        const result = imgHash.compare(
          [153, 99, 43, 180, 174, 196, 101, 105],
          [152, 99, 43, 180, 174, 196, 101, 105]
        );

        expect(result).to.be.equal(1);
      });

      it("should compare pHashes in async", async () => {
        const result = await imgHash.compareAsync(
          [153, 99, 43, 180, 174, 196, 101, 105],
          [152, 99, 43, 180, 174, 196, 101, 105]
        );

        expect(result).to.be.equal(1);
      });
    });
  });
};
