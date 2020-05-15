const sharp = require('../build/Release/sharp.node');

function guessColorspace () {
  return sharp.guessColorspace(this.options);
}

/**
 * Decorate the Sharp class with our example function
 * @private
 */
module.exports = function (Sharp) {
  Object.assign(Sharp.prototype, { guessColorspace });
};
