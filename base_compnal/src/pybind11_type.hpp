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
   
   using HalfInt = compnal::type::HalfInt;
   auto  py_c = py::class_<HalfInt>(m, "HalfInt", py::module_local());
   
   //Constructors
   py_c.def(py::init<>());
   py_c.def(py::init<double>(), "value"_a);

   // Operator Overloading: Unary Operators
   py_c.def("__pos__", [](const HalfInt &self) { return +self; }, py::is_operator());
   py_c.def("__neg__", [](const HalfInt &self) { return -self; }, py::is_operator());

   // Operator Overloading: Compound Assignment Operators
   py_c.def("__iadd__",      [](HalfInt &self, const HalfInt &rhs) { return self += rhs; }, py::is_operator());
   py_c.def("__iadd__",      [](HalfInt &self, const int      rhs) { return self += rhs; }, py::is_operator());
   py_c.def("__iadd__",      [](HalfInt &self, const double   rhs) { return self += rhs; }, py::is_operator());
   py_c.def("__isub__",      [](HalfInt &self, const HalfInt &rhs) { return self -= rhs; }, py::is_operator());
   py_c.def("__isub__",      [](HalfInt &self, const int      rhs) { return self -= rhs; }, py::is_operator());
   py_c.def("__isub__",      [](HalfInt &self, const double   rhs) { return self -= rhs; }, py::is_operator());
   py_c.def("__imul__",      [](HalfInt &self, const HalfInt &rhs) { return self *= rhs; }, py::is_operator());
   py_c.def("__imul__",      [](HalfInt &self, const int      rhs) { return self *= rhs; }, py::is_operator());
   py_c.def("__imul__",      [](HalfInt &self, const double   rhs) { return self *= rhs; }, py::is_operator());
   py_c.def("__itruediv__" , [](HalfInt &self, const HalfInt &rhs) { return self /= rhs; }, py::is_operator());
   py_c.def("__itruediv__" , [](HalfInt &self, const int      rhs) { return self /= rhs; }, py::is_operator());
   py_c.def("__itruediv__" , [](HalfInt &self, const double   rhs) { return self /= rhs; }, py::is_operator());
   py_c.def("__ifloordiv__", [](HalfInt &self, const HalfInt &rhs) { return self = HalfInt{static_cast<int>(self/rhs)}; }, py::is_operator());
   py_c.def("__ifloordiv__", [](HalfInt &self, const int      rhs) { return self = HalfInt{static_cast<int>(self/rhs)}; }, py::is_operator());
   py_c.def("__ifloordiv__", [](HalfInt &self, const double   rhs) { return self = HalfInt{static_cast<int>(self/rhs)}; }, py::is_operator());
   py_c.def("__ipow__"     , [](HalfInt &self, const HalfInt &rhs) { return self = HalfInt{std::pow(0.5*self.GetInteger(), rhs)}; }, py::is_operator());
   py_c.def("__ipow__"     , [](HalfInt &self, const int      rhs) { return self = HalfInt{std::pow(0.5*self.GetInteger(), rhs)}; }, py::is_operator());
   py_c.def("__ipow__"     , [](HalfInt &self, const double   rhs) { return self = HalfInt{std::pow(0.5*self.GetInteger(), rhs)}; }, py::is_operator());

   // Operator Overloading: Addition Operator
   py_c.def("__add__"  , [](const HalfInt &self, const HalfInt &rhs) { return self + rhs ; }, py::is_operator());
   py_c.def("__add__"  , [](const HalfInt &self, const int      rhs) { return self + rhs ; }, py::is_operator());
   py_c.def("__add__"  , [](const HalfInt &self, const double   rhs) { return self + rhs ; }, py::is_operator());
   py_c.def("__radd__" , [](const HalfInt &self, const HalfInt &lhs) { return lhs  + self; }, py::is_operator());
   py_c.def("__radd__" , [](const HalfInt &self, const int      lhs) { return lhs  + self; }, py::is_operator());
   py_c.def("__radd__" , [](const HalfInt &self, const double   lhs) { return lhs  + self; }, py::is_operator());
   
   // Operator Overloading: Subtraction Operator
   py_c.def("__sub__"  , [](const HalfInt &self, const HalfInt &rhs) { return self - rhs ; }, py::is_operator());
   py_c.def("__sub__"  , [](const HalfInt &self, const int      rhs) { return self - rhs ; }, py::is_operator());
   py_c.def("__sub__"  , [](const HalfInt &self, const double   rhs) { return self - rhs ; }, py::is_operator());
   py_c.def("__rsub__" , [](const HalfInt &self, const HalfInt &lhs) { return lhs  - self; }, py::is_operator());
   py_c.def("__rsub__" , [](const HalfInt &self, const int      lhs) { return lhs  - self; }, py::is_operator());
   py_c.def("__rsub__" , [](const HalfInt &self, const double   lhs) { return lhs  - self; }, py::is_operator());
   
   // Operator Overloading: Multiplication Operator
   py_c.def("__mul__"  , [](const HalfInt &self, const HalfInt &rhs) { return self * rhs ; }, py::is_operator());
   py_c.def("__mul__"  , [](const HalfInt &self, const int      rhs) { return self * rhs ; }, py::is_operator());
   py_c.def("__mul__"  , [](const HalfInt &self, const double   rhs) { return self * rhs ; }, py::is_operator());
   py_c.def("__rmul__" , [](const HalfInt &self, const HalfInt &lhs) { return lhs  * self; }, py::is_operator());
   py_c.def("__rmul__" , [](const HalfInt &self, const int      lhs) { return lhs  * self; }, py::is_operator());
   py_c.def("__rmul__" , [](const HalfInt &self, const double   lhs) { return lhs  * self; }, py::is_operator());

   // Operator Overloading: Division Operator
   py_c.def("__truediv__"  , [](const HalfInt &self, const HalfInt &rhs) { return self / rhs ; }, py::is_operator());
   py_c.def("__truediv__"  , [](const HalfInt &self, const int      rhs) { return self / rhs ; }, py::is_operator());
   py_c.def("__truediv__"  , [](const HalfInt &self, const double   rhs) { return self / rhs ; }, py::is_operator());
   py_c.def("__rtruediv__" , [](const HalfInt &self, const HalfInt &lhs) { return lhs  / self; }, py::is_operator());
   py_c.def("__rtruediv__" , [](const HalfInt &self, const int      lhs) { return lhs  / self; }, py::is_operator());
   py_c.def("__rtruediv__" , [](const HalfInt &self, const double   lhs) { return lhs  / self; }, py::is_operator());
   
   py_c.def("__floordiv__"  , [](const HalfInt &self, const HalfInt &rhs) { return static_cast<int>(self / rhs ); }, py::is_operator());
   py_c.def("__floordiv__"  , [](const HalfInt &self, const int      rhs) { return static_cast<int>(self / rhs ); }, py::is_operator());
   py_c.def("__floordiv__"  , [](const HalfInt &self, const double   rhs) { return static_cast<int>(self / rhs ); }, py::is_operator());
   py_c.def("__rfloordiv__" , [](const HalfInt &self, const HalfInt &lhs) { return static_cast<int>(lhs  / self); }, py::is_operator());
   py_c.def("__rfloordiv__" , [](const HalfInt &self, const int      lhs) { return static_cast<int>(lhs  / self); }, py::is_operator());
   py_c.def("__rfloordiv__" , [](const HalfInt &self, const double   lhs) { return static_cast<int>(lhs  / self); }, py::is_operator());
   
   // Operator Overloading: Power Operator
   py_c.def("__pow__"  , [](const HalfInt &self, const HalfInt &rhs) { return std::pow(0.5*self.GetInteger(), 0.5*rhs.GetInteger()); }, py::is_operator());
   py_c.def("__pow__"  , [](const HalfInt &self, const int      rhs) { return std::pow(0.5*self.GetInteger(), rhs); }, py::is_operator());
   py_c.def("__pow__"  , [](const HalfInt &self, const double   rhs) { return std::pow(0.5*self.GetInteger(), rhs); }, py::is_operator());
   py_c.def("__rpow__" , [](const HalfInt &self, const HalfInt &lhs) { return std::pow(0.5*lhs.GetInteger(), 0.5*self.GetInteger()); }, py::is_operator());
   py_c.def("__rpow__" , [](const HalfInt &self, const int      lhs) { return std::pow(lhs, 0.5*self.GetInteger()); }, py::is_operator());
   py_c.def("__rpow__" , [](const HalfInt &self, const double   lhs) { return std::pow(lhs, 0.5*self.GetInteger()); }, py::is_operator());
   
   // Operator Overloading: Equality Operator
   py_c.def("__eq__", [](const HalfInt &self, const HalfInt &rhs) { return self == rhs; }, py::is_operator());
   py_c.def("__eq__", [](const HalfInt &self, const int      rhs) { return self == rhs; }, py::is_operator());
   py_c.def("__eq__", [](const HalfInt &self, const double   rhs) { return self == rhs; }, py::is_operator());

   // Operator Overloading: Inequality Operator
   py_c.def("__ne__", [](const HalfInt &self, const HalfInt &rhs) { return self != rhs; }, py::is_operator());
   py_c.def("__ne__", [](const HalfInt &self, const int      rhs) { return self != rhs; }, py::is_operator());
   py_c.def("__ne__", [](const HalfInt &self, const double   rhs) { return self != rhs; }, py::is_operator());

   // Operator Overloading: Comparison Operator
   py_c.def("__lt__", [](const HalfInt &self, const HalfInt &rhs) { return self <  rhs; }, py::is_operator());
   py_c.def("__lt__", [](const HalfInt &self, const int      rhs) { return self <  rhs; }, py::is_operator());
   py_c.def("__lt__", [](const HalfInt &self, const double   rhs) { return self <  rhs; }, py::is_operator());
   py_c.def("__le__", [](const HalfInt &self, const HalfInt &rhs) { return self <= rhs; }, py::is_operator());
   py_c.def("__le__", [](const HalfInt &self, const int      rhs) { return self <= rhs; }, py::is_operator());
   py_c.def("__le__", [](const HalfInt &self, const double   rhs) { return self <= rhs; }, py::is_operator());
   py_c.def("__gt__", [](const HalfInt &self, const HalfInt &rhs) { return self >  rhs; }, py::is_operator());
   py_c.def("__gt__", [](const HalfInt &self, const int      rhs) { return self >  rhs; }, py::is_operator());
   py_c.def("__gt__", [](const HalfInt &self, const double   rhs) { return self >  rhs; }, py::is_operator());
   py_c.def("__ge__", [](const HalfInt &self, const HalfInt &rhs) { return self >= rhs; }, py::is_operator());
   py_c.def("__ge__", [](const HalfInt &self, const int      rhs) { return self >= rhs; }, py::is_operator());
   py_c.def("__ge__", [](const HalfInt &self, const double   rhs) { return self >= rhs; }, py::is_operator());
   
}





} //namespace wrapper
} //namespace compnal




#endif /* COMPNAL_PYBIND11_TYPE_HPP_ */
