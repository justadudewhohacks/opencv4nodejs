const charMax = 127;
const charMin = -charMax - 1;
const ucharMax = (charMax * 2) + 1;

const shortMax = 32767;
const shortMin = -shortMax - 1;
const ushortMax = (shortMax * 2) + 1;

const intMax = 2147483647;
const intMin = -intMax - 1;


const floatMin = 0.0000000001;
const floatMax = 0.9999999999;
//const floatMin = 1.8E-38;
//const floatMax = 3.4E+38;

const doubleMin = 2.2E-308;
const doubleMax = 1.79E+308;

module.exports = {
  charMax,
  charMin,
  ucharMax,
  shortMax,
  shortMin,
  ushortMax,
  intMax,
  intMin,
  floatMin,
  floatMax,
  doubleMin,
  doubleMax
};
