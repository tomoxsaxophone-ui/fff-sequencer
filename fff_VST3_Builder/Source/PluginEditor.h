#pragma once
#include "PluginProcessor.h"
#include <juce_gui_extra/juce_gui_extra.h>

class FffAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    explicit FffAudioProcessorEditor (FffAudioProcessor&);
    ~FffAudioProcessorEditor() override = default;
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    FffAudioProcessor& processorRef;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FffAudioProcessorEditor)
};
