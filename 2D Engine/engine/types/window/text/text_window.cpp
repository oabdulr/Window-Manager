#include "../window.h"

void text_window::content() {

	// draw number lines

	float lines = floor(this->size.height / font_size) - 1;
	int y_offset = 10;
	for (int line = 0; line < lines; line++)
	{
		engine->drawing->render_string(vec2(this->size.x + 10, this->size.y + y_offset + (font_size * line)), std::format("{}", line), font_size, -1);
		engine->drawing->draw_line(vec2(this->size.x + 5, this->size.y + y_offset + (font_size * line) + height + 20), vec2(this->size.x + this->size.width - 5, this->size.y + y_offset + (font_size * line) + height + 20));

		if (this->line_data.find(line) == this->line_data.end())
			this->line_data[line] = std::tuple<std::string, vec2>("", { this->size.x + 10, this->size.y + y_offset + (font_size * line) });
		else
		{
			vec2 pos = vec2(this->size.x + 15 + engine->current_font->get_max_size() * (engine->text_cursor->raw_scale), this->size.y + y_offset + (font_size * line));
			vec2 offset_data = engine->drawing->render_string(pos, std::get<0>(this->line_data[line]), font_size - 3, -1, this->size.width - 55);
			this->line_data[line] = std::tuple<std::string, vec2>(std::get<0>(this->line_data[line]), pos + offset_data);
		}
	}
}

void text_window::handle_input() {
	if (mouse_cursor::m1)
	{

		float lines = floor(this->size.height / font_size) - 1;
		int y_offset = 10;
		for (int line = 0; line < lines; line++)
		{
			rect line_rect = rect(this->size.x + 5, this->size.y + y_offset + (font_size * line), this->size.width - 5, this->height + 20);
			if (line_rect.is_inside(mouse_cursor::mouse_positon))
			{
				engine->text_cursor->should_draw = true;
				engine->text_cursor->pos = std::get<1>(this->line_data[line]);

				key_manager::current_line = line;
				key_manager::current_window = this;
			}
		}

		if (!holding)
		{
			holding++;
			return;
		}
	}
	else if (!mouse_cursor::m1 && holding)
	{
		holding = 0;
		holding_position.set(0, 0);
	}
}