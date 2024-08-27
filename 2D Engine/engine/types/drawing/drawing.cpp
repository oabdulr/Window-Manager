#include "drawing.h"

void drawing::cleanup_textures()
{
	for (auto texture_pair : engine->loaded_textures)
		glDeleteTextures(1, &texture_pair.second);
}

void drawing::draw_texture(const char* name, vec2 tl, vec2 bl, vec2 tr, vec2 br, bool resolve)
{
	this->set_color(vec3(255, 255, 255));
	glEnable(GL_TEXTURE_2D);

	int tex = engine->drawing->get_texture(name);
	if (!tex)
		return;

	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);

	if (resolve)
	{
		tl.resolve_engine_pixel(engine->screen_size);
		bl.resolve_engine_pixel(engine->screen_size);
		tr.resolve_engine_pixel(engine->screen_size);
		br.resolve_engine_pixel(engine->screen_size);
	}

	glTexCoord2f(0.0f, 0.0f); glVertex2f(tl.x, tl.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(tr.x, tr.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(br.x, br.y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(bl.x, bl.y);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

int drawing::load_texture(const char* path, const char* name)
{
	int width, height, channels;
	stbi_uc* image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
	if (!image)
	{
		printf("Failed to load image\n");
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(image);

	engine->loaded_textures[name] = textureID;

	return textureID;
}

void drawing::set_color(vec3 color, bool is32)
{
	glColor3f(is32 ? color.x / 255.f : color.x, is32 ? color.y / 255.f : color.y, is32 ? color.z / 255.f : color.z);
}

void drawing::set_thickness(int t)
{
	glLineWidth(t);
}

int drawing::get_texture(const char* name)
{
	if (engine->loaded_textures.find(name) != engine->loaded_textures.end())
		return engine->loaded_textures[name];

	return engine->loaded_textures["?"];
}

void drawing::draw_circle(vec2 start, float r, int num_segments, bool dotted) {
	glBegin(dotted ? GL_LINES : GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		vec2 move = vec2(x + start.x, y + start.y);
		// flip
		move.resolve_engine_pixel(engine->screen_size);
		glVertex2f(move.x, move.y);//output vertex 
	}
	glEnd();
}

void drawing::draw_line(vec2 start, vec2 end, int thickness)
{
	// flip
	start.resolve_engine_pixel(engine->screen_size);
	end.resolve_engine_pixel(engine->screen_size);

	glLineWidth(thickness);
	glBegin(GL_LINES);
	glVertex2f(start.x, start.y);
	glVertex2f(end.x, end.y);
	glEnd();


	glLineWidth(1);
}

void drawing::draw_rect(rect data, int thickness)
{
	// top
	this->draw_line(vec2(data.x, data.y), vec2(data.x + data.width, data.y), thickness);
	// left side
	this->draw_line(vec2(data.x, data.y), vec2(data.x, data.y + data.height + 1), thickness); // Need to add +1 to make it equal??
	// right side
	this->draw_line(vec2(data.x + data.width, data.y), vec2(data.x + data.width, data.y + data.height), thickness);
	// bottom
	this->draw_line(vec2(data.x, data.y + data.height), vec2(data.x + data.width, data.y + data.height), thickness);
}

void drawing::draw_filled_rect(rect data, int thickness)
{
	// flip
	vec2 tl = vec2(data.x, data.y).resolve_engine_pixel_v(engine->screen_size);
	vec2 tr = vec2(data.x + data.width, data.y).resolve_engine_pixel_v(engine->screen_size);
	vec2 br = vec2(data.x + data.width, data.y + data.height).resolve_engine_pixel_v(engine->screen_size);
	vec2 bl = vec2(data.x, data.y + data.height).resolve_engine_pixel_v(engine->screen_size);

	glLineWidth(thickness);
	//glPolygonMode( GL_FRONT, GL_FILL );
	glBegin(GL_QUADS);
	glVertex2f(tl.x, tl.y);
	glVertex2f(tr.x, tr.y);
	glVertex2f(br.x, br.y);
	glVertex2f(bl.x, bl.y);
	glEnd();
}

void drawing::render_char(glyph* glyph, vec2 pos, char c, vec2 offsets, float raw_scale, int outline, vec4 color)
{
	if (!glyph)
		return;

	glBindTexture(GL_TEXTURE_2D, glyph->texture_id);
	glBegin(GL_QUADS);

	int width = glyph->width * raw_scale;
	int height = glyph->height * raw_scale;

	if (outline)
	{
		glColor4f(0.0f, 0.0f, 0.0f, 1.f);

		vec2 tl{ offsets.x + pos.x - outline, pos.y - (outline + 1) + offsets.y };
		vec2 bl{ offsets.x + pos.x - outline, pos.y + height + (outline + 1) + offsets.y };
		vec2 tr{ offsets.x + pos.x + width + outline, pos.y - (outline + 1) + offsets.y };
		vec2 br{ offsets.x + pos.x + width + outline, pos.y + height + (outline + 1) + offsets.y };


		tl.resolve_engine_pixel(this->engine->screen_size);
		bl.resolve_engine_pixel(this->engine->screen_size);
		tr.resolve_engine_pixel(this->engine->screen_size);
		br.resolve_engine_pixel(this->engine->screen_size);


		glTexCoord2f(0.0f, 0.0f); glVertex2f(tl.x, tl.y);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(tr.x, tr.y);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(br.x, br.y);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(bl.x, bl.y);
	}


	glColor4f(color.x, color.y, color.z, color.w);

	vec2 tl{ offsets.x + pos.x, pos.y + offsets.y };
	vec2 bl{ offsets.x + pos.x, pos.y + height + offsets.y };
	vec2 tr{ offsets.x + pos.x + width, pos.y + offsets.y };
	vec2 br{ offsets.x + pos.x + width, pos.y + height + offsets.y };


	tl.resolve_engine_pixel(this->engine->screen_size);
	bl.resolve_engine_pixel(this->engine->screen_size);
	tr.resolve_engine_pixel(this->engine->screen_size);
	br.resolve_engine_pixel(this->engine->screen_size);


	glTexCoord2f(0.0f, 0.0f); glVertex2f(tl.x, tl.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(tr.x, tr.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(br.x, br.y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(bl.x, bl.y);

	glEnd();
}


void drawing::render_char(vec2 pos, char c, vec2 offsets, float raw_scale, vec4 color)
{
	if (!engine->current_font)
		return;

	glyph* glyph = engine->current_font->get_glyph(c);

	if (!glyph)
		return;

	int width = glyph->width * raw_scale;
	int height = glyph->height * raw_scale;

	glBindTexture(GL_TEXTURE_2D, glyph->texture_id);
	glBegin(GL_QUADS);

	glColor4f(color.x, color.y, color.z, color.w);

	vec2 tl{ offsets.x + pos.x, pos.y + offsets.y };
	vec2 bl{ offsets.x + pos.x, pos.y + height + offsets.y };
	vec2 tr{ offsets.x + pos.x + width, pos.y + offsets.y };
	vec2 br{ offsets.x + pos.x + width, pos.y + height + offsets.y };


	tl.resolve_engine_pixel(this->engine->screen_size);
	bl.resolve_engine_pixel(this->engine->screen_size);
	tr.resolve_engine_pixel(this->engine->screen_size);
	br.resolve_engine_pixel(this->engine->screen_size);


	glTexCoord2f(0.0f, 0.0f); glVertex2f(tl.x, tl.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(tr.x, tr.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(br.x, br.y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(bl.x, bl.y);

	glEnd();
}

vec2 drawing::render_string(vec2 pos, std::string string, int pt_scale, int outline, float cutoff, vec4 color, bool apply_scale)
{

	vec2 offsets{ 0, 0 };

	glEnable(GL_TEXTURE_2D);
	float raw_scale;
	if (apply_scale)
		raw_scale = static_cast<float>((pt_scale * (this->engine->desktop_scale * 1.3f))) / static_cast<float>(engine->current_font->get_max_size());
	else
		raw_scale = static_cast<float>((pt_scale) / static_cast<float>(engine->current_font->get_max_size()));

	engine->text_cursor->raw_scale = raw_scale;

	float space_pixel = 18 * raw_scale;
	float padding_pixel = 1 * raw_scale;

	if (!engine->current_font)
		return { };

	for (char c : string)
	{
		if (c == ' ')
			offsets.x += space_pixel;
		if ((int)c == 1 || c == '\n')
		{
			offsets.y += engine->current_font->get_fixed_height() * raw_scale;
			offsets.x = 0;
			continue;
		}

		glyph* p_glyph = engine->current_font->get_glyph(c);

		if (!p_glyph)
			continue;

		if (outline == -1)
		{
			this->render_char({ pos.x + 1, pos.y }, c, offsets, raw_scale, { 0.f, 0.f, 0.f, 1.f });
			this->render_char({ pos.x - 1, pos.y }, c, offsets, raw_scale, { 0.f, 0.f, 0.f, 1.f });
			this->render_char({ pos.x, pos.y + 1 }, c, offsets, raw_scale, { 0.f, 0.f, 0.f, 1.f });
			this->render_char({ pos.x, pos.y - 1 }, c, offsets, raw_scale, { 0.f, 0.f, 0.f, 1.f });

			this->render_char({ pos.x + 1, pos.y + 1 }, c, offsets, raw_scale, { 0.f, 0.f, 0.f, 1.f });
			this->render_char({ pos.x - 1, pos.y + 1 }, c, offsets, raw_scale, { 0.f, 0.f, 0.f, 1.f });
			this->render_char({ pos.x + 1, pos.y - 1 }, c, offsets, raw_scale, { 0.f, 0.f, 0.f, 1.f });
			this->render_char({ pos.x - 1, pos.y - 1 }, c, offsets, raw_scale, { 0.f, 0.f, 0.f, 1.f });

			this->render_char(p_glyph, pos, c, offsets, raw_scale, 0, color);
		}
		else
			this->render_char(p_glyph, pos, c, offsets, raw_scale, outline, color);

		if (cutoff != 0 && cutoff <= offsets.x)
			break;

		offsets.x += static_cast<float>(p_glyph->width * raw_scale) + 5;
	}

	glDisable(GL_TEXTURE_2D);

	return offsets;
}