#include "PluginProcessor.h"
#include "PluginEditor.h"

FffAudioProcessorEditor::FffAudioProcessorEditor (FffAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p) {
    setSize (1040, 680);
    setResizable (true, true);
}

void FffAudioProcessorEditor::paint (juce::Graphics& g) {
    g.fillAll (juce::Colour (0xfff4f6fa));
    g.setColour (juce::Colour (0xff2b303c));
    g.setFont (juce::FontOptions (22.0f, juce::Font::bold));
    g.drawText ("#fff — Drum Sequencer (VST3 / Standalone)", getLocalBounds().removeFromTop(48), juce::Justification::centred);
}

void FffAudioProcessorEditor::resized() {}

juce::AudioProcessorEditor* FffAudioProcessor::createEditor() {
    return new FffAudioProcessorEditor (*this);
}
