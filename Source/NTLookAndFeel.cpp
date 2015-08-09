

#include "NTLookAndFeel.h"

void NTLookAndFeel::drawButtonBackground(juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour,
                                         bool isMouseOverButton, bool isButtonDown){
    
	if (isMouseOverButton && !isButtonDown) {

		g.fillAll(Colour{ uint8(240),uint8(240),uint8(240) });

	}
	else if (isMouseOverButton && isButtonDown) {

		g.fillAll(Colour{ uint8(225),uint8(225),uint8(225) });

	}
	else {
		g.fillAll(Colours::white);
	}
	g.setColour(Colours::lightgrey);
	g.drawRect(0, 0, button.getWidth(), button.getHeight(), 2);

    
}


void NTLookAndFeel::drawTickBox(juce::Graphics &g, juce::Component &button, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown){
    
    auto& toggle = dynamic_cast<ToggleButton&>(button);
    
    if (toggle.getRadioGroupId() > 0) {
        auto rect = Rectangle<float>(x,y,w,h);
        rect.reduce(w * .2, h*.2);
        
        g.setColour(Colours::white);
        g.fillEllipse(rect);
        g.setColour(Colours::lightgrey);
        g.drawEllipse(rect,2);
        
        if (ticked) {
            rect.reduce(rect.getWidth() * .2,rect.getHeight() *.2);

            g.fillEllipse(rect);
        }
    }else{
        auto rect = Rectangle<float>(x,y,w,h);
        g.setColour(Colours::white);
        g.fillRect(rect);
        g.setColour(Colours::lightgrey);
        g.drawRect(rect,3);
        if (ticked) {
            rect.reduce(rect.getWidth() * .25,rect.getHeight() *.25);
            g.fillRect(rect);
        }

    }
    
    
}
    
void NTLookAndFeel::drawToggleButton (Graphics& g, ToggleButton& button, bool isMouseOverButton, bool isButtonDown){
    
    float fontSize = jmin (15.0f, button.getHeight() * 0.75f);
    const int tickWidth = fontSize * 1.6f;
    
    drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                 tickWidth, tickWidth,
                 button.getToggleState(),
                 button.isEnabled(),
                 isMouseOverButton,
                 isButtonDown);
    
    g.setColour (button.findColour (ToggleButton::textColourId));
    g.setFont (fontSize);
    
    if (! button.isEnabled())
        g.setOpacity (0.5f);
    
    const int textX = (int) tickWidth + 10;
    
    g.drawFittedText (button.getButtonText(),
                      textX, 0,
                      button.getWidth() - textX - 2, button.getHeight(),
                      Justification::centredLeft, 10);
}


