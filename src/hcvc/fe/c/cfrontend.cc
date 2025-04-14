//
// Copyright (c) 2022 Wael-Amine Boutglay
//

#include "hcvc/fe/c/cfrontend.hh"

#include <iostream>
#include "clang/Analysis/AnalysisDeclContext.h"
#include "clang/Tooling/Tooling.h"

#include "compiler.cc"

namespace hcvc::fe {

  //*-- CFrontend
  CFrontend::CFrontend() = default;

  CFrontend::~CFrontend() = default;

  hcvc::Module *CFrontend::process(const hcvc::Source &source) {
    std::string bool_definition = "typedef enum {"
                                  "  true = 1,"
                                  "  false = 0"
                                  "} bool;\n\n"
                                  "void _requires(const char *);\n\n"
                                  "void _ensures(const char *);\n\n";
    std::unique_ptr<clang::ASTUnit> ast(
        clang::tooling::buildASTFromCodeWithArgs(bool_definition + source.content(),
                                                 {
                                                     "-Wno-implicit-function-declaration",
                                                     "-Wno-main", // allow other parameters to be passed to main other than argc or argv
                                                     "-Wno-main-return-type", // allow main to not return an int value
                                                     "-Wno-comment" // ignore warning about comment
                                                 }, source.path()));
    clang::ASTContext *ast_context = &(ast->getASTContext());
    clang::TranslationUnitDecl *translation_unit = ast_context->getTranslationUnitDecl();

    fe::c::Compiler compiler(ast_context, translation_unit, _context);
    return compiler.compile();
  }

}
