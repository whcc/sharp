'use strict';

const assert = require('assert');
const sharp = require('../../');
const fixtures = require('../fixtures');

describe('Example', function () {
  it('Returns a colorspace', function () {
    assert.strictEqual('srgb', sharp(fixtures.inputJpgWithPortraitExif1).guessColorspace());
  });
});
