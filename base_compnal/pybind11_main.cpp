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
#include "./src/pybind11_solver_exact_diag.hpp"

PYBIND11_MODULE(base_compnal, m) {
   
   using RealType = double;
   
   py::module_ m_model = m.def_submodule("model");
   pybind11ModelBaseElectron1D<RealType>(m_model);
   pybind11ModelBaseSpin1D<RealType>(m_model);
   pybind11ModelBaseSpinElectron1D<RealType>(m_model);
   pybind11ModelBaseSpinMultiElectrons1D<RealType>(m_model);
   pybind11ModelXXZ1D<RealType>(m_model);
   pybind11ModelHubbard1D<RealType>(m_model);
   pybind11ModelKondoLattice1D<RealType>(m_model);
   pybind11ModelGeneral1D<RealType>(m_model);
   pybind11ModelBoundaryCondition(m_model);

   py::module_ m_sp_mat = m.def_submodule("sparse_matrix");
   pybind11SparseMatrixCRS<RealType>(m_sp_mat);
   pybind11SparseMatrixBraketVector<RealType>(m_sp_mat);
   pybind11SparseMatrixParameters(m_sp_mat);
   
   py::module_ m_solver = m.def_submodule("solver");
   pybind11SolverExactDiag<compnal::model::XXZ_1D<RealType>>(m_solver, "XXZ");
   pybind11SolverExactDiag<compnal::model::Hubbard_1D<RealType>>(m_solver, "Hubbard");
   pybind11SolverExactDiag<compnal::model::KondoLattice_1D<RealType>>(m_solver, "KondoLattice");
   pybind11SolverExactDiag<compnal::model::GeneralModel_1D<compnal::model::BaseU1Spin_1D<RealType>>>(m_solver, "U1Spin");
   pybind11SolverExactDiag<compnal::model::GeneralModel_1D<compnal::model::BaseU1Electron_1D<RealType>>>(m_solver, "U1Electron");
   pybind11SolverExactDiag<compnal::model::GeneralModel_1D<compnal::model::BaseU1SpinElectron_1D<RealType>>>(m_solver, "U1SpinElectron");
   pybind11SolverExactDiag<compnal::model::GeneralModel_1D<compnal::model::BaseU1SpinMultiElectrons_1D<RealType>>>(m_solver, "U1SpinMultiElectron");

};
