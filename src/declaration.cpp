#include "declaration.h"

#include <utility>

vdd::Declaration::Declaration(std::unordered_set<std::string> templateTypenames, Type type, std::unique_ptr<Declarator> declarator):
    templateTypenames(std::move(templateTypenames)),
    type(std::move(type)),
    declarator(std::move(declarator)) { }

vdd::NameDeclarator::NameDeclarator(std::string name):
    name(std::move(name)) { }

vdd::WrappingDeclarator::WrappingDeclarator(std::unique_ptr<Declarator> declarator):
    declarator(std::move(declarator)) { }

vdd::PointerDeclarator::PointerDeclarator(std::unique_ptr<Declarator> declarator):
    WrappingDeclarator(std::move(declarator)) { }

vdd::MemberPointerDeclarator::MemberPointerDeclarator(vdd::Type type, std::unique_ptr<Declarator> declarator):
    WrappingDeclarator(std::move(declarator)),
    type(std::move(type)) { }

vdd::ArrayDeclarator::ArrayDeclarator(std::unique_ptr<Declarator> declarator, std::string count):
    WrappingDeclarator(std::move(declarator)),
    count(std::move(count)) { }

vdd::FunctionDeclarator::FunctionDeclarator(std::unique_ptr<Declarator> declarator, std::vector<Declaration> arguments):
    WrappingDeclarator(std::move(declarator)),
    arguments(std::move(arguments)) { }
