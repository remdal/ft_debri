#ifndef PHASEAUDIO_HPP
#define PHASEAUDIO_HPP

// For CFTypeRef
#include <CoreFoundation/CFBase.h>
#include <string>
#include <vector>

#include <Utils/NonCopyable.h>

class PhaseAudio : public NonCopyable
{
public:
    PhaseAudio( const std::string& assetSearchPath );
    ~PhaseAudio();
    
    std::string loadStereoSound( const std::string& assetSearchPath, const std::string& assetName );
    void playSoundEvent( const std::string& identifier );
private:
    
    // Track backing data to release:
    struct SoundDatum
    {
        CFTypeRef   asset;
        CFTypeRef   event;
        std::string assetIdentifier;
        std::string eventIdentifier;
    };
    
    std::vector<SoundDatum> soundData;
    CFTypeRef               _phaseEngine;
};

#endif // PHASEAUDIO_HPP