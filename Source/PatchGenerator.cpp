/*
  ==============================================================================

    PatchGenerator.cpp
    Created: 27 Jun 2020 2:01:28am
    Author:  Hisham Abdel-Aty

  ==============================================================================
*/

#include "PatchGenerator.h"


//==============================================================================
std::pair<int, float> PatchGenerator::getRandomParameter(int index)
{
    std::uniform_real_distribution<float> distribution(0, 1);
    float randomValue = distribution(generator);
    return std::make_pair(index, randomValue);
}

//==============================================================================
PluginPatch PatchGenerator::getRandomPatch()
{
    PluginPatch randomPatch = skeletonPatch;
    std::uniform_real_distribution<float> distribution(0, 1);
    for (auto& parameter : randomPatch)
        parameter.second = distribution(generator);
    return randomPatch;
}