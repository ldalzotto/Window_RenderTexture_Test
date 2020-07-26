#pragma once

#include <stdint.h>

struct Vector3f
{
	unsigned char x, y, z;
};

struct Texture
{
	uint16_t WIDTH, HEIGHT;
	Vector3f* Pixels;
};

void Texture_alloc(Texture* p_texture, uint16_t p_width, uint16_t p_height);
void Texture_free(Texture* p_texture);
void Texture_fill(Texture* p_texture, Vector3f* p_color);
size_t Texture_getByteSize(Texture* p_texture);
