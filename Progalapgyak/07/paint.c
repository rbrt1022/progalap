/* Logo-szerű függvénykönyvtár C nyelvhez
 *
 * A függvénykönyvtár alapját Douglas Thain `A simple graphics library for
 * CSE 20211' munkája képezi (gfx.h és gfx.c fájlok)
 * http://www.nd.edu/~dthain/courses/cse20211/fall2013/gfx
 *
 * Gercsó Márk, gmark@inf.u-szeged.hu
 * Gergely Tamás, gertom@inf.u-szeged.hu
 */

#include "paint.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "gfx.h"

extern Display *gfx_display;
extern Window   gfx_window;

#define CURSOR_SIZE 10

typedef struct {
    float x;
    float y;
    float angle;
    bool is_pen_down;

    color_t background_color;
    color_t foreground_color;
    color_t cursor_color;
} state_t;

typedef struct {
    int width;
    int height;
    int* pixels;
    bool closed;
} window_data_t;

typedef struct {
    int moving_delay;
    int turning_delay;
} animation_speed_t;

typedef struct {
    bool cursor_drawing_active;
    int* cursor_positions;
    int cursor_position_length;
    int cursor_size;
    bool cursor_active;
} cursor_data_t;

/* Nem nyilvános változók és utility függvények. */

static window_data_t window;
static state_t current_state;
static cursor_data_t cursor;
static animation_speed_t speed;
static bool filling_active;

static const int color_list_size = 26;
static const color_t color_list[] = {WHITE, RED, LIGHT_RED, DARK_RED, PINK, LIGHT_PINK, ORANGE, CORAL, YELLOW, GOLD,
                      LIGHT_YELLOW, PURPLE, LIGHT_PURPLE, DARK_PURPLE, GREEN, LIGHT_GREEN, DARK_GREEN,
                      BLUE, LIGHT_BLUE, DARK_BLUE, BROWN, LIGHT_BROWN, DARK_BROWN, LIGHT_GRAY, GRAY, BLACK};

static struct {
    float x;
    float y;
    float angle;
} home;

static float deg_to_rad(float deg) {
    return deg * M_PI / 180;
}

static float rad_to_deg(float rad) {
    return rad * 180 / M_PI;
}

static float round_digits(float number, int digits) {
    int mul = pow(10, digits);
    return ((float)((int)(number * mul))) / mul;
}

static int clamp(int value, int min, int max) {
    return value < min ? min : value > max ? max : value;
}

static color_t rgb_to_color(int r, int g, int b) {
    return (r << 16) + (g << 8) + b;
}

static int get_pixel(int x, int y) {
    if (x < 0 || y < 0 || x >= window.width || y >= window.height || window.closed) {
        return -1;
    }

    return window.pixels[x + y * window.width];
}

static void set_pixel(int x, int y) {
    if (x < 0 || y < 0 || x >= window.width || y >= window.height || window.closed) {
        return;
    }

    gfx_point(x, y);

    if (!cursor.cursor_drawing_active && !filling_active) {
        gfx_flush();
    }

    if (!cursor.cursor_drawing_active) {
        window.pixels[x + y * window.width] = current_state.foreground_color;
    } else {
        cursor.cursor_positions[cursor.cursor_position_length] = x + y * window.width;
        cursor.cursor_position_length++;
    }
}

static void reset_cursor_data() {
    cursor.cursor_position_length = 0;
}

static void remove_cursor() {
    if (window.closed) {
        return;
    }

    color_t start_color = current_state.foreground_color;

    for (int i = 0; i < cursor.cursor_position_length; i++) {
        int index = cursor.cursor_positions[i];
        color_t value = window.pixels[index];
        int y = index / window.width;
        int x = index - window.width * y;

        if (current_state.foreground_color != value) {
            set_color(value);
        }

        gfx_point(x, y);
    }

    set_color(start_color);
}

static void draw_current_position() {
    if (!cursor.cursor_active || window.closed) {
        return;
    }

    cursor.cursor_drawing_active = true;

    remove_cursor();
    reset_cursor_data();

    state_t saved_state = current_state;
    color_t current_color = current_state.foreground_color;
    set_color(current_state.cursor_color);

    int size = cursor.cursor_size;
    int upper_angle = 30;

    float len = size / sin(deg_to_rad(90 - upper_angle));

    bool start_is_pen_down = current_state.is_pen_down;

    pen_down();
    right(180 - upper_angle);
    forward(len);

    pen_up();
    back(len);
    pen_down();

    right(2 * upper_angle);
    forward(len);

    current_state.is_pen_down = start_is_pen_down;
    current_state = saved_state;

    gfx_flush();

    set_color(current_color);

    cursor.cursor_drawing_active = false;
}