Slider::SliderLayout NTLookAndFeel::getSliderLayout(juce::Slider &slider){
    // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints
    
    int minXSpace = 0;
    int minYSpace = 0;
    
    Slider::TextEntryBoxPosition textBoxPos = slider.getTextBoxPosition();
    
    if (textBoxPos == Slider::TextBoxLeft || textBoxPos == Slider::TextBoxRight)
        minXSpace = 30;
    else
        minYSpace = 15;
    
    Rectangle<int> localBounds = slider.getLocalBounds();
    
    const int textBoxWidth = jmax (0, jmin (slider.getTextBoxWidth(),  localBounds.getWidth() - minXSpace));
    const int textBoxHeight = jmax (0, jmin (slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));
    
    Slider::SliderLayout layout;
    
    // 2. set the textBox bounds
    
    if (textBoxPos != Slider::NoTextBox)
    {
        if (slider.isBar())
        {
            layout.textBoxBounds = localBounds;
        }
        else
        {
            layout.textBoxBounds.setWidth (textBoxWidth);
            layout.textBoxBounds.setHeight (textBoxHeight);
            
            if (textBoxPos == Slider::TextBoxLeft)           layout.textBoxBounds.setX (0);
            else if (textBoxPos == Slider::TextBoxRight)     layout.textBoxBounds.setX (localBounds.getWidth() - textBoxWidth);
            else /* above or below -> centre horizontally */ layout.textBoxBounds.setX ((localBounds.getWidth() - textBoxWidth) / 2);
            
            if (textBoxPos == Slider::TextBoxAbove)          layout.textBoxBounds.setY (0);
            else if (textBoxPos == Slider::TextBoxBelow)     layout.textBoxBounds.setY (localBounds.getHeight() - textBoxHeight);
            else /* left or right -> centre vertically */    layout.textBoxBounds.setY ((localBounds.getHeight() - textBoxHeight) / 2);
        }
    }
    
    // 3. set the slider bounds
    
    layout.sliderBounds = localBounds;
    
    if (slider.isBar())
    {
        layout.sliderBounds.reduce (1, 1);   // bar border
    }
    else
    {
        if (textBoxPos == Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft (textBoxWidth + 10);
        else if (textBoxPos == Slider::TextBoxRight) layout.sliderBounds.removeFromRight (textBoxWidth);
        else if (textBoxPos == Slider::TextBoxAbove) layout.sliderBounds.removeFromTop (textBoxHeight);
        else if (textBoxPos == Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom (textBoxHeight);
        
        const int thumbIndent = getSliderThumbRadius (slider);
        
        if (slider.isHorizontal())    layout.sliderBounds.reduce (thumbIndent, 0);
        else if (slider.isVertical()) layout.sliderBounds.reduce (0, thumbIndent);
    }
    
    return layout;
    
}



//void NTLookAndFeel::drawLinearSlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos,
//                                     float maxSliderPos, const Slider::SliderStyle style, juce::Slider &slider){
//    
//    
//    
//}


void NTLookAndFeel::drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                 float sliderPos,
                                 float minSliderPos,
                                 float maxSliderPos,
                                 const Slider::SliderStyle style, Slider& slider){
    
    
    if (style == Slider::LinearHorizontal) {
        g.setColour(Colours::lightgrey);
        int startY = y + height/4;
        int endY = (y + height) - height/4;
        int midY = (startY+endY)/2;
        
        g.drawLine(x, startY, x, endY,3);
        g.drawLine(x+width, startY, x+width, endY,3);
        g.drawLine(x, midY, x+width, midY,3);
    }else{
        LookAndFeel_V3::drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
    
}


void NTLookAndFeel::drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                            float sliderPos, float minSliderPos, float maxSliderPos,
                                           const Slider::SliderStyle style, Slider& slider){
    const float sliderRadius = height/3.5f;

    if (style == Slider::LinearHorizontal) {
        g.setColour(Colours::grey);
        float kx = sliderPos;
        float ky = y + height * 0.5f;
        g.fillRect (Rectangle<float> (kx - 2.5f, ky - sliderRadius, 7.0f, sliderRadius * 2.0f));
    }else{
        LookAndFeel_V3::drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }

}

void NTLookAndFeel::drawComboBox(juce::Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox &box){
    g.fillAll (box.findColour (ComboBox::backgroundColourId));
    
    const Colour buttonColour (box.findColour (ComboBox::buttonColourId));
    g.setColour (Colours::lightgrey);
    g.drawRect (0, 0, width, height,2);

    
    Path p;

    
    
    int xEnd = (buttonX+buttonW) - buttonW/3;
    int midPointX = (buttonX + xEnd)/2.f;

    int yStart = buttonY + buttonH/3;
    int yEnd = (buttonY + buttonH ) - buttonH/3;
    p.addTriangle (buttonX, yStart,
                   xEnd ,yStart,
                   midPointX,yEnd);
    
    g.setColour (Colours::lightgrey);
    g.fillPath (p);
}


void NTLookAndFeel::drawLabel(juce::Graphics &g, juce::Label &label){
    g.fillAll (label.findColour (Label::backgroundColourId));
    
    if (! label.isBeingEdited())
    {
        const float alpha = label.isEnabled() ? 1.0f : 0.5f;
        const Font font (getLabelFont (label));
        
        g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);
        
        Rectangle<int> textArea (label.getBorderSize().subtractedFrom (label.getLocalBounds()));
        
        g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                          jmax (1, (int) (textArea.getHeight() / font.getHeight())),
                          label.getMinimumHorizontalScale());
        
        g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
    }
    else if (label.isEnabled())
    {
        g.setColour (label.findColour (Label::outlineColourId));
    }
    
    g.drawRect (label.getLocalBounds(),2);
}


void NTLookAndFeel::drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& editor)
{
	g.setColour(Colours::lightgrey);
	g.drawRect(0, 0, width, height, 2);

}

//----------------------------------------------------NTLookAndFeelToolBar---------------------------------------------------

void NTLookAndFeelToolBar::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
	bool isMouseOverButton, bool isButtonDown) {
	if (isMouseOverButton && !isButtonDown) {

		g.fillAll(Colour{ uint8(240),uint8(240),uint8(240) });

	}
	else if (isMouseOverButton && isButtonDown) {

		g.fillAll(Colour{ uint8(225),uint8(225),uint8(225) });

	}
	else {
		g.fillAll(Colours::white);
	}


}