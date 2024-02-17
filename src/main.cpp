#ifdef ESP_PLATFORM

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#endif

#include "graphics.hpp"
#include "gui.hpp"
#include "path.hpp"
#include "filestream.hpp"
#include <iostream>

using namespace gui::elements;

// ESP-IDF main
extern "C" void app_main()
{
    graphics::init();

    auto canvas = graphics::Surface(graphics::getScreenWidth(), graphics::getScreenHeight());

    auto surface1 = graphics::Surface(320, 100);
    auto surface2 = graphics::Surface(320, 100);

    surface1.setTransparency(true);
    surface1.setTransparentColor(graphics::packRGB565(255, 255, 255));
    surface1.clear(graphics::packRGB565(0, 0, 0));

    std::string text = "Hello World !";
    surface1.setFontSize(64);
    surface1.setColor(graphics::packRGB565(255, 0, 0)); // This is due to a bug
    surface1.setTextColor(graphics::packRGB565(255, 255, 255));
    surface1.drawText(text, 0, 0);

    surface2.clear(graphics::packRGB565(0, 0, 0));
    for (uint16_t x = 0; x < 320; x++)
    {
        const uint8_t r = 255;
        const auto g = static_cast<uint8_t>((static_cast<float>(x) / 320) * 255);
        const uint8_t b = 0;

        surface2.drawLine(x, 0, x, 100, graphics::packRGB565(r, g, b));
    }
    surface2.pushSurface(&surface1, 0, 0);

    surface2.setTransparency(true);
    surface2.setTransparentColor(graphics::packRGB565(0, 0, 0));

    canvas.pushSurface(&surface2, 0, 0);


    // Window win;
    // Input* in = new Input(35, 35, 0, 0);
    // in->setTitle("Prénom:");
    // in->setPlaceHolder("écrire ici");
    //
    // win.addChild(in);

    /*Switch* sw1 = new Switch(10, 100);
    Switch* sw2 = new Switch(10, 150);
    sw2->setState(true);*/

    // VerticalList* list = new VerticalList(40, 200, 40, 300);
    // for (uint16_t i = 0; i < 3; i++)
    //     list->add(new Switch(0, 0));
    //
    // win.addChild(list);
    //
    // Button* button = new Button(35, 394, 250, 38);
    // Label* label = new Label(0, 0, 100, 18);
    // label->setText("Supprimer");
    // button->setLabel(label);
    // button->format();
    //
    // //win.addChild(label);
    //
    // win.addChild(button);

    while (graphics::isRunning())
    {
        // win.updateAll();
        //
        // if(in->isTouched())
        // {
        //     //in->setX(in->getX() + 20);
        //     in->setText("C'est Gabriel");
        // }

        /*if(sw1->isTouched())
        {
            if(sw1->getState())
                in->enable();
            else
                in->disable();
        }*/

        graphics::showSurface(&canvas);

#ifdef ESP_PLATFORM

        vTaskDelay(pdMS_TO_TICKS(10));

#else

        SDL_Delay(10);

#endif
    }
}

#ifndef ESP_PLATFORM

// Native main
int main(int argc, char **argv)
{
    graphics::SDLInit(app_main);
}

#endif
