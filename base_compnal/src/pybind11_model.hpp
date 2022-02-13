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
//  Created by Kohei Suzuki on 2021/11/09.
//

#ifndef COMPNAL_PYBIND11_MODEL_HPP_
#define COMPNAL_PYBIND11_MODEL_HPP_

#include "../../compnal-cpp/src/model/base_u1_spin.hpp"
#include "../../compnal-cpp/src/model/general_model.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

namespace compnal {
namespace wrapper {

namespace py = pybind11;

//The following does not bring in anything else from the pybind11 namespace except for literals.
using namespace pybind11::literals;

template<typename RealType>
void pybind11ModelBaseU1Spin(py::module &m) {
   
   using CppC  = compnal::model::BaseU1Spin<RealType>;
   using QType = typename compnal::model::BaseU1Spin<RealType>::QType;
   auto  py_c = py::class_<CppC>(m, "BaseU1Spin", py::module_local());
   
   //Constructors
   py_c.def(py::init<>());
   py_c.def(py::init<const type::HalfInt>(), "spin"_a);
   py_c.def(py::init<const double>(), "spin"_a);
   py_c.def(py::init<const type::HalfInt, const type::HalfInt>(), "spin"_a, "total_sz"_a);
   py_c.def(py::init<const type::HalfInt, const double>(), "spin"_a, "total_sz"_a);
   py_c.def(py::init<const double, const type::HalfInt>(), "spin"_a, "total_sz"_a);
   py_c.def(py::init<const double, const double>(), "spin"_a, "total_sz"_a);

   //Public Member Functions
   py_c.def("set_magnitude_spin"     , &CppC::SetMagnitudeSpin, "spin"_a);
   py_c.def("set_total_sz"           , &CppC::SetTotalSz      , "total_sz"_a);
   py_c.def("validate_q_number"      , py::overload_cast<const int, const QType>(&CppC::ValidateQNumber, py::const_), "system_size"_a, "total_sz"_a);
   py_c.def("calculate_target_dim"   , py::overload_cast<const int, const QType>(&CppC::CalculateTargetDim, py::const_), "system_size"_a, "total_sz"_a);
   py_c.def("get_dim_onsite"         , &CppC::GetDimOnsite    );
   py_c.def("get_total_sz"           , &CppC::GetTotalSz      );
   py_c.def("get_magnitude_spin"     , &CppC::GetMagnitudeSpin);
   
   //Read Only property
   py_c.def("get_onsite_operator_sx" , &CppC::GetOnsiteOperatorSx );
   py_c.def("get_onsite_operator_isy", &CppC::GetOnsiteOperatoriSy);
   py_c.def("get_onsite_operator_sz" , &CppC::GetOnsiteOperatorSz );
   py_c.def("get_onsite_operator_sp" , &CppC::GetOnsiteOperatorSp );
   py_c.def("get_onsite_operator_sm" , &CppC::GetOnsiteOperatorSm );

   //Static Member Functions
   py_c.def_static("create_onsite_operator_sx" , &CppC::CreateOnsiteOperatorSx , "spin"_a);
   py_c.def_static("create_onsite_operator_isy", &CppC::CreateOnsiteOperatoriSy, "spin"_a);
   py_c.def_static("create_onsite_operator_sz" , &CppC::CreateOnsiteOperatorSz , "spin"_a);
   py_c.def_static("create_onsite_operator_sp" , &CppC::CreateOnsiteOperatorSp , "spin"_a);
   py_c.def_static("create_onsite_operator_sm" , &CppC::CreateOnsiteOperatorSm , "spin"_a);
   
   py_c.def("print_basis_onsite", [](CppC &self) {
      py::scoped_ostream_redirect stream(std::cout, py::module_::import("sys").attr("stdout"));
      self.PrintBasisOnsite();
   });

}

template<typename RealType>
void pybind11ModelGeneral(py::module &m) {
   
   using BU1S   = compnal::model::BaseU1Spin<RealType>;
   using GMBU1S = compnal::model::GeneralModel<BU1S>;
   using IntegerType = typename GMBU1S::IntegerType;
   using StringType  = typename GMBU1S::StringType;
   using IndexType   = typename GMBU1S::IndexType;
   using VariantVecType = std::vector<typename GMBU1S::VariantType>;
   
   auto convert_to_py = [](const auto &v) {
      if (std::holds_alternative<IntegerType>(v)) {
         return py::int_(std::get<IntegerType>(v));
      }
      else if (std::holds_alternative<StringType>(v)) {
         return py::str(std::get<StringType>(v));
      }
      else if (std::holds_alternative<VariantVecType>(v)) {
         const auto &variant_vec = std::get<VariantVecType>(v);
         py::tuple tuple;
         for (const auto &it: variant_vec) {
            if (std::holds_alternative<IntegerType>(it)) {
               tuple = tuple + py::make_tuple(std::get<IntegerType>(it));
            }
            else if (std::holds_alternative<StringType>(it)) {
               tuple = tuple + py::make_tuple(std::get<StringType>(it));
            }
            else {
               throw std::runtime_error("Invalid template parameters");
            }
         }
         return tuple;
      }
      else {
         throw std::runtime_error("Invalid template parameters");
      }
   };
   
   py::class_<GMBU1S, BU1S> gm_u1_spin(m, "U1Spin", py::module_local());
   gm_u1_spin.def(py::init<>());
   gm_u1_spin.def(py::init<const type::HalfInt>(), "spin"_a);
   gm_u1_spin.def(py::init<const double>(), "spin"_a);
   gm_u1_spin.def(py::init<const type::HalfInt, const type::HalfInt>(), "spin"_a, "total_sz"_a);
   gm_u1_spin.def(py::init<const type::HalfInt, const double>(), "spin"_a, "total_sz"_a);
   gm_u1_spin.def(py::init<const double, const type::HalfInt>(), "spin"_a, "total_sz"_a);
   gm_u1_spin.def(py::init<const double, const double>(), "spin"_a, "total_sz"_a);

   gm_u1_spin.def("add_potential"  , &GMBU1S::AddPotential, "site"_a, "m"_a, "value"_a = 1.0);
   gm_u1_spin.def("add_interaction", &GMBU1S::AddInteraction, "site_1"_a, "m_1"_a, "site_2"_a, "m_2"_a, "value"_a = 1.0);
   gm_u1_spin.def("get_system_size", &GMBU1S::GetSystemSize);
   gm_u1_spin.def("get_interaction_list", &GMBU1S::GetInteractionList);
   gm_u1_spin.def("get_potential"       , &GMBU1S::GetPotential, "site"_a);
   gm_u1_spin.def("get_interaction"     , &GMBU1S::GetInteraction, "site_1"_a, "site_2"_a);
   gm_u1_spin.def("get_index_list" , [](GMBU1S &self) {
      const auto set = self.GetIndexList();
      std::vector<IndexType> vec(set.begin(), set.end());
      std::sort(vec.begin(), vec.end());
      py::list list;
      for (const auto &it: vec) {
         if (std::holds_alternative<IntegerType>(it)) {
            list.append(py::int_(std::get<IntegerType>(it)));
         }
         else if (std::holds_alternative<StringType>(it)) {
            list.append(py::str(std::get<StringType>(it)));
         }
         else if (std::holds_alternative<VariantVecType>(it)) {
            const auto &variant_vec = std::get<VariantVecType>(it);
            py::tuple tuple;
            for (const auto &it2: variant_vec) {
               if (std::holds_alternative<IntegerType>(it2)) {
                  tuple = tuple + py::make_tuple(std::get<IntegerType>(it2));
               }
               else if (std::holds_alternative<StringType>(it2)) {
                  tuple = tuple + py::make_tuple(std::get<StringType>(it2));
               }
               else {
                  throw std::runtime_error("Invalid template parameters");
               }
            }
            list.append(tuple);
         }
         else {
            throw std::runtime_error("Invalid template parameters");
         }
      }
      return list;
   });
   
   gm_u1_spin.def("get_potential_list"  , [](GMBU1S &self) {
      py::dict py_potential;
      for (const auto &it: self.GetPotentialList()) {
         if (std::holds_alternative<IntegerType>(it.first)) {
            py_potential[py::int_(std::get<IntegerType>(it.first))] = it.second;
         }
         else if (std::holds_alternative<StringType>(it.first)) {
            py_potential[py::str(std::get<StringType>(it.first))] = it.second;
         }
         else if (std::holds_alternative<VariantVecType>(it.first)) {
            const auto &variant_vec = std::get<VariantVecType>(it.first);
            py::tuple tuple;
            for (const auto &it: variant_vec) {
               if (std::holds_alternative<IntegerType>(it)) {
                  tuple = tuple + py::make_tuple(std::get<IntegerType>(it));
               }
               else if (std::holds_alternative<StringType>(it)) {
                  tuple = tuple + py::make_tuple(std::get<StringType>(it));
               }
               else {
                  throw std::runtime_error("Invalid template parameters");
               }
            }
            py_potential[tuple] = it.second;
         }
         else {
            throw std::runtime_error("Invalid template parameters");
         }
      }
      return py_potential;
   });


   

}


} //namespace wrapper
} //namespace compnal

#endif /* COMPNAL_PYBIND11_MODEL_HPP_ */
