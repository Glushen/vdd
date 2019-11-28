#include "declaration.h"

#include <iostream>
#include <utility>
#include <bits/unordered_set.h>
#include <unordered_set>
#include <cassert>

vdd::Declaration::Declaration(std::unordered_set<std::string> templateTypenames, Type type, std::unique_ptr<Declarator> declarator):
    templateTypenames(std::move(templateTypenames)),
    type(std::move(type)),
    declarator(std::move(declarator)) { }

vdd::NameDeclarator::NameDeclarator(std::string name):
    name(std::move(name)) { }

void vdd::NameDeclarator::print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames, int indentSpaceCount) {
    assert(false);
}

vdd::WrappingDeclarator::WrappingDeclarator(std::unique_ptr<Declarator> declarator):
    declarator(std::move(declarator)) { }

vdd::PointerDeclarator::PointerDeclarator(std::unique_ptr<Declarator> declarator):
    WrappingDeclarator(std::move(declarator)) { }

void vdd::PointerDeclarator::print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames, int indentSpaceCount) {
    output << "pointer to ";
    declarator->print(output, templateTypenames, indentSpaceCount);
}

vdd::MemberPointerDeclarator::MemberPointerDeclarator(vdd::Type type, std::unique_ptr<Declarator> declarator):
    WrappingDeclarator(std::move(declarator)),
    type(std::move(type)) { }

void vdd::MemberPointerDeclarator::print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames, int indentSpaceCount) {
    output << "pointer to member of ";
    type.print(output, templateTypenames);
    output << " ";
    declarator->print(output, templateTypenames, indentSpaceCount);
}

vdd::ArrayDeclarator::ArrayDeclarator(std::unique_ptr<Declarator> declarator, std::string count):
    WrappingDeclarator(std::move(declarator)),
    count(std::move(count)) { }

void vdd::ArrayDeclarator::print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames, int indentSpaceCount) {
    output << "array of ";
    if (count.empty()) {
        output << "unspecified size";
    } else {
        output << "size " << count;
    }
    output << " of ";
    declarator->print(output, templateTypenames, indentSpaceCount);
}

vdd::FunctionDeclarator::FunctionDeclarator(std::unique_ptr<Declarator> declarator, std::vector<Declaration> arguments):
    WrappingDeclarator(std::move(declarator)),
    arguments(std::move(arguments)) { }

void vdd::FunctionDeclarator::print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames, int indentSpaceCount) {
    assert(false);
}
