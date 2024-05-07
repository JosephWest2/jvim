#pragma once

#include "main.h"

typedef struct {
    int charwidth;
    int lineHeight;
} RenderState;

void Render(JVIMState* jvs);
