//  Copyright 2022 Kohei Suzuki
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  Created by Kohei Suzuki on 2022/02/13.
//

#ifndef COMPNAL_PYBIND11_TYPE_HPP_
#define COMPNAL_PYBIND11_TYPE_HPP_

#include "../../compnal-cpp/src/type/all.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

namespace compnal {
namespace wrapper {

namespace py = pybind11;

//The following does not bring in anything else from the pybind11 namespace except for literals.
using namespace pybind11::literals;

void pybind11TypeHalfInt(py::module &m) {
   
   using CppC = compnal::type::HalfInt;
   auto  py_c = py::class_<CppC>(m, "HalfInt", py::module_local());
   
   //Constructors
   py_c.def(py::init<>());
   py_c.def(py::init<int>(), "value"_a);
   py_c.def(py::init<double>(), "value"_a);
   
   
   
}





} //namespace wrapper
} //namespace compnal




#endif /* COMPNAL_PYBIND11_TYPE_HPP_ */
