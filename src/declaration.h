#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include "type.h"

namespace vdd {
    class Declarator {
    public:
        virtual ~Declarator() = default;
    };

    class Declaration {
    public:
        std::unordered_set<std::string> templateTypenames;
        Type type;
        std::unique_ptr<Declarator> declarator;
        Declaration(std::unordered_set<std::string> templateTypenames, Type type, std::unique_ptr<Declarator> declarator);
    };

    class NameDeclarator: public Declarator {
    public:
        std::string name;
        explicit NameDeclarator(std::string);
    };

    class WrappingDeclarator: public Declarator {
    public:
        std::unique_ptr<Declarator> declarator;
        explicit WrappingDeclarator(std::unique_ptr<Declarator> declarator);
    };

    class PointerDeclarator: public WrappingDeclarator {
    public:
        explicit PointerDeclarator(std::unique_ptr<Declarator> declarator);
    };

    class MemberPointerDeclarator: public WrappingDeclarator {
    public:
        vdd::Type type;
        MemberPointerDeclarator(vdd::Type type, std::unique_ptr<Declarator> declarator);
    };

    class ArrayDeclarator: public WrappingDeclarator {
    public:
        std::string count;
        explicit ArrayDeclarator(std::unique_ptr<Declarator> declarator, std::string count = "");
    };

    class FunctionDeclarator: public WrappingDeclarator {
    public:
        std::vector<Declaration> arguments;
        FunctionDeclarator(std::unique_ptr<Declarator> declarator, std::vector<Declaration> arguments);
    };
}
