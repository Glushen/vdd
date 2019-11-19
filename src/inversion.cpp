#include <cassert>
#include "inversion.h"

vdd::InversionTypeDeclarator::InversionTypeDeclarator(vdd::Type type):
    type(std::move(type)) { }

vdd::InvertedDeclaration::InvertedDeclaration(std::unordered_set<std::string> templateTypenames, std::unique_ptr<Declarator> declarator, std::string name):
    templateTypenames(std::move(templateTypenames)),
    declarator(std::move(declarator)),
    name(std::move(name)) { }

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
