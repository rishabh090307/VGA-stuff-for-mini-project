#ifndef LANDMARKS_H
#define LANDMARKS_H

#define LANDMARK_COUNT 38

typedef struct {
    const char *name;
    int x;
    int y;
} Landmark;

extern Landmark landmarks[LANDMARK_COUNT];

#endif