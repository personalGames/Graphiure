/* 
 * File:   Button.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 19:41
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "Component.h"
#include "ResourceHolder.h"
#include "IDFonts.h"
#include "IDTextures.h"
#include "Utilities.h"
#include "ButtonState.h"

#include <vector>
#include <wchar.h>
#include <memory>
#include <functional>
#include "Context.h"

namespace GUI {

    /**
     * Representa un botón en la GUI
     */
    class Button : public Component {
    public:
        /**
         * Define un alias para guardar una función
         */
        typedef std::function<void() > Callback;

        /**
         * Constructor
         * @param context contexto de la aplicación
         */
        Button(Context context);
        /**
         * Destructor
         */
        virtual ~Button();
        /**
         * Establece la función que se ejecutará con el botón
         * @param callback función
         */
        void setCallback(Callback callback);
        /**
         * Setea el texto del botón
         * @param text texto
         */
        void setText(const  wchar_t* text);
        /**
         * Establece si tendrá dos estados o solo uno
         * @param flag true si tendrá dos estados
         */
        void setToggle(bool flag);

        
        virtual bool isSelectable() const;
        virtual void select();
        virtual void deselect();
        virtual void activate();
        virtual void deactivate();
        virtual void handleEvent(const sf::Event& event);

    private:
        /**
         * Función que ejecutará el botón
         */
        Callback callback;
        /**
         * Imagen del botón
         */
        sf::Sprite sprite;
        /**
         * Texto del botón
         */
        sf::Text text;
        /**
         * SI tiene dos estados o no
         */
        bool isToggle;
        /**
         * Sonido del botón
         */
        SoundPlayer& mSounds;

        /**
         * Cambia la textura del botón según su estado
         * @param buttonType
         */
        void changeTexture(ButtonState buttonType);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    };
}
#endif	/* BUTTON_H */

