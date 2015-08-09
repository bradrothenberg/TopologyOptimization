#pragma once


#include "../JuceLibraryCode/JuceHeader.h"

struct NTLookAndFeel:public LookAndFeel_V3{
   virtual void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown)override;
    
    //void drawButtonText (Graphics &g ,TextButton &button ,bool isMouseOverButton,bool isButtonDown) override;
    
    virtual void drawTickBox (Graphics& g, Component& component,
                      float x, float y, float w, float h,
                      bool ticked,
                      bool isEnabled,
                      bool isMouseOverButton,
                      bool isButtonDown) override;
    
    
    virtual void drawToggleButton (Graphics&, ToggleButton&, bool isMouseOverButton, bool isButtonDown) override;
    
    virtual Slider::SliderLayout getSliderLayout (Slider&) override;
    
    virtual void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                     float sliderPos,
                                     float minSliderPos,
                                     float maxSliderPos,
                                     const Slider::SliderStyle style, Slider& slider) override;
    
    virtual void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                                float sliderPos, float minSliderPos, float maxSliderPos,
                                const Slider::SliderStyle style, Slider& slider) override;
    
    virtual void drawComboBox (Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &comboBox)override;
    
//    void drawTextEditorOutline (Graphics&g, int width, int height, TextEditor&) override;
//    
      virtual void  drawLabel (Graphics &, Label &) override;
    
   // Label* createSliderTextBox (Slider& slider);

	  void drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& editor) override;
};

struct NTLookAndFeelToolBar :public NTLookAndFeel {
	virtual void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
		bool isMouseOverButton, bool isButtonDown)override;

};