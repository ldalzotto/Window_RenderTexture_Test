#include "Texture.h"

#include <cstdlib>
#include <string.h>

void Texture_alloc(Texture* p_texture, uint16_t p_width, uint16_t p_height)
{
	p_texture->Pixels = (Vector3f*) calloc(1, sizeof(Vector3f) * (p_width * p_height));
	p_texture->WIDTH = p_width;
	p_texture->HEIGHT = p_height;
};

void Texture_free(Texture* p_texture)
{
	if (p_texture->Pixels)
	{
		free(p_texture->Pixels);
		p_texture->Pixels = nullptr;
	}
}

void Texture_fill(Texture* p_texture, Vector3f* p_color)
{
	size_t l_count = p_texture->HEIGHT * p_texture->WIDTH;
	for (size_t i = 0; i < l_count; i++)
	{
		p_texture->Pixels[i] = *p_color;
	}
};

size_t Texture_getByteSize(Texture* p_texture)
{
	return sizeof(Vector3f) * p_texture->WIDTH * p_texture->HEIGHT;
};