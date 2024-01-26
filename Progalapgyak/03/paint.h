/* Logo-szerű függvénykönyvtár C nyelvhez
 *
 * A függvénykönyvtár alapját Douglas Thain `A simple graphics library for
 * CSE 20211' munkája képezi (gfx.h és gfx.c fájlok)
 * http://www.nd.edu/~dthain/courses/cse20211/fall2013/gfx
 *
 * Gercsó Márk, gmark@inf.u-szeged.hu
 * Gergely Tamás, gertom@inf.u-szeged.hu
 */

#ifndef GRAPHICS_LOGO_H
#define GRAPHICS_LOGO_H

#include <stdbool.h>

/* Előre definiált színek listája */
typedef enum {
    WHITE        = 0xFFFFFF,
    RED          = 0xFF0000,
    LIGHT_RED    = 0xF08080,
    DARK_RED     = 0x8B0000,
    PINK         = 0xFF69B4,
    LIGHT_PINK   = 0xFFC0CB,
    ORANGE       = 0xFFA500,
    CORAL        = 0xFF7F50,
    YELLOW       = 0xFFFF00,
    GOLD         = 0xFFD700,
    LIGHT_YELLOW = 0xFFFFE0,
    PURPLE       = 0xBA55D3,
    LIGHT_PURPLE = 0xD8BFD8,
    DARK_PURPLE  = 0x800080,
    GREEN        = 0x00FF00,
    LIGHT_GREEN  = 0x00FA9A,
    DARK_GREEN   = 0x2E8B57,
    BLUE         = 0x0000FF,
    LIGHT_BLUE   = 0x87CEEB,
    DARK_BLUE    = 0x00008B,
    BROWN        = 0xA52A2A,
    LIGHT_BROWN  = 0xDEB887,
    DARK_BROWN   = 0x8B4513,
    LIGHT_GRAY   = 0xC0C0C0,
    GRAY         = 0x808080,
    BLACK        = 0x000000
} color_t;

/* Elkészít egy ablakot megadott méretben, az alapértelmezett beállításokkal
 * A kurzor a képernyő közepén helyezkedik el, a háttér fekete, az előtér
 * fehér, míg a kurzor zöld színű lesz.
 * width: az ablak szélessége
 * height: az ablak magassága
 */
void create_window(int width, int height);

/* Várakozik a 'q' billentyű lenyomására, majd bezárja az ablakot. */
void close_window();

/* Beállítja az előtér színét, amely színnel a rajzolás történik.
 * c: az előtér új színe a color_t listából
 */
void set_color(color_t c);

/* Beállítja az előtér színét, amely színnel a rajzolás történik.
 * r: a szín piros komponense (0..255)
 * g: a szín zöld komponense (0..255)
 * b: a szín kék komponense (0..255)
 */
void set_color_rgb(int r, int g, int b);

/* Beállítja a háttér színét.
 * c: a háttér új színe a color_t listából
 */
void set_background(color_t c);

/* Beállítja a háttér színét.
 * r: a szín piros komponense (0..255)
 * g: a szín zöld komponense (0..255)
 * b: a szín kék komponense (0..255)
 */
void set_background_rgb(int r, int g, int b);

/* Beállítja a kurzort jelző nyíl színét.
 * c: a háttér új színe a color_t listából
 */
void set_arrow_color(color_t c);

/* Beállítja a kurzort jelző nyíl színét.
 * r: a szín piros komponense (0..255)
 * g: a szín zöld komponense (0..255)
 * b: a szín kék komponense (0..255)
 */
void set_arrow_color_rgb(int r, int g, int b);

/* Visszaad egy véletlenszerű színt a color_t listából. */
color_t get_random_color();

/* Visszaad egy teljesen véletlenszerű RGB színt. */
color_t get_random_color_rgb();

/* Engedélyezi a kurzort jelző nyíl megjelenítését. */
void show_cursor();

/* Letiltja a kurzort jelző nyíl megjelenítését. */
void hide_cursor();

/* Kitölti az előtér színével azt az egybefüggő, azonos színű területet,
 * ahol a kurzor jelenleg áll. Ha a kurzor egy olyan pixelen áll, amely
 * színe megegyezik az előtér színével, akkor nem történik semmi.
 */
void fill();

/* Felemeli a tollat. Amíg fel van emelve a toll, addig nem történik
 * rajzolás a kurzor mozgatása közben.
 */
