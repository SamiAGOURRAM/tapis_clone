#
# Copyright (c) 2022 Wael-Amine Boutglay
#

cmake_minimum_required(VERSION 3.7)

project(smtface)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
string(APPEND CMAKE_CXX_FLAGS_RELEASE " -O3")
string(APPEND CMAKE_CC_FLAGS_RELEASE " -O3")

set(SMTFACE_Z3 ON)
if(SMTFACE_Z3)
    string(APPEND CMAKE_CXX_FLAGS " -DSMTFACE_Z3")
endif()

# "include" directories
include_directories(include)

set(SMTFACE_FILES src/core/context.cc
        src/core/evaluator.cc
        src/core/interpolator.cc
        src/core/printer.cc
        src/core/register.cc
        src/core/solver.cc
        src/core/sort.cc
        src/core/symbol.cc
        src/core/substituter.cc
        src/core/term.cc

        src/theories/core.cc
        src/theories/ints.cc
        src/theories/arrays.cc

        src/utils/array_to_epr.cc
        src/utils/count_quantifier_depth.cc
        src/utils/not_eliminator.cc
        src/utils/has_ite.cc
        src/utils/dnfizer.cc
        src/utils/ite_eliminator.cc

        src/shorthands.cc)

    set(SMTFACE_FILES ${SMTFACE_FILES}
            src/solvers/z3/converter.cc
            src/solvers/z3/interpolator.cc
            src/solvers/z3/model.cc
            src/solvers/z3/solver.cc)

# the smtface library
add_library(smtface STATIC ${SMTFACE_FILES})
