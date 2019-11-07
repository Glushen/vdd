#pragma once

#include <memory>
#include <vector>
#include "type.h"

namespace vdd {
    class Declarator {
    public:
        virtual ~Declarator() = default;
    };

    class Declaration {
    public:
        Type type;
        std::unique_ptr<Declarator> declarator;
        std::vector<std::string> templateTypenames;
        Declaration(std::vector<std::string> templateTypenames, Type type, std::unique_ptr<Declarator> declarator);
    };

    class NameDeclarator: public Declarator {
    public:
        std::string name;
        explicit NameDeclarator(std::string);
    };

    class PointerDeclarator: public Declarator {
    public:
        std::unique_ptr<Declarator> declarator;
        explicit PointerDeclarator(std::unique_ptr<Declarator> declarator);
    };

    class MemberPointerDeclarator: public Declarator {
    public:
        vdd::Type type;
        std::unique_ptr<Declarator> declarator;
        MemberPointerDeclarator(vdd::Type type, std::unique_ptr<Declarator> declarator);
    };

    class ArrayDeclarator: public Declarator {
    public:
        std::unique_ptr<Declarator> declarator;
        std::string count;
        explicit ArrayDeclarator(std::unique_ptr<Declarator> declarator, std::string count = "");
    };

    class FunctionDeclarator: public Declarator {
    public:
        std::unique_ptr<Declarator> declarator;
        std::vector<Declaration> arguments;
        FunctionDeclarator(std::unique_ptr<Declarator> declarator, std::vector<Declaration> arguments);
    };
}
