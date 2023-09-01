#pragma once
#include<iostream>
#include<cctype>
#include<vector>
#include<cmath>
#include<map>
#include<set>
#include<algorithm>
#include<string>
enum class TypeLetters {
    MissingTypeOfLetter,
    NoMissingTypeOfLetters
};
std::string readGenotypes(std::string& gen);

std::set<char>getGenotype(const std::string& firstGen, const std::string& secondGen);

TypeLetters findLettersCase(const std::string gen);

std::string easyFix(const std::string& gen);

std::string hardFix(const std::string& gen);

std::string fixGenotype(const std::string& gen);

void findGametes(const std::string gen, size_t indLength, size_t& indexArr, std::vector<std::string>& combinations, std::string currComb);

std::string calculateAlignment(const std::string& gen, size_t wordLenght);

std::vector<std::vector<std::string>>readOffspring(const std::string& firstGen, const std::string& secondGen);

void printGenerations(const std::string& firstGen, const std::string& secondGen);