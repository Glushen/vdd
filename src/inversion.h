#pragma once

#include "declaration.h"

namespace vdd {
    class InversionTypeDeclarator: public Declarator {
    public:
        Type type;
        explicit InversionTypeDeclarator(Type type);
        void print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames, int indentSpaceCount) override;
    };

    class InvertedDeclaration {
    public:
        std::unordered_set<std::string> templateTypenames;
        std::unique_ptr<Declarator> declarator;
        std::string name;
        InvertedDeclaration(std::unordered_set<std::string> templateTypenames, std::unique_ptr<Declarator> declarator, std::string name);
        void print(std::ostream& output, int indentSpaceCount);
    };

    class InversionFunctionDeclarator: public WrappingDeclarator {
    public:
        std::vector<InvertedDeclaration> arguments;
        InversionFunctionDeclarator(std::unique_ptr<Declarator> declarator, std::vector<InvertedDeclaration> arguments);
        void print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames, int indentSpaceCount) override;
    };

    InvertedDeclaration invertDeclaration(Declaration declaration);
}