void pen_up();

/* Leteszi a tollat. Ha le van téve a toll, akkor a kurzor mozgatása közben
 * a bejárt útvonalat végigrajzoljuk az előtér színével.
 */
void pen_down();

/* A kurzort distance egységnyi pixellel előre mozgatja.
 * distance: a mozgatás mértéke pixelben
 */
void forward(float distance);

/* A kurzort distance egységnyi pixellel hátrafel mozgatja.
 * distance: a mozgatás mértéke pixelben
 */
void back(float distance);

/* A kurzort elforgatja balra angle fokkal.
 * angle: a forgatás mértéke fokban
 */
void left(float angle);

/* A kurzort elforgatja jobbra angle fokkal.
 * angle: a forgatás mértéke fokban
 */
void right(float angle);

/* Beállítja az animáció (mozgás, fordulás, kitöltés) sebességét.
 * value: 0 (leglassabb) és 10 (leggyorsabb) közötti szám
 */
void set_speed(int value);

/* Beállítja a mozgás animáció sebességét.
 * value: 0 (leglassabb) és 10 (leggyorsabb) közötti szám
 */
void set_move_speed(int value);

/* Beállítja a forgás animáció sebességét.
 * value: 0 (leglassabb) és 10 (leggyorsabb) közötti szám
 */
void set_turn_speed(int value);

/* Beállítja a kurzor irányát target_angle fokra.
 * target_angle: a kívánt szög fokban (0: jobbra, 90: le, 180: balra, 270: fel)
 */
void turn_to(float target_angle);

/* A kurzor irányát beállítja felfelé (270). */
void turn_up();

/* A kurzor irányát beállítja lefelé (90). */
void turn_down();

/* A kurzor irányát beállítja balra (180). */
void turn_left();

/* A kurzor irányát beállítja jobbra (0). */
void turn_right();

/* A kurzort a megadott (x, y) pozícióba mozgatja. Mozgás közben rajzol, ha
 * lent van a toll.
 * x: vízszintes pozíció
 * y: függőleges pozíció
 */
void goto_position(float x, float y);

/* A kurzort a megadott (x, y) pozícióra helyezi. Nincs rajzolás.
 * x: vízszintes pozíció
 * y: függőleges pozíció
 */
void jump_to_position(float x, float y);

/* A kurzor aktuális helyzete (x, y pozíció, irány) lesz a `home' helyzet.
 * Kezdetben ez a képernyő közepe, és a kurzor felfelé néz.
 */
void set_home();

/* A kurzort a mentett `home' helyzetbe mozgatja. Ha kell, rajzol közben. */
void goto_home();

/* A kurzort a mentett `home' helyzetbe helyezi. Nincs rajzolás. */
void jump_home();

/* Visszaadja a kurzor aktuális helyzetének vízszintes koordinátáját. */
float get_x_position();

/* Visszaadja a kurzor aktuális helyzetének függőleges koordinátáját. */
float get_y_position();

/* Visszaadja a kurzor aktuális helyzetének irányát (fokban). */
float get_angle();

/* Visszaadja az előtér (rajzolás) színét. */
color_t get_foreground_color();

/* Visszaadja a háttér színét. */
color_t get_background_color();

/* Visszaadja a kurzor színét. */
color_t get_cursor_color();

/* Visszaadja, hogy a toll le van-e rakva? */
int is_pen_down();

/* Visszaadja, hogy a kurzor meg van-e jelenítve? */
int is_cursor_active();

/* Az ablak tartalmát ppm formátumban elmenti a filename nevű fájlba.
 * filename: a létrehozandó fájl neve.
 */
void save_image(const char* filename);

/* Ellenőrzi, hogy a következő esemény a bal egérkattintás-e? */
bool new_event_is_left_click();

/* Ellenőrzi, hogy a következő esemény a key billentyű leütése-e?
 * key: a várt billentyű
 */
bool new_event_is_button(char key);

/* Visszaadja az utolsó esemény x koordinátáját. */
int last_event_x();

/* Visszaadja az utolsó esemény y koordinátáját. */
int last_event_y();

/* Egy boldog felhő kirajzolása az aktuális pozíció köré megadott méretben.
 * size: a felhő mérete (min: 8)
 */
void draw_cloud(float size);

#endif
