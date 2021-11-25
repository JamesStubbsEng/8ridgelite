/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 28 Oct 2020 9:26:07pm
    Author:  James

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
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

    void drawRoundThumb(Graphics& g, float x, float y, float diameter, Colour colour, float outlineThickness)
    {
        auto halfThickness = outlineThickness * 0.5f;

        Path p;
        p.addEllipse(x + halfThickness,
            y + halfThickness,
            diameter - outlineThickness,
            diameter - outlineThickness);

        DropShadow(Colours::black, 1, {}).drawForPath(g, p);

        g.setColour(colour);
        g.fillPath(p);

        g.setColour(colour.brighter());
        g.strokePath(p, PathStrokeType(outlineThickness));
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

    void drawTickBox(Graphics& g, Component& component,
        float x, float y, float w, float h,
        bool ticked,
        bool isEnabled,
        bool isMouseOverButton,
        bool isButtonDown) override
    {
        auto boxSize = w * 0.7f;

        auto isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());

        auto colour = component.findColour(TextButton::buttonColourId)
            .withMultipliedSaturation((component.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
            .withMultipliedAlpha(component.isEnabled() ? 1.0f : 0.7f);

        drawRoundThumb(g, x, y + (h - boxSize) * 0.5f, boxSize, colour,
            isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);

        if (ticked)
        {
            g.setColour(isEnabled ? findColour(TextButton::buttonOnColourId) : Colours::grey);

            auto scale = 9.0f;
            auto trans = AffineTransform::scale(w / scale, h / scale).translated(x - 2.5f, y + 1.0f);

            g.fillPath(LookAndFeel_V4::getTickShape(6.0f), trans);
        }
    }

    void drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override
    {
        auto sliderRadius = (float)(getSliderThumbRadius(slider) - 2);

        auto isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());

        auto knobColour = slider.findColour(Slider::thumbColourId)
            .withMultipliedSaturation((slider.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
            .withMultipliedAlpha(slider.isEnabled() ? 1.0f : 0.7f);

        if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
        {
            float kx, ky;

            if (style == Slider::LinearVertical)
            {
                kx = x + width * 0.5f;
                ky = sliderPos;
            }
            else
            {
                kx = sliderPos;
                ky = y + height * 0.5f;
            }

            auto outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

            drawRoundThumb(g,
                kx - sliderRadius,
                ky - sliderRadius,
                sliderRadius * 2.0f,
                knobColour, outlineThickness);
        }
        else
        {
            // Just call the base class for the demo
            LookAndFeel_V2::drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override
    {
        g.fillAll(slider.findColour(Slider::backgroundColourId));

        //grey slider background
        //g.fillAll(Colour(0x50263238));

        //slightly transparent white
        //g.fillAll(Colour(0x20ffffff));

        if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
        {
            Path p;

            if (style == Slider::LinearBarVertical)
                p.addRectangle((float)x, sliderPos, (float)width, 1.0f + height - sliderPos);
            else
                p.addRectangle((float)x, (float)y, sliderPos - x, (float)height);

            auto baseColour = slider.findColour(Slider::rotarySliderFillColourId)
                .withMultipliedSaturation(slider.isEnabled() ? 1.0f : 0.5f)
                .withMultipliedAlpha(0.8f);

            g.setColour(baseColour);
            g.fillPath(p);

            auto lineThickness = jmin(15.0f, jmin(width, height) * 0.45f) * 0.1f;
            g.drawRect(slider.getLocalBounds().toFloat(), lineThickness);
        }
        else
        {
            drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height,
        float /*sliderPos*/,
        float /*minSliderPos*/,
        float /*maxSliderPos*/,
        const Slider::SliderStyle /*style*/, Slider& slider) override
    {
        auto sliderRadius = getSliderThumbRadius(slider) - 5.0f;
        Path on, off;

        if (slider.isHorizontal())
        {
            auto iy = y + height * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r(x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
            auto onW = r.getWidth() * ((float)slider.valueToProportionOfLength(slider.getValue()));

            on.addRectangle(r.removeFromLeft(onW));
            off.addRectangle(r);
        }
        else
        {
            auto ix = x + width * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r(ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
            auto onH = r.getHeight() * ((float)slider.valueToProportionOfLength(slider.getValue()));

            on.addRectangle(r.removeFromBottom(onH));
            off.addRectangle(r);
        }

        g.setColour(slider.findColour(Slider::rotarySliderFillColourId));
        g.fillPath(on);

        g.setColour(slider.findColour(Slider::trackColourId));
        g.fillPath(off);
    }

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
    {
        auto radius = jmin(width / 2, height / 2) - 2.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

        if (slider.isEnabled())
            g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
        else
            g.setColour(Colour(0x80808080));

        {
            Path filledArc;
            filledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, 0.0);
            g.fillPath(filledArc);
        }

        {
            auto lineThickness = jmin(15.0f, jmin(width, height) * 0.45f) * 0.1f;
            Path outlineArc;
            outlineArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.0);
            g.strokePath(outlineArc, PathStrokeType(lineThickness));
        }
    }
};