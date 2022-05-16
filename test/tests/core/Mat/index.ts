import { TestContext } from '../../model';

import MatTests from './MatTests';
import accessorTests from './accessorTests';
import constructorTestsFromJsArray from './constructorTestsFromJsArray';
import constructorTestsFromFillVector from './constructorTestsFromFillVector';
import operatorTests from './operatorTests';

export default function (args: TestContext) {
  describe('Mat', () => MatTests(args));
  describe('accessors', () => accessorTests(args));
  describe('constructor', () => {
    describe('from array', () => constructorTestsFromJsArray(args));
    describe('from fill vector', () => constructorTestsFromFillVector(args));
  });
  describe('operators', () => operatorTests(args));
}
