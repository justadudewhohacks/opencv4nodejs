import { assert } from 'chai';

exports.assertPropsWithValue = obj => (props) => {
  Object.keys(props).forEach(key =>
    assert(props[key] === obj[key], `${key} - expected: ${props[key]}, have: ${obj[key]}`)
  );
};
