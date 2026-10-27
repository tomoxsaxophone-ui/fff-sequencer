#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <array>
#include <vector>

struct NoteEvent { int tick = 0; int velocity = 80; };

struct SampleLayer {
    float volume = 0.85f;
    float pan = 0.0f;
    int pitchSemitones = 0;
    float attackSec = 0.002f;
    float decaySec = 0.25f;
    bool solo = false;
    bool mute = false;
    juce::AudioBuffer<float> sampleBuffer;
    double sampleRate = 44100.0;
};

struct DrumTrack {
    juce::String name = "TRACK";
    int steps = 16;
    int playMode = 0; // 0:STACK, 1:VELOCITY, 2:ROUND
    bool monoMode = true;
    bool chokeGroup = false;
    int roundRobinIndex = 0;
    std::vector<NoteEvent> notes;
    std::array<SampleLayer, 3> layers;
};

class FffAudioProcessor : public juce::AudioProcessor {
public:
    FffAudioProcessor();
    ~FffAudioProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "#fff"; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return true; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 32; }
    int getCurrentProgram() override { return currentPreset; }
    void setCurrentProgram (int index) override { currentPreset = juce::jlimit(0, 31, index); }
    const juce::String getProgramName (int index) override { return "Preset #" + juce::String(index + 1); }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    std::array<DrumTrack, 8> tracks;
    int currentPreset = 0;
    bool polyStretchMode = false;
    double hostBpm = 120.0;

private:
    double currentSampleRate = 44100.0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FffAudioProcessor)
};
