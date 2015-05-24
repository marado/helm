/* Copyright 2013-2015 Matt Tytel
 *
 * twytch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * twytch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with twytch.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "formant_section.h"

#include "synth_slider.h"

#define SLIDER_WIDTH 10

FormantSection::FormantSection(String name) : SynthSection(name) {
  addButton(on_ = new ToggleButton("formant_on"));

  addSlider(x_ = new SynthSlider("formant_x"));
  x_->setSliderStyle(Slider::LinearBar);

  addSlider(y_ = new SynthSlider("formant_y"));
  y_->setSliderStyle(Slider::LinearBarVertical);

  addAndMakeVisible(xy_pad_ = new XYPad());
  xy_pad_->setXSlider(x_);
  xy_pad_->setYSlider(y_);
}

FormantSection::~FormantSection() {
  on_ = nullptr;
  x_ = nullptr;
  y_ = nullptr;
  xy_pad_ = nullptr;
}

void FormantSection::paint(Graphics& g) {
  static const DropShadow component_shadow(Colour(0x88000000), 2, Point<int>(0, 1));
  SynthSection::paint(g);
  component_shadow.drawForRectangle(g, xy_pad_->getBounds());
}

void FormantSection::resized() {
  on_->setBounds(2, 0, 20, 20);
  x_->setBounds(0, getHeight() - SLIDER_WIDTH, getWidth() - SLIDER_WIDTH, SLIDER_WIDTH);
  y_->setBounds(getWidth() - SLIDER_WIDTH, 20, SLIDER_WIDTH, getHeight() - 20 - SLIDER_WIDTH);
  xy_pad_->setBounds(0, 20, getWidth() - SLIDER_WIDTH, getHeight() - 20 - SLIDER_WIDTH);
}


void FormantSection::buttonClicked(Button* clicked_button) {
  SynthSection::buttonClicked(clicked_button);
  if (clicked_button == on_) {
    bool active = clicked_button->getToggleStateValue().getValue();
    for (auto slider : slider_lookup_)
      slider.second->setActive(active);
  }
}
