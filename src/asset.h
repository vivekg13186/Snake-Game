//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// rTexpacker v2.0 Atlas Descriptor Code exporter v2.0                          //
//                                                                              //
// more info and bugs-report:  github.com/raylibtech/rtools                     //
// feedback and support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2020-2022 raylib technologies (@raylibtech)                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#define ATLAS_ASSET_IMAGE_PATH      "asset.png"
#define ATLAS_ASSET_SPRITE_COUNT    34

// Atlas sprite properties
typedef struct rtpAtlasSprite {
    const char *nameId;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;
} rtpAtlasSprite;

// Atlas sprites array
static rtpAtlasSprite rtpDescAsset[34] = {
    { "apple", 0, 0, 269, 586, 42, 41, 0, false, 0, 0, 42, 41 },
    { "banner", 0, 0, 478, 0, 478, 521, 0, false, 0, 0, 478, 521 },
    { "checker", 0, 0, 0, 586, 128, 128, 0, false, 0, 0, 128, 128 },
    { "clock", 0, 0, 1838, 0, 190, 201, 0, false, 0, 0, 190, 201 },
    { "game_over", 0, 0, 0, 0, 478, 586, 0, false, 0, 0, 478, 586 },
    { "help", 0, 0, 956, 0, 478, 502, 0, false, 0, 0, 478, 502 },
    { "key", 0, 0, 128, 586, 59, 57, 0, false, 0, 0, 59, 57 },
    { "sound_off", 0, 0, 1434, 0, 209, 206, 0, false, 0, 0, 209, 206 },
    { "sound_on", 0, 0, 1643, 0, 195, 206, 0, false, 0, 0, 195, 206 },
    { "snake_body_bottom_left", 0, 0, 477, 586, 40, 40, 0, false, 0, 4, 36, 36 },
    { "snake_body_bottom_right", 0, 0, 517, 586, 40, 40, 0, false, 4, 4, 36, 36 },
    { "snake_body_horz", 0, 0, 557, 586, 40, 40, 0, false, 0, 5, 40, 30 },
    { "snake_body_top_left", 0, 0, 597, 586, 40, 40, 0, false, 0, 0, 36, 36 },
    { "snake_body_top_right", 0, 0, 397, 586, 40, 40, 0, false, 4, 0, 36, 36 },
    { "snake_body_vert", 0, 0, 438, 587, 38, 38, 0, false, 5, 0, 30, 40 },
    { "snake_head_down", 0, 0, 311, 586, 43, 41, 0, false, 0, 0, 43, 41 },
    { "snake_head_left", 0, 0, 187, 586, 41, 43, 0, false, 0, 0, 41, 43 },
    { "snake_head_right", 0, 0, 228, 586, 41, 43, 0, false, 0, 0, 41, 43 },
    { "snake_head_up", 0, 0, 354, 586, 43, 41, 0, false, 0, 0, 43, 41 },
    { "snake_tail_down", 0, 0, 637, 586, 40, 40, 0, false, 5, 0, 30, 40 },
    { "snake_tail_left", 0, 0, 677, 586, 40, 40, 0, false, 0, 5, 40, 30 },
    { "snake_tail_right", 0, 0, 717, 586, 40, 40, 0, false, 0, 5, 40, 30 },
    { "snake_tail_up", 0, 0, 757, 586, 40, 40, 0, false, 5, 0, 30, 40 },
    { "0", 0, 0, 797, 586, 11, 14, 0, false, 0, 0, 11, 14 },
    { "1", 0, 0, 808, 586, 8, 14, 0, false, 0, 0, 8, 14 },
    { "2", 0, 0, 816, 586, 11, 14, 0, false, 0, 0, 11, 14 },
    { "3", 0, 0, 827, 586, 11, 14, 0, false, 0, 0, 11, 14 },
    { "4", 0, 0, 838, 586, 12, 14, 0, false, 0, 0, 12, 14 },
    { "5", 0, 0, 850, 586, 11, 14, 0, false, 0, 0, 11, 14 },
    { "6", 0, 0, 861, 586, 11, 14, 0, false, 0, 0, 11, 14 },
    { "7", 0, 0, 898, 586, 11, 13, 0, false, 0, 0, 11, 13 },
    { "8", 0, 0, 872, 586, 11, 14, 0, false, 0, 0, 11, 14 },
    { "9", 0, 0, 883, 586, 11, 14, 0, false, 0, 0, 11, 14 },
    { "point", 0, 0, 894, 586, 4, 14, 0, false, 0, 10, 4, 4 },
};
