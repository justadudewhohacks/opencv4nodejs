const { charMax, charMin, ucharMax, shortMax, shortMin, ushortMax, intMax,
  intMin, floatMin, floatMax, doubleMin, doubleMax } = require('./typeRanges');

module.exports = function(cv, type) {
  switch (type) {
    case cv.CV_8UC1: {
      return ([
        [ucharMax, 0, 0],
        [0, ucharMax, 0],
        [0, 0, ucharMax],
        [ucharMax, 0, 0]
      ]);
    }
    case cv.CV_8UC2: {
      return ([
        [[ucharMax, 0], [0, 0], [0, ucharMax]],
        [[0, 0], [ucharMax, 0], [0, ucharMax]],
        [[0, 0], [0, 0], [ucharMax, 0]],
        [[ucharMax, 0], [0, 0], [0, 0]]
      ]);
    }
    case cv.CV_8UC3: {
      return ([
        [[ucharMax, 0, 0], [0, 0, 0], [0, ucharMax, ucharMax]],
        [[0, 0, ucharMax], [ucharMax, 0, 0], [ucharMax, 0, ucharMax]],
        [[0, 0, ucharMax], [0, 0, 0], [ucharMax, 0, 0]],
        [[ucharMax, 0, ucharMax], [0, 0, 0], [0, 0, ucharMax]]
      ]);
    }
    case cv.CV_8UC4: {
      return ([
        [[ucharMax, 0, 0, 0], [ucharMax, 0, 0, 0], [0, ucharMax, ucharMax, ucharMax]],
        [[0, 0, ucharMax, 0], [ucharMax, ucharMax, 0, 0], [ucharMax, 0, ucharMax, ucharMax]],
        [[0, 0, ucharMax, 0], [ucharMax, 0, 0, 0], [ucharMax, 0, 0, ucharMax]],
        [[ucharMax, 0, ucharMax, 0], [ucharMax, 0, 0, 0], [0, 0, ucharMax, ucharMax]]
      ]);
    }
    case cv.CV_8SC1: {
      return ([
        [charMax, charMin, charMin],
        [charMin, charMax, charMin],
        [charMin, charMin, charMax],
        [charMax, charMin, charMin]
      ]);
    }
    case cv.CV_8SC2: {
      return ([
        [[charMax, charMin], [charMin, charMin], [charMin, charMax]],
        [[charMin, charMin], [charMax, charMin], [charMin, charMax]],
        [[charMin, charMin], [charMin, charMin], [charMax, charMin]],
        [[charMax, charMin], [charMin, charMin], [charMin, charMin]]
      ]);
    }
    case cv.CV_8SC3: {
      return ([
        [[charMax, charMin, charMin], [charMin, charMin, charMin], [charMin, charMax, charMax]],
        [[charMin, charMin, charMax], [charMax, charMin, charMin], [charMax, charMin, charMax]],
        [[charMin, charMin, charMax], [charMin, charMin, charMin], [charMax, charMin, charMin]],
        [[charMax, charMin, charMax], [charMin, charMin, charMin], [charMin, charMin, charMax]]
      ]);
    }
    case cv.CV_8SC4: {
      return ([
        [[charMax, charMin, charMin, charMin], [charMax, charMin, charMin, charMin], [charMin, charMax, charMax, charMax]],
        [[charMin, charMin, charMax, charMin], [charMax, charMax, charMin, charMin], [charMax, charMin, charMax, charMax]],
        [[charMin, charMin, charMax, charMin], [charMax, charMin, charMin, charMin], [charMax, charMin, charMin, charMax]],
        [[charMax, charMin, charMax, charMin], [charMax, charMin, charMin, charMin], [charMin, charMin, charMax, charMax]]
      ]);
    }
    case cv.CV_16UC1: {
      return ([
        [ushortMax, 0, 0],
        [0, ushortMax, 0],
        [0, 0, ushortMax],
        [ushortMax, 0, 0]
      ]);
    }
    case cv.CV_16UC2: {
      return ([
        [[ushortMax, 0], [0, 0], [0, ushortMax]],
        [[0, 0], [ushortMax, 0], [0, ushortMax]],
        [[0, 0], [0, 0], [ushortMax, 0]],
        [[ushortMax, 0], [0, 0], [0, 0]]
      ]);
    }
    case cv.CV_16UC3: {
      return ([
        [[ushortMax, 0, 0], [0, 0, 0], [0, ushortMax, ushortMax]],
        [[0, 0, ushortMax], [ushortMax, 0, 0], [ushortMax, 0, ushortMax]],
        [[0, 0, ushortMax], [0, 0, 0], [ushortMax, 0, 0]],
        [[ushortMax, 0, ushortMax], [0, 0, 0], [0, 0, ushortMax]]
      ]);
    }
    case cv.CV_16UC4: {
      return ([
        [[ushortMax, 0, 0, 0], [ushortMax, 0, 0, 0], [0, ushortMax, ushortMax, ushortMax]],
        [[0, 0, ushortMax, 0], [ushortMax, ushortMax, 0, 0], [ushortMax, 0, ushortMax, ushortMax]],
        [[0, 0, ushortMax, 0], [ushortMax, 0, 0, 0], [ushortMax, 0, 0, ushortMax]],
        [[ushortMax, 0, ushortMax, 0], [ushortMax, 0, 0, 0], [0, 0, ushortMax, ushortMax]]
      ]);
    }
    case cv.CV_16SC1: {
      return ([
        [shortMax, shortMin, shortMin],
        [shortMin, shortMax, shortMin],
        [shortMin, shortMin, shortMax],
        [shortMax, shortMin, shortMin]
      ]);
    }
    case cv.CV_16SC2: {
      return ([
        [[shortMax, shortMin], [shortMin, shortMin], [shortMin, shortMax]],
        [[shortMin, shortMin], [shortMax, shortMin], [shortMin, shortMax]],
        [[shortMin, shortMin], [shortMin, shortMin], [shortMax, shortMin]],
        [[shortMax, shortMin], [shortMin, shortMin], [shortMin, shortMin]]
      ]);
    }
    case cv.CV_16SC3: {
      return ([
        [[shortMax, shortMin, shortMin], [shortMin, shortMin, shortMin], [shortMin, shortMax, shortMax]],
        [[shortMin, shortMin, shortMax], [shortMax, shortMin, shortMin], [shortMax, shortMin, shortMax]],
        [[shortMin, shortMin, shortMax], [shortMin, shortMin, shortMin], [shortMax, shortMin, shortMin]],
        [[shortMax, shortMin, shortMax], [shortMin, shortMin, shortMin], [shortMin, shortMin, shortMax]]
      ]);
    }
    case cv.CV_16SC4: {
      return ([
        [[shortMax, shortMin, shortMin, shortMin], [shortMax, shortMin, shortMin, shortMin], [shortMin, shortMax, shortMax, shortMax]],
        [[shortMin, shortMin, shortMax, shortMin], [shortMax, shortMax, shortMin, shortMin], [shortMax, shortMin, shortMax, shortMax]],
        [[shortMin, shortMin, shortMax, shortMin], [shortMax, shortMin, shortMin, shortMin], [shortMax, shortMin, shortMin, shortMax]],
        [[shortMax, shortMin, shortMax, shortMin], [shortMax, shortMin, shortMin, shortMin], [shortMin, shortMin, shortMax, shortMax]]
      ]);
    }
    case cv.CV_32SC1: {
      return ([
        [intMax, intMin, intMin],
        [intMin, intMax, intMin],
        [intMin, intMin, intMax],
        [intMax, intMin, intMin]
      ]);
    }
    case cv.CV_32SC2: {
      return ([
        [[intMax, intMin], [intMin, intMin], [intMin, intMax]],
        [[intMin, intMin], [intMax, intMin], [intMin, intMax]],
        [[intMin, intMin], [intMin, intMin], [intMax, intMin]],
        [[intMax, intMin], [intMin, intMin], [intMin, intMin]]
      ]);
    }
    case cv.CV_32SC3: {
      return ([
        [[intMax, intMin, intMin], [intMin, intMin, intMin], [intMin, intMax, intMax]],
        [[intMin, intMin, intMax], [intMax, intMin, intMin], [intMax, intMin, intMax]],
        [[intMin, intMin, intMax], [intMin, intMin, intMin], [intMax, intMin, intMin]],
        [[intMax, intMin, intMax], [intMin, intMin, intMin], [intMin, intMin, intMax]]
      ]);
    }
    case cv.CV_32SC4: {
      return ([
        [[intMax, intMin, intMin, intMin], [intMax, intMin, intMin, intMin], [intMin, intMax, intMax, intMax]],
        [[intMin, intMin, intMax, intMin], [intMax, intMax, intMin, intMin], [intMax, intMin, intMax, intMax]],
        [[intMin, intMin, intMax, intMin], [intMax, intMin, intMin, intMin], [intMax, intMin, intMin, intMax]],
        [[intMax, intMin, intMax, intMin], [intMax, intMin, intMin, intMin], [intMin, intMin, intMax, intMax]]
      ]);
    }
    case cv.CV_32FC1: {
      return ([
        [floatMax, floatMin, floatMin],
        [floatMin, -floatMax, -floatMin],
        [floatMin, -floatMin, -floatMax],
        [floatMax, floatMin, floatMin]
      ]);
    }
    case cv.CV_32FC2: {
      return ([
        [[floatMax, floatMin], [floatMin, floatMin], [floatMin, -floatMax]],
        [[floatMin, -floatMin], [floatMax, -floatMin], [-floatMin, floatMax]],
        [[floatMin, floatMin], [floatMin, -floatMin], [-floatMax, floatMin]],
        [[floatMax, -floatMin], [floatMin, floatMin], [floatMin, floatMin]]
      ]);
    }
    case cv.CV_32FC3: {
      return ([
        [[floatMax, -floatMin, floatMin], [floatMin, -floatMin, floatMin], [floatMin, -floatMax, floatMax]],
        [[floatMin, floatMin, -floatMax], [floatMax, floatMin, floatMin], [floatMax, floatMin, floatMax]],
        [[floatMin, floatMin, floatMax], [-floatMin, -floatMin, -floatMin], [floatMax, -floatMin, floatMin]],
        [[-floatMax, floatMin, floatMax], [floatMin, -floatMin, -floatMin], [floatMin, floatMin, floatMax]]
      ]);
    }
    case cv.CV_32FC4: {
      return ([
        [[floatMax, -floatMin, -floatMin, floatMin], [floatMax, floatMin, floatMin, floatMin], [-floatMin, -floatMax, floatMax, floatMax]],
        [[floatMin, floatMin, floatMax, floatMin], [-floatMax, -floatMax, -floatMin, -floatMin], [floatMax, floatMin, floatMax, floatMax]],
        [[floatMin, floatMin, floatMax, -floatMin], [floatMax, floatMin, -floatMin, floatMin], [-floatMax, -floatMin, floatMin, floatMax]],
        [[-floatMax, floatMin, floatMax, floatMin], [floatMax, floatMin, floatMin, -floatMin], [-floatMin, floatMin, floatMax, floatMax]]
      ]);
    }
    case cv.CV_64FC1: {
      return ([
        [doubleMax, doubleMin, doubleMin],
        [doubleMin, -doubleMax, -doubleMin],
        [doubleMin, -doubleMin, -doubleMax],
        [doubleMax, doubleMin, doubleMin]
      ]);
    }
    case cv.CV_64FC2: {
      return ([
        [[doubleMax, doubleMin], [doubleMin, doubleMin], [doubleMin, -doubleMax]],
        [[doubleMin, -doubleMin], [doubleMax, -doubleMin], [-doubleMin, doubleMax]],
        [[doubleMin, doubleMin], [doubleMin, -doubleMin], [-doubleMax, doubleMin]],
        [[doubleMax, -doubleMin], [doubleMin, doubleMin], [doubleMin, doubleMin]]
      ]);
    }
    case cv.CV_64FC3: {
      return ([
        [[doubleMax, -doubleMin, doubleMin], [doubleMin, -doubleMin, doubleMin], [doubleMin, -doubleMax, doubleMax]],
        [[doubleMin, doubleMin, -doubleMax], [doubleMax, doubleMin, doubleMin], [doubleMax, doubleMin, doubleMax]],
        [[doubleMin, doubleMin, doubleMax], [-doubleMin, -doubleMin, -doubleMin], [doubleMax, -doubleMin, doubleMin]],
        [[-doubleMax, doubleMin, doubleMax], [doubleMin, -doubleMin, -doubleMin], [doubleMin, doubleMin, doubleMax]]
      ]);
    }
    case cv.CV_64FC4: {
      return ([
        [[doubleMax, -doubleMin, -doubleMin, doubleMin], [doubleMax, doubleMin, doubleMin, doubleMin], [-doubleMin, -doubleMax, doubleMax, doubleMax]],
        [[doubleMin, doubleMin, doubleMax, doubleMin], [-doubleMax, -doubleMax, -doubleMin, -doubleMin], [doubleMax, doubleMin, doubleMax, doubleMax]],
        [[doubleMin, doubleMin, doubleMax, -doubleMin], [doubleMax, doubleMin, -doubleMin, doubleMin], [-doubleMax, -doubleMin, doubleMin, doubleMax]],
        [[-doubleMax, doubleMin, doubleMax, doubleMin], [doubleMax, doubleMin, doubleMin, -doubleMin], [-doubleMin, doubleMin, doubleMax, doubleMax]]
      ]);
    }
    default: {
      return null;
    }
  }
};
