// Copyright 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020 Lovell Fuller and contributors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include <vips/vips8>
#include "example.h"
#include "common.h"

namespace example {
  // typedef enum {
  // VIPS_INTERPRETATION_ERROR = -1,
  // VIPS_INTERPRETATION_MULTIBAND = 0,
  // VIPS_INTERPRETATION_B_W = 1,
  // VIPS_INTERPRETATION_HISTOGRAM = 10,
  // VIPS_INTERPRETATION_XYZ = 12,
  // VIPS_INTERPRETATION_LAB = 13,
  // VIPS_INTERPRETATION_CMYK = 15,
  // VIPS_INTERPRETATION_LABQ = 16,
  // VIPS_INTERPRETATION_RGB = 17,
  // VIPS_INTERPRETATION_CMC = 18,
  // VIPS_INTERPRETATION_LCH = 19,
  // VIPS_INTERPRETATION_LABS = 21,
  // VIPS_INTERPRETATION_sRGB = 22,
  // VIPS_INTERPRETATION_YXY = 23,
  // VIPS_INTERPRETATION_FOURIER = 24,
  // VIPS_INTERPRETATION_RGB16 = 25,
  // VIPS_INTERPRETATION_GREY16 = 26,
  // VIPS_INTERPRETATION_MATRIX = 27,
  // VIPS_INTERPRETATION_scRGB = 28,
  // VIPS_INTERPRETATION_HSV = 29,
  // VIPS_INTERPRETATION_LAST = 30
  // } VipsInterpretation;

  Napi::Value guessColorspace(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Object options = info[0].As<Napi::Object>();
    vips::VImage image;
    sharp::ImageType imageType = sharp::ImageType::UNKNOWN;
    sharp::InputDescriptor *input = NULL;
    try {
      input = sharp::CreateInputDescriptor(options.Get("input").As<Napi::Object>());
      std::tie(image, imageType) = OpenInput(input);
      VipsImage *vips_image = image.get_image();
      VipsInterpretation vipsInterp = vips_image_guess_interpretation(vips_image);
      switch (vipsInterp) {
        // TODO(mm): What is the best value to work with? Enum? String?
        case VIPS_INTERPRETATION_ERROR:
          return Napi::String::New(env, "error");
        case VIPS_INTERPRETATION_sRGB:
          return Napi::String::New(env, "srgb");
        default:
          return Napi::Number::New(env, vipsInterp);
      }
    } catch (vips::VError const &err) {
      // TODO(mm): Figure out how Sharp likes to deal with errors...
      std::cerr << "ERROR in guessColorspace: " << err.what() << std::endl;
      return env.Null();
    }
  }
}  // namespace example
