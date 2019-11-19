#pragma once

#include "declaration.h"

namespace vdd {
    class InversionTypeDeclarator: public Declarator {
    public:
        Type type;
        explicit InversionTypeDeclarator(Type type);
    };

    class InvertedDeclaration {
    public:
        std::unordered_set<std::string> templateTypenames;
        std::unique_ptr<Declarator> declarator;
        std::string name;
        InvertedDeclaration(std::unordered_set<std::string> templateTypenames, std::unique_ptr<Declarator> declarator, std::string name);
    };

    class InversionFunctionDeclarator: public WrappingDeclarator {
    public:
        std::vector<InvertedDeclaration> arguments;
        InversionFunctionDeclarator(std::unique_ptr<Declarator> declarator, std::vector<InvertedDeclaration> arguments);
    };

    InvertedDeclaration invertDeclaration(Declaration declaration);
};
