/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLGameCoordinator.hpp        +++     +++	**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 20/09/2025 16:50:46      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RMDLGAMECOORDINATOR_HPP
# define RMDLGAMECOORDINATOR_HPP

#include <Foundation/Foundation.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <Metal/Metal.hpp>
#include <MetalFX/MetalFX.hpp>

#include <string>
#include <unordered_map>

class GameCoordinator : public NonCopyable
{
public:
    GameCoordinator(MTL::Device* pDevice,
                    NS::UInteger width,
                    NS::UInteger height,
                    const std::string& assetSearchPath);
    ~GameCoordinator();

    void resizeDrawable(float width, float height);
    void draw( CA::MetalDrawable* pDrawable );
    void loadGameTextures(const std::string& textureSearchPath);
    void loadGameSounds(const std::string& assetSearchPath);

    enum class HighScoreSource {
        Local
    };

    int highScore() const;
private:
    std::unordered_map<std::string, NS::SharedPtr<MTL::Texture>>    _textureAssets;
    int                                                             frame;
    int                                                             _highScore;
};