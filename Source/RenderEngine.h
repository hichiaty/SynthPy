/*
  ==============================================================================

    RenderEngine.h
    Created: 27 Jun 2020 2:01:45am
    Author:  Hisham Abdel-Aty

  ==============================================================================
*/

#ifndef RENDERENGINE_H_INCLUDED
#define RENDERENGINE_H_INCLUDED

#include <random>
#include <array>
#include <iomanip>
#include <sstream>
#include <string>
#include "Maximilian/maximilian.h"
#include "Maximilian/libs/maxiFFT.h"
#include "Maximilian/libs/maxiMFCC.h"
#include "../JuceLibraryCode/JuceHeader.h"

using namespace juce;

typedef std::vector<std::pair<int, float>>  PluginPatch;
typedef std::vector<std::array<double, 13>> MFCCFeatures;

class RenderEngine
{
public:
    RenderEngine(int sr=44100,
        int bs=512,
        int ffts=512) :
        sampleRate(sr),
        bufferSize(bs),
        fftSize(ffts),
        plugin(nullptr)
    {
        maxiSettings::setup(sampleRate, 1, bufferSize);
    }

    virtual ~RenderEngine()
    {
        if (plugin)
        {
            plugin->releaseResources();
                plugin.release();
        }
    }

    RenderEngine(RenderEngine&) = default;

    bool loadPlugin(const std::string& path);

    void setPatch(const PluginPatch patch);

    const PluginPatch getPatch();

    void renderPatch(const uint8  midiNote,
        const uint8  midiVelocity,
        const double noteLength,
        const double renderLength);

    const MFCCFeatures getMFCCFrames();

    const MFCCFeatures getNormalisedMFCCFrames(const std::array<double, 13>& mean,
        const std::array<double, 13>& variance);

    const std::vector<double> getRMSFrames();

    const size_t getPluginParameterSize();

    const String getPluginParametersDescription();

    bool overridePluginParameter(const int   index,
        const float value);

    bool removeOverridenParameter(const int index);

    const std::vector<double> getAudioFrames();

    bool writeToWav(const std::string& path);

private:
    void fillAudioFeatures(const AudioSampleBuffer& data,
        maxiFFT& fft);

    void ifTimeSetNoteOff(const double& noteLength,
        const double& sampleRate,
        const int& bufferSize,
        const uint8& midiChannel,
        const uint8& midiPitch,
        const uint8& midiVelocity,
        const int& currentBufferIndex,
        MidiBuffer& bufferToNoteOff);

    void fillAvailablePluginParameters(PluginPatch& params);

    double               sampleRate;
    int                  bufferSize;
    int                  fftSize;
    maxiMFCC             mfcc;
    std::unique_ptr<juce::AudioPluginInstance, std::default_delete<juce::AudioPluginInstance>> plugin;
    PluginPatch          pluginParameters;
    PluginPatch          overridenParameters;
    MFCCFeatures         mfccFeatures;
    std::vector<double>  processedMonoAudioPreview;
    std::vector<double>  rmsFrames;
    double               currentRmsFrame = 0;
};


#endif  // RENDERENGINE_H_INCLUDED