static void take_step(float current_x, float current_y) {
    if (current_state.is_pen_down) {
        set_pixel((int)current_x, (int)current_y);
    }

    current_state.x = current_x; // WARNING modification
    current_state.y = current_y; // WARNING modification

    if (!cursor.cursor_drawing_active) {
        draw_current_position();
        usleep(speed.moving_delay);
    }
}

static void clear_puffer() {
    XEvent event;
    while (XPending(gfx_display) > 0) {
        XNextEvent(gfx_display, &event);
    }
}

static void draw_cloud_eye(int r) {
    if (r >= 5) {
        for (int i = 0; i < 360; i++) {
            forward(2.0 * r / 6 * M_PI / 360);
            right(1);
        }
        turn_up();
        pen_up();
        forward(1);
        fill();

        pen_up();
        forward(-1);
        left(90);
    } else {
        set_pixel(current_state.x, current_state.y);
    }
}

static void draw_cloud_mouth(int r) {
    turn_to(130);
    for (int i = 0; i < 100; i++) {
        forward(r / 14.0);
        right(1);
    }
}

/* A paint.h használható függvényei */

void create_window(int width, int height) {
    srand(time(NULL));

    gfx_open(width, height, "");
    window.closed = false;
    window.width  = width;
    window.height = height;
    window.pixels = (int*) malloc(width * height * sizeof(int));
    memset(window.pixels, BLACK, window.width * window.height * sizeof(int));

    cursor.cursor_size = CURSOR_SIZE;
    cursor.cursor_active = true;
    cursor.cursor_positions = (int*) malloc(4 * cursor.cursor_size * sizeof(int));
    reset_cursor_data();

    home.x = window.width / 2;
    home.y = window.height / 2;
    home.angle = 270;

    pen_up();
    jump_home();

    set_background(BLACK);
    set_color(WHITE);

    set_arrow_color(GREEN);
    cursor.cursor_drawing_active = false;

    set_speed(7);

    draw_current_position();

    pen_down();
}

void close_window() {
    if (window.closed) {
        return;
    }

    while(1) {
        if(gfx_wait() == 'q')
            break;
    }

    window.closed = true;
    free(window.pixels);
    free(cursor.cursor_positions);

    XDestroyWindow(gfx_display, gfx_window);
    gfx_flush();
}

