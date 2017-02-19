#include <cairo/cairo.h>
#include <cairo/cairo-ft.h>
#include <cairo/cairo-pdf.h>

int main(int argc, char** argv)
{
  double width = 1920.0;
  double height = 1080.0;
  cairo_surface_t* surf = cairo_pdf_surface_create("test.pdf", width, height);
  cairo_t* cr = cairo_create(surf);

  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_set_line_width(cr, 6.0);

  cairo_move_to(cr, 32.0, 32.0);
  cairo_line_to(cr, 960.0, 520.0);

  cairo_stroke(cr);

  double pt_size = 64.0;

  // Note: FT assertions below are ignored.
  FT_Library ft_library;
  FT_Init_FreeType(&ft_library);

  FT_Face ft_face;
  FT_New_Face(ft_library, "/usr/share/fonts/cantarell/Cantarell-Regular.otf", 0, &ft_face);

  cairo_font_face_t* font = cairo_ft_font_face_create_for_ft_face(ft_face, 0);
  cairo_glyph_t glyphs[2];

  glyphs[0].index = 73; // 'h'
  glyphs[0].x = 128.0;
  glyphs[0].y = 256.0;
  glyphs[1].index = 74; // 'i'
  glyphs[1].x = 128.0 + 64.0;
  glyphs[1].y = 256.0;

  cairo_set_font_face(cr, font);
  cairo_set_font_size(cr, pt_size);
  cairo_show_glyphs(cr, glyphs, 2);

  cairo_font_face_destroy(font);

  cairo_show_page(cr);

  cairo_destroy(cr);
  cairo_surface_destroy(surf);

  FT_Done_FreeType(ft_library);

  return 0;
}