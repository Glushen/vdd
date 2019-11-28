#include <cassert>
#include <iostream>
#include "inversion.h"

vdd::InversionTypeDeclarator::InversionTypeDeclarator(vdd::Type type):
    type(std::move(type)) { }

void vdd::InversionTypeDeclarator::print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames, int indentSpaceCount) {
    type.print(output, templateTypenames);
}

vdd::InvertedDeclaration::InvertedDeclaration(std::unordered_set<std::string> templateTypenames, std::unique_ptr<Declarator> declarator, std::string name):
    templateTypenames(std::move(templateTypenames)),
    declarator(std::move(declarator)),
    name(std::move(name)) { }

void vdd::InvertedDeclaration::print(std::ostream& output, int indentSpaceCount) {
    for (int i = 0; i < indentSpaceCount; i++) {
        output << ' ';
    }

    if (!name.empty()) {
        output << '\'' << name << '\'' << " is a ";
    } else {
        output << "unnamed ";
    }

    if (dynamic_cast<InversionFunctionDeclarator*>(declarator.get())) {
        output << "function ";
    } else if (dynamic_cast<InversionTypeDeclarator*>(declarator.get())) {
        output << "variable of ";
    }

    declarator->print(output, templateTypenames, indentSpaceCount);
}

vdd::InvertedDeclaration vdd::invertDeclaration(vdd::Declaration declaration) {
    Declarator* oldDeclarator = declaration.declarator.release();
    Declarator* newDeclarator = new InversionTypeDeclarator(std::move(declaration.type));

    while (auto wrappingDeclarator = dynamic_cast<WrappingDeclarator*>(oldDeclarator)) {
        if (auto functionDeclarator = dynamic_cast<FunctionDeclarator*>(wrappingDeclarator)) {
            auto invertedArguments = std::vector<InvertedDeclaration>();
            for (auto& argument : functionDeclarator->arguments) {
                invertedArguments.push_back(invertDeclaration(std::move(argument)));
            }
            auto invertedFunctionDeclarator = new InversionFunctionDeclarator(std::move(functionDeclarator->declarator), std::move(invertedArguments));
            delete wrappingDeclarator;
            wrappingDeclarator = invertedFunctionDeclarator;
        }
        oldDeclarator = wrappingDeclarator->declarator.release();
        wrappingDeclarator->declarator.reset(newDeclarator);
        newDeclarator = wrappingDeclarator;
    }

    auto nameDeclarator = dynamic_cast<NameDeclarator*>(oldDeclarator);
    assert(nameDeclarator != nullptr);
    auto name = std::move(nameDeclarator->name);
    delete nameDeclarator;

    return InvertedDeclaration(
        std::move(declaration.templateTypenames),
        std::unique_ptr<Declarator>(newDeclarator),
        std::move(name)
    );
}

vdd::InversionFunctionDeclarator::InversionFunctionDeclarator(std::unique_ptr<Declarator> declarator, std::vector<InvertedDeclaration> arguments):
    WrappingDeclarator(std::move(declarator)),
    arguments(std::move(arguments)) { }

void vdd::InversionFunctionDeclarator::print(std::ostream& output, const std::unordered_set<std::string>& templateTypenames, int indentSpaceCount) {
    if (arguments.empty()) {
        output << "without arguments";
    } else if (arguments.size() == 1) {
        output << "with the following argument:";
    } else {
        output << "with the following arguments:";
    }

    for (auto& argument : arguments) {
        output << '\n';

        argument.templateTypenames = templateTypenames;
        argument.print(output, indentSpaceCount + 4);
    }
}
