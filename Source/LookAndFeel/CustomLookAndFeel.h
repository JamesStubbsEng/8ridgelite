/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 28 Oct 2020 9:26:07pm
    Author:  James

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <string> 

//==============================================================================
/**
*/

class CustomLookAndFeel : public LookAndFeel_V4
{
    Typeface::Ptr montserratTf = Typeface::createSystemTypefaceFor(BinaryData::_124_MontserratBlack_ttf, BinaryData::_124_MontserratBlack_ttfSize);
    float fontSize = 25.0f;

    Font getTextButtonFont(TextButton&, int buttonHeight) override
    {
        Font f(montserratTf);
        f.setHeight(fontSize);
        return f;
    }

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool isMouseOverButton, bool isButtonDown) override
    {
        auto baseColour = backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
            .withMultipliedAlpha(button.isEnabled() ? 0.9f : 0.5f);

        if (isButtonDown || isMouseOverButton)
            baseColour = baseColour.contrasting(isButtonDown ? 0.2f : 0.1f);

        auto flatOnLeft = button.isConnectedOnLeft();
        auto flatOnRight = button.isConnectedOnRight();
        auto flatOnTop = button.isConnectedOnTop();
        auto flatOnBottom = button.isConnectedOnBottom();

        auto width = button.getWidth() - 1.0f;
        auto height = button.getHeight() - 1.0f;

        if (width > 0 && height > 0)
        {
            auto cornerSize = jmin(15.0f, jmin(width, height) * 0.45f);
            auto lineThickness = cornerSize * 0.1f;
            auto halfThickness = lineThickness * 0.5f;

            Path outline;
            outline.addRoundedRectangle(0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
                cornerSize, cornerSize,
                !(flatOnLeft || flatOnTop),
                !(flatOnRight || flatOnTop),
                !(flatOnLeft || flatOnBottom),
                !(flatOnRight || flatOnBottom));

            auto outlineColour = button.findColour(button.getToggleState() ? TextButton::textColourOnId
                : TextButton::textColourOnId);

            g.setColour(baseColour);
            g.fillPath(outline);

            if (!button.getToggleState())
            {
                g.setColour(outlineColour);
                g.strokePath(outline, PathStrokeType(lineThickness));
            }
        }
    }

};
