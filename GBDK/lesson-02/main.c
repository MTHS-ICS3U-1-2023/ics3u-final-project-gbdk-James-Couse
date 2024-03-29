// copyright (c) 2023 James Couse All rights reserved
//
// Created by: James Couse
// Created on: Dec 2023
// This program is the "Space Aliens" program for the GameBoy

#include <gb/gb.h>
#include <stdio.h>

#include "SpaceAliens.c"

int main() {
    // This displays a sprite on the GameBoy screen
    set_sprite_data(0, 16, SpaceAliens);

    set_sprite_tile(0, 15);

    move_sprite(0, 88, 78);

    set_sprite_tile(1, 5);
    set_sprite_tile(2, 10);

    move_sprite(1, 8, 144);
    move_sprite(2, 64, 64);

    SHOW_SPRITES;

    return 0;
}
