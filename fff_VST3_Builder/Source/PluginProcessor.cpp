#include "PluginProcessor.h"
#include "PluginEditor.h"

FffAudioProcessor::FffAudioProcessor()
    : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)) {
    const char* defaults[8] = { "KICK", "SNARE", "HIHAT CL", "HIHAT OP", "TOM", "PERC", "CLAP", "CYMBAL" };
    for (int i = 0; i < 8; ++i) {
        tracks[i].name = defaults[i];
        tracks[i].steps = 16;
        tracks[i].notes.clear(); // Always empty on initial startup
    }
}

void FffAudioProcessor::prepareToPlay (double sampleRate, int) {
    currentSampleRate = sampleRate;
}

void FffAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    if (auto* playHead = getPlayHead()) {
        if (auto pos = playHead->getPosition()) {
            if (auto bpm = pos->getBpm())
                hostBpm = *bpm;
        }
    }
    juce::ignoreUnused(midiMessages);
}

void FffAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
    juce::ValueTree state ("FFF_STATE");
    state.setProperty ("preset", currentPreset, nullptr);
    state.setProperty ("polyStretch", polyStretchMode, nullptr);
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void FffAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName ("FFF_STATE")) {
        auto state = juce::ValueTree::fromXml (*xmlState);
        currentPreset = state.getProperty ("preset", 0);
        polyStretchMode = state.getProperty ("polyStretch", false);
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new FffAudioProcessor();
}
