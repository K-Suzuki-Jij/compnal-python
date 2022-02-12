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
//  Created by Kohei Suzuki on 2021/11/10.
//

#ifndef COMPNAL_PYBIND11_SOLVER_EXACT_DIAG_HPP_
#define COMPNAL_PYBIND11_SOLVER_EXACT_DIAG_HPP_

#include "../../compnal-cpp/src/solver/all.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

namespace py = pybind11;

//The following does not bring in anything else from the pybind11 namespace except for literals.
using namespace pybind11::literals;

void pybind11SolverDiagonalizationMethod(py::module &m) {
   py::enum_<compnal::solver::DiagMethod>(m, "DiagMethod")
      .value("LANCZOS", compnal::solver::DiagMethod::LANCZOS)
      .value("LOBPCG", compnal::solver::DiagMethod::LOBPCG);
}

template<class ModelClass>
void pybind11SolverExactDiag(py::module &m, const std::string &mtype_str) {
   
   using ED = compnal::solver::ExactDiag<ModelClass>;
   using CRS = compnal::sparse_matrix::CRS<typename ModelClass::ValueType>;
   auto str = std::string("_ExactDiag") + mtype_str;
   
   py::class_<ED>(m, str.c_str(), py::module_local())
   .def(py::init<const ModelClass&>(), "model"_a)
   .def(py::init<const ModelClass&, compnal::sparse_matrix::ParametersAll&>(), "model"_a, "params"_a)
   .def_readonly("model", &ED::model)
   .def_readonly("params", &ED::params)
   .def("get_eigenvectors", &ED::GetEigenvectors)
   .def("get_eigenvalues", &ED::GetEigenvalues)
   .def("calculate_expectation_value", &ED::CalculateExpectationValue, "m"_a, "site"_a, "level"_a = 0)
   .def("calculate_correlation_function", py::overload_cast<const CRS&, const int, const int>(&ED::CalculateCorrelationFunction, py::const_), "m"_a, "site"_a, "level"_a = 0)
   .def("calculate_correlation_function",
        py::overload_cast<const CRS&, const int, const CRS&, const int, const int>(&ED::CalculateCorrelationFunction),
        "m_1"_a, "site_1"_a, "m_2"_a, "site_2"_a, "level"_a = 0)
   .def("calculate_correlation_function",
        py::overload_cast<const CRS&, const int, const CRS&, const int, const CRS&, const int, const int>(&ED::CalculateCorrelationFunction),
        "m_1"_a, "site_1"_a, "m_2"_a, "site_2"_a, "m_3"_a, "site_3"_a, "level"_a = 0)
   .def("calculate_correlation_function",
        py::overload_cast<const CRS&, const int, const CRS&, const int, const CRS&, const int, const CRS&, const int, const int>(&ED::CalculateCorrelationFunction),
        "m_1"_a, "site_1"_a, "m_2"_a, "site_2"_a, "m_3"_a, "site_3"_a, "m_4"_a, "site_4"_a, "level"_a = 0)
   .def("calculate_ground_state", [](ED &self) {
      py::scoped_ostream_redirect stream(
          std::cout,                                // std::ostream&
          py::module_::import("sys").attr("stdout") // Python output
      );
      self.CalculateGroundState();
   })
   .def("calculate_target_state", [](ED &self, const int target_sector) {
      py::scoped_ostream_redirect stream(
          std::cout,                                // std::ostream&
          py::module_::import("sys").attr("stdout") // Python output
      );
      self.CalculateTargetState(target_sector);
   }, "target_sector"_a);
   
   auto mkci_str = std::string("ExactDiag");
   m.def(mkci_str.c_str(), [](const ModelClass &model) {
      return compnal::solver::ExactDiag<ModelClass>(model);
   }, "model"_a);
   

}




#endif /* COMPNAL_PYBIND11_SOLVER_EXACT_DIAG_HPP_ */
