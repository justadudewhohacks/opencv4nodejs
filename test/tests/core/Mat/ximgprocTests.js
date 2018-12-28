const cv = global.dut;

const {
    generateAPITests,
    assertMetaData,
} = global.utils;

module.exports = () => {
    describe('guidedFilter', () => {
        if (!cv.xmodules.ximgproc) {
            it('compiled without ximgproc');
            return;
        }

        const getDut = () => new cv.Mat(100, 100, cv.CV_8UC3);

        const guide = new cv.Mat(100, 100, cv.CV_8UC3);
        const radius = 3;
        const eps = 100;
        const ddepth = -1;
        generateAPITests({
            getDut,
            methodName: 'guidedFilter',
            methodNameSpace: 'Mat',
            getRequiredArgs: () => ([
                guide,
                radius,
                eps
            ]),
            getOptionalArgs: () => ([
                ddepth
            ]),
            expectOutput: (res) => {
                assertMetaData(res)(100, 100, cv.CV_8UC3);
            }
        });
    });
}