#include "Functions.h"
std::string readGenotypes(std::string& gen) {
    std::string secondGen;
    do {
        std::cin >> gen;
    } while (gen.length() % 2 != 0);
    do {
        std::cin >> secondGen;
    } while (secondGen.size() != gen.size());
    return secondGen;
}

std::set<char>getGenotype(const std::string& firstGen, const std::string& secondGen) {
    std::set<char>alleles;
    std::string allAlleles;
    allAlleles.append(firstGen).append(secondGen);
    for (const auto allele : allAlleles) {
        alleles.insert(allele);
    }
    return alleles;
}

TypeLetters findLettersCase(const std::string gen) {
    bool isUpperCase = false, isLowerCase = false;
    size_t size = gen.size();
    for (size_t i = 0;i < size;i++) {
        if (islower(gen[i])) {
            isLowerCase = true;
            break;
        }
    }
    for (size_t i = 0;i < size;i++) {
        if (isupper(gen[i])) {
            isUpperCase = true;
            break;
        }
    }
    if (isUpperCase && isLowerCase)
        return TypeLetters::NoMissingTypeOfLetters;
    return TypeLetters::MissingTypeOfLetter;
}

std::string easyFix(const std::string& gen) {
    std::string fixedGen = gen;
    std::sort(fixedGen.begin(), fixedGen.end());
    return fixedGen;
}

std::string hardFix(const std::string& gen) {
    std::string fixedGen = gen;
    std::map<char, int>upperLetters;
    for (size_t i = 0;i < gen.length();i++) {
        if (isupper(gen[i])) {
            upperLetters[tolower(fixedGen[i])]++;
            fixedGen[i] = tolower(fixedGen[i]);
        }
    }
    std::sort(fixedGen.begin(), fixedGen.end());
    for (const auto el : upperLetters) {
        size_t index = fixedGen.find(el.first);
        fixedGen[index] = toupper(fixedGen[index]);
        if (el.second == 2) {
            fixedGen[index + 1] = toupper(fixedGen[index + 1]);
        }
    }
    return fixedGen;
}

std::string fixGenotype(const std::string& gen) {
    std::string orderedGen = gen;
    TypeLetters currCase = findLettersCase(gen);
    switch (currCase) {
    case TypeLetters::MissingTypeOfLetter:
        orderedGen = easyFix(orderedGen);
        break;
    case TypeLetters::NoMissingTypeOfLetters:
        orderedGen = hardFix(orderedGen);
        break;
    default:
        std::cerr << "Something went wrong!\n";
        break;
    }
    return orderedGen;
}

void findGametes(const std::string gen, size_t indLength, size_t& indexArr, std::vector<std::string>& combinations, std::string currComb) {
    if (indLength >= gen.length()) {
        combinations[indexArr] = currComb;
        indexArr++;
        return;
    }
    currComb.push_back(gen[indLength]);
    indLength += 2;
    findGametes(gen, indLength, indexArr, combinations, currComb);
    currComb.pop_back();
    currComb.push_back(gen[indLength - 1]);
    findGametes(gen, indLength, indexArr, combinations, currComb);
}

std::string calculateAlignment(const std::string& gen, size_t wordLenght) {
    std::string fixGametes;
    const std::string emptySpaces(wordLenght / 4, ' ');
    fixGametes.append(emptySpaces);
    if (gen.size() % 2 != 0) {
        fixGametes.push_back(' ');
    }
    fixGametes.append(gen).append(emptySpaces);
    return fixGametes;

}

std::vector<std::vector<std::string>>readOffspring(const std::string& firstGen, const std::string& secondGen) {
    size_t size = static_cast<size_t>(pow(2, firstGen.size() / 2));
    std::vector<std::vector<std::string>>offspring(size + 1, std::vector<std::string>(size + 1));
    offspring[0][0] = "F";
    size_t index = 0;
    std::vector<std::string>gametes(size);
    findGametes(firstGen, 0, index, gametes, "");
    for (size_t i = 0;i < size;i++) {
        offspring[0][i + 1] = gametes[i];
    }
    index = 0;
    findGametes(secondGen, 0, index, gametes, "");
    for (size_t i = 0;i < size;i++) {
        offspring[i + 1][0] = gametes[i];
    }
    std::string combination;
    for (size_t i = 1;i < size + 1;i++) {
        for (size_t j = 1;j < size + 1;j++) {
            combination.append(offspring[i][0]).append(offspring[0][j]);
            offspring[i][j] = fixGenotype(combination);
            combination.clear();
        }
    }
    std::string genWithAlignment(offspring[0][1].size() - 1, ' ');
    genWithAlignment.append(offspring[0][0]);
    offspring[0][0] = genWithAlignment;
    size_t genLenght = offspring[1][1].size();
    for (size_t i = 1;i < size + 1;i++) {
        offspring[0][i] = calculateAlignment(offspring[0][i], genLenght);
    }
    return offspring;
}

void printGenerations(const std::string& firstGen, const std::string& secondGen) {
    std::vector<std::vector<std::string>>offspring = readOffspring(firstGen, secondGen);
    size_t size = offspring.size();

    for (const auto row : offspring) {
        for (const auto el : row) {
            std::cout << el << " ";
        }
        std::cout << "\n";
    }
}