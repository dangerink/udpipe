// This file is part of UDPipe <http://github.com/ufal/udpipe/>.
//
// Copyright 2015 Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <fstream>
#include <string>
#include <iostream>

#include "model.h"
#include "model_morphodita_parsito.h"

namespace ufal {
namespace udpipe {

const string model::DEFAULT;
const string model::TOKENIZER_NORMALIZED_SPACES = "normalized_spaces";
const string model::TOKENIZER_PRESEGMENTED = "presegmented";
const string model::TOKENIZER_RANGES = "ranges";

model* model::load(const char* fname) {
  ifstream in(fname, ifstream::in | ifstream::binary);
  if (!in.is_open()) return nullptr;
  return load(in);
}

model* model::load(istream& is) {
  char len;
  string prefix = "UdPipe load: ";
  bool has_char = (bool)is.get(len);
  if (!has_char) {
    cout << prefix + "no chars in buffer.\n"; 
    return nullptr;
  }
  string name(len, ' ');
  if (!is.read(&name[0], len)) {
    cout << prefix + "can't get name.\n";
    return nullptr;
  }

  if (name == "morphodita_parsito") { 
    cout << prefix + "name match ok:" + name + "\n";
    return model_morphodita_parsito::load(is);
  }

  cout << prefix + "name match fails:" + name + "\n";
  return nullptr;
}

} // namespace udpipe
} // namespace ufal
