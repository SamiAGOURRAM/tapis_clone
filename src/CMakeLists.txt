add_library(tapislib STATIC
        hcvc/fe/c/cfrontend.cc

        tapis/engines/bounds.cc
        tapis/engines/engine.cc
        tapis/engines/options.cc
        tapis/engines/outputs.cc
        tapis/engines/statistics.cc

        tapis/engines/hornice/hornice.cc
        tapis/engines/hornice/learner.cc
        tapis/engines/hornice/teacher.cc

        tapis/engines/attributes/attribute.cc
        tapis/engines/hornice/qdt/classifier.cc
        tapis/engines/hornice/qdt/diagram.cc
        tapis/engines/attributes/enumerator.cc
        tapis/engines/attributes/new_attr_synthesizer.cc
        tapis/engines/hornice/qdt/learner.cc
        tapis/engines/hornice/qdt/quantifier.cc
        tapis/engines/horn_ice_qdt.cc
        tapis/engines/hornice/qdt/general_qdt/classifier.cc

        tapis/engines/ai/ai.cc
        )

add_library(hcvc STATIC
        hcvc/context.cc
        hcvc/module.cc
        hcvc/verifier.cc
        hcvc/clause/clause.cc
        hcvc/clause/hypergraph.cc
        hcvc/clause/predicate.cc
        hcvc/clause/set.cc
        hcvc/fe/frontend.cc
        hcvc/logic/evaluator.cc
        hcvc/logic/not_eliminator.cc
        hcvc/logic/operator.cc
        hcvc/logic/printer.cc
        hcvc/logic/smtface.cc
        hcvc/logic/substituter.cc
        hcvc/logic/term.cc
        hcvc/program/function.cc
        hcvc/program/state.cc
        hcvc/program/type.cc
        hcvc/program/variable.cc
        hcvc/utils/source.cc
        hcvc/utils/to_smtlib.cc

        hcvc/fe/c/cfrontend.cc)
