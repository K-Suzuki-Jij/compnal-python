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
//  Created by Kohei Suzuki on 2021/06/29.
//

#include "./src/pybind11_model.hpp"
#include "./src/pybind11_sparse_matrix.hpp"
#include "./src/pybind11_type.hpp"

PYBIND11_MODULE(base_compnal, m) {
   namespace py = pybind11;
   
   using RealType = double;
   
   py::module_ m_model = m.def_submodule("model");
   compnal::wrapper::pybind11ModelBaseU1Spin<RealType>(m_model);
   compnal::wrapper::pybind11ModelGeneral<RealType>(m_model);

   py::module_ m_sp_mat = m.def_submodule("sparse_matrix");
   compnal::wrapper::pybind11SparseMatrixCRS<RealType>(m_sp_mat);
   compnal::wrapper::pybind11SparseMatrixBraketVector<RealType>(m_sp_mat);
   compnal::wrapper::pybind11SparseMatrixParameters(m_sp_mat);
   
   py::module_ m_type = m.def_submodule("type");
   compnal::wrapper::pybind11TypeHalfInt(m_type);

};
