'use strict';

const assert = require('assert');
const sharp = require('../../');
const fixtures = require('../fixtures');

describe('Example', function () {
  it('Returns a colorspace', function () {
    const space = sharp(fixtures.inputJpgAdobeRGB).guessColorspace();
    assert.strictEqual('srgb', space);
  });

  it('Can output an sRGB with a custom color profile.', function (done) {
    sharp(fixtures.inputJpgAdobeRGB)
      .withMetadata()
      .toFile(fixtures.path('output-asrgb1.jpg'), done);
  });
});