void set_color(color_t c) {
    set_color_rgb((c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
}

void set_color_rgb(int r, int g, int b) {
    gfx_color(r, g, b);
    current_state.foreground_color = rgb_to_color(r, g, b);
}

void set_background(color_t c) {
    if (window.closed) {
        return;
    }

    color_t start_color = current_state.foreground_color;
    set_color(c);
    for (int i = 0; i < window.width * window.height; i++) {
        if (window.pixels[i] == current_state.background_color) {
            window.pixels[i] = c;
            int x = i % window.width;
            int y = i / window.width;
            gfx_point(x, y);
        }
    }

    set_color(start_color);

    gfx_clear_color((c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
    current_state.background_color = c;
}

void set_background_rgb(int r, int g, int b) {
    set_background(rgb_to_color(r, g, b));
}

void set_arrow_color(color_t c) {
    current_state.cursor_color = c;
}

void set_arrow_color_rgb(int r, int g, int b) {
    set_arrow_color(rgb_to_color(r, g, b));
}

color_t get_random_color() {
    return color_list[rand() % color_list_size];
}

color_t get_random_color_rgb() {
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return (r << 16) + (g << 8) + b;
}

void show_cursor() {
    cursor.cursor_active = true;
    draw_current_position();
    gfx_flush();
}

void hide_cursor() {
    cursor.cursor_active = false;
    remove_cursor();
    gfx_flush();
}

typedef struct pixel_list_item {
    int x;
    int y;
    struct pixel_list_item* next;
} pixel_list_item_t;

void fill() {
    if (cursor.cursor_drawing_active || window.closed) {
        return;
    }

    if (current_state.x < 0 || current_state.y < 0 || current_state.x >= window.width || current_state.y >= window.height) {
        return;
    }

    int color_to_search = get_pixel(current_state.x, current_state.y);
    if (color_to_search == current_state.foreground_color) {
        return;
    }

    int item_size = 0;

    pixel_list_item_t* start = (pixel_list_item_t*) malloc(sizeof(pixel_list_item_t));
    start->x = current_state.x;
    start->y = current_state.y;
    item_size++;

    pixel_list_item_t* last = start;

    filling_active = true;
    while (item_size != 0) {
        int pixel_color = get_pixel(start->x, start->y);
        if (pixel_color == color_to_search) {
            set_pixel(start->x, start->y);

            pixel_list_item_t* left = (pixel_list_item_t*) malloc(sizeof(pixel_list_item_t));
            left->x = start->x - 1;
            left->y = start->y;
            last->next = left;

            pixel_list_item_t* right = (pixel_list_item_t*) malloc(sizeof(pixel_list_item_t));
            right->x = start->x + 1;
            right->y = start->y;
            left->next = right;

            pixel_list_item_t* up = (pixel_list_item_t*) malloc(sizeof(pixel_list_item_t));
            up->x = start->x;
            up->y = start->y - 1;
            right->next = up;

            pixel_list_item_t* down = (pixel_list_item_t*) malloc(sizeof(pixel_list_item_t));
            down->x = start->x;
            down->y = start->y + 1;
            up->next = down;

            down->next = NULL;
            last = down;

            item_size += 4;
        }

        pixel_list_item_t* previous_item = start;
        start = start->next;
        item_size--;

        free(previous_item);
    }

    filling_active = false;
    draw_current_position();
}

void pen_up() {
    current_state.is_pen_down = false;
}

void pen_down() {
    current_state.is_pen_down = true;
}

void forward(float distance) {
    if (window.closed) {
        return;
    }

    float diff_x = round_digits(cos(deg_to_rad(current_state.angle)) * distance, 4);
    float diff_y = round_digits(sin(deg_to_rad(current_state.angle)) * distance, 4);

    float start_x = current_state.x;
    float start_y = current_state.y;

    float current_x, current_y;
    float diff_greater, diff_smaller;
    float start_greater_diff, start_smaller_diff;

    bool x_is_bigger = fabsf(diff_x) > fabsf(diff_y);
    if (x_is_bigger) {
        diff_greater = diff_x;
        diff_smaller = diff_y;
        start_greater_diff = start_x;
        start_smaller_diff = start_y;
    } else {
        diff_greater = diff_y;
        diff_smaller = diff_x;
        start_greater_diff = start_y;
        start_smaller_diff = start_x;
    }

    float distancePerStep = diff_smaller / diff_greater;
    float end = start_greater_diff + diff_greater;
    for (float i = start_greater_diff; diff_greater > 0 ? i <= end : i >= end; diff_greater > 0 ? i++ : i--) {
        current_x = i;
        current_y = start_smaller_diff + (i - start_greater_diff) * distancePerStep;

        if (x_is_bigger) {
            take_step(current_x, current_y);
        } else {
            take_step(current_y, current_x);
        }
    }

    current_state.x = start_x + diff_x;
    current_state.y = start_y + diff_y;
}

void back(float distance) {
    forward(-distance);
}

void left(float angle) {
    right(-angle);
}

void right(float angle) {
    bool to_left = angle < 0;
    angle = fabsf(angle);
    for (int i = 0; i < (int)angle; i++) {
        if (!cursor.cursor_drawing_active) {
            draw_current_position();
            usleep(speed.turning_delay);
        }

        current_state.angle += to_left ? -1 : 1;
    }

    current_state.angle += (angle - (int) angle) * (to_left ? -1 : 1);
    current_state.angle -= (((int) current_state.angle) / 360) * 360;

    if (current_state.angle < 0) {
        current_state.angle += 360;
    }

    current_state.angle = round_digits(current_state.angle, 5);
}

void set_speed(int value) {
    set_move_speed(value);
    set_turn_speed(value);
}

void set_move_speed(int value) {
    value = clamp(value, 0, 10);
    int speed_values[] = {200000, 50000, 25000, 10000, 4000, 1500, 600, 200, 50, 5, 0};
    speed.moving_delay = speed_values[value];
}

void set_turn_speed(int value) {
    value = clamp(value, 0, 10);
    int speed_values[] = {80000, 30000, 15000, 5000, 2000, 800, 300, 100, 25, 5, 0};
    speed.turning_delay = speed_values[value];
}

void turn_to(float goal) {
    goal = fmod(goal, 360);

    float distanceToRight = (360 + goal - current_state.angle);
    distanceToRight = fmod(distanceToRight, 360);

    float distanceToLeft = (360 + current_state.angle - goal);
    distanceToLeft = fmod(distanceToLeft, 360);

    if (distanceToRight <= distanceToLeft) {
        right(distanceToRight);
    } else {
        left(distanceToLeft);
    }

    draw_current_position();
}

void turn_up() {
    turn_to(270);
}

void turn_down() {
    turn_to(90);
}

void turn_left() {
    turn_to(180);
}

void turn_right() {
    turn_to(0);
}

void goto_position(float x, float y) {
    if (window.closed) {
        return;
    }

    float dest_x = x;
    float dest_y = y;

    float start_x = current_state.x;
    float start_y = current_state.y;

    float diff_x = dest_x - start_x;
    float diff_y = dest_y - start_y;

    float angle = fabsf(rad_to_deg(atan((float) diff_x / diff_y)));
    if (dest_x <= start_x && dest_y >= start_y) {
        angle =  90 + angle;
    } else if (dest_x <= start_x && dest_y <= start_y) {
        angle =  270 - angle;
    } else if (dest_x > start_x && dest_y <= start_y) {
        angle =  270 + angle;
    } else if (dest_x > start_x && dest_y > start_y) {
        angle = 90 - angle;
    } else {
        printf("WHAT'S HAPPENING?\n");
    }

    turn_to(angle);

    forward(sqrt(diff_x * diff_x + diff_y * diff_y));

    current_state.x = x;
    current_state.y = y;

    if (current_state.is_pen_down) {
        set_pixel(x, y);
    }
}

void jump_to_position(float x, float y) {
    if (window.closed) {
        return;
    }

    current_state.x = x;
    current_state.y = y;
}

void set_home() {
    home.x = current_state.x;
    home.y = current_state.y;
    home.angle = current_state.angle;
}

void goto_home() {
    goto_position(home.x, home.y);
    current_state.angle = home.angle;
}

void jump_home() {
    current_state.x = home.x;
    current_state.y = home.y;
    current_state.angle = home.angle;
}

float get_x_position() {
    return current_state.x;
}

float get_y_position() {
    return current_state.y;
}

float get_angle() {
    return current_state.angle;
}

color_t get_foreground_color() {
    return current_state.foreground_color;
}

color_t get_background_color() {
    return current_state.background_color;
}

color_t get_cursor_color() {
    return current_state.cursor_color;
}

int is_pen_down() {
    return current_state.is_pen_down;
}

int is_cursor_active() {
    return cursor.cursor_active;
}

void save_image(const char* filename) {
    if (window.closed) {
        return;
    }

    char ext[] = ".ppm";
    char fname[strlen(filename) + 5];
    strcpy(fname, filename);
    if (!(strlen(filename) >= strlen(ext) && strncmp(filename + strlen(filename) - strlen(ext), ext, strlen(ext)) == 0)) {
        strcat(fname, ext);
    }

    FILE* file = fopen(fname, "w");
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n%d\n", window.width, window.height, 255);

    for (int i = 0; i < window.width * window.height; i++) {
        color_t c = window.pixels[i];
        fprintf(file, "%d %d %d ", (c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
    }

    fclose(file);
}

bool new_event_is_left_click() {
    if (window.closed) {
        return false;
    }
    clear_puffer();
    return gfx_wait() == 1; // 1: left click
}

bool new_event_is_button(char key) {
    if (window.closed) {
        return false;
    }
    clear_puffer();
    return gfx_wait() == key;
}

int last_event_x() {
    return gfx_xpos();
}

int last_event_y() {
    return gfx_ypos();
}

void draw_cloud(float size) {
    if (size < 8) {
        size = 8;
    }

    state_t start_state = current_state;

    pen_up();
    turn_up();
    back(size * 0.7);
    left(90);
    forward(size / 2.8);
    right(90);
    pen_down();

    float r = size / 8;
    float angle = 135;
    for (int i = 0; i < 8; i++) {
        left(angle);
        for (int i = 0; i < 180; i++) {
            forward(2 * r * M_PI / 180);

            int diff = 15.0;
            if (current_state.angle <= diff || current_state.angle >= (360 - diff) || (current_state.angle >= (180 - diff) && current_state.angle <= (180 + diff))) {
                forward(0.75 * size / 100.0);
            }

            right(1);
        }
    }

    pen_up();
    turn_right();
    forward(size / 2.8);
    left(90);
    forward(size * 0.7);

    forward(size / 4.5);
    left(90);
    forward(size / 3.0);
    pen_down();

    draw_cloud_eye(r);

    pen_up();
    back(size / 3.0 * 2.0);
    pen_down();

    draw_cloud_eye(r);

    pen_up();
    turn_up();
    back(size / 2.0);
    right(90);
    forward(size / 16.0);
    pen_down();

    draw_cloud_mouth(r);

    pen_up();
    forward(size / 3.0);
    turn_up();
    back(size / 4.5);

    current_state = start_state;
}
