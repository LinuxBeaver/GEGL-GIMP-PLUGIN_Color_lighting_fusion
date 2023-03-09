/* This file is an image processing operation for GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright 2006 Øyvind Kolås <pippin@gimp.org>
 * 2022 GEGL ColorLightFusion - Beaver.
 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES



enum_start (gegl_blend_mode_type4)
  enum_value (GEGL_BLEND_MODE_TYPE_GRAINMERGE, "grainmerge",
              N_("Grain Merge"))
  enum_value (GEGL_BLEND_MODE_TYPE_HSLCOLOR,      "hslcolor",
              N_("HSL Color"))
  enum_value (GEGL_BLEND_MODE_TYPE_SOFTLIGHT,      "softlight",
              N_("Soft Light"))
  enum_value (GEGL_BLEND_MODE_TYPE_OVERLAY,      "overlay",
              N_("Overlay"))
  enum_value (GEGL_BLEND_MODE_TYPE_BURN,      "burn",
              N_("Burn"))
  enum_value (GEGL_BLEND_MODE_TYPE_LCHCOLOR,      "lchcolor",
              N_("LCh Color"))
  enum_value (GEGL_BLEND_MODE_TYPE_MULTIPLY,      "multiply",
              N_("Multiply"))
  enum_value (GEGL_BLEND_MODE_TYPE_LINEARLIGHT,      "linearlight",
              N_("Linear Light"))
 enum_value (GEGL_BLEND_MODE_TYPE_HARDLIGHT,      "hardlight",
              N_("Hard Light"))
 enum_value (GEGL_BLEND_MODE_TYPE_ADDITION,      "addition",
              N_("Addition"))
 enum_value (GEGL_BLEND_MODE_TYPE_SCREEN,      "screen",
              N_("Screen"))
 enum_value (GEGL_BLEND_MODE_TYPE_HSVHUE,      "hsvhue",
              N_("HSV Hue"))
 enum_value (GEGL_BLEND_MODE_TYPE_ANTIERASE,      "antierase",
              N_("No Color or Blend Mode"))
property_enum (blendmode, _("Color Blend Mode"),
    GeglBlendModeType4, gegl_blend_mode_type4,
    GEGL_BLEND_MODE_TYPE_ANTIERASE)
enum_end (GeglBlendModeType4)



property_color (color, _("Color to blend"), "#")
    ui_meta     ("role", "color-primary")

property_double (scale, _("Sharpen"), 0.0)
    description(_("Scaling factor for unsharp-mask, the strength of effect"))
    value_range (0.0, 3.0)
    ui_range    (0.0, 3.0)
    ui_gamma    (3.0)


property_double (sat, _("Saturation (RESETS at 1)"), 1.0)
    description(_("Scale, strength of effect"))
    value_range (0.0, 10.0)
    ui_range (0.0, 2.0)

property_double (contrast, _("Contrast (RESETS AT 1)"),  1.0)
   description  (_("Magnitude of contrast scaling >1.0 brighten < 1.0 darken"))
   value_range  (-5.0, 5.0)
   ui_range     (0.0, 2.0)

property_double (brightness, _("Brightness"), 0.0)
   description  (_("Amount to increase brightness"))
   value_range  (-3.0, 3.0)
   ui_range     (-1.0, 1.0)

property_double (lightness, _("Lightness"), 0.0)
   description  (_("Lightness adjustment"))
   value_range  (-70, 70.0)

property_double (shadows, _("Shadows"), 0.0)
    description (_("Adjust exposure of shadows"))
    value_range (-100.0, 100.0)

property_double (highlights, _("Highlights"), 0.0)
    description (_("Adjust exposure of highlights"))
    value_range (-100.0, 100.0)

property_double (whitepoint, _("Shadow Highlight White point adjustment"), 0.0)
    description (_("Shift white point"))
    value_range (-10.0, 10.0)

property_double (radius, _("Shadow Highlight Radius (RESETS AT 100)"), 100.0)
    description (_("Spatial extent"))
    value_range (0.1, 1500.0)
    ui_range    (0.1, 200.0)

property_double (compress, _("Shadow Hightlight Compress (RESETS AT 50)"), 50.0)
    description (_("Compress the effect on shadows/highlights and preserve midtones"))
    value_range (0.0, 100.0)

property_double (shadows_ccorrect, _("Shadows color adjustment (RESETS AT 100)"), 100.0)
    description (_("Adjust saturation of shadows"))
    value_range (0.0, 100.0)

property_double (highlights_ccorrect, _("Highlights color adjustment (RESETS AT 50)"), 50.0)
    description (_("Adjust saturation of highlights"))
    value_range (0.0, 100.0)


property_double (red, _("Red Channel (Resets at 1)"), 1.0)
  description(_("Set the red amount for the red channel"))
  value_range (-2.0, 2.0)


property_double (green, _("Green Channel (Resets at 1)"), 1.0)
  description(_("Set the green amount for the green channel"))
  value_range (-2.0, 2.0)

property_double (blue, _("Blue channel (Resets at 1)"), 1.0)
  description(_("Set the blue amount for the blue channel"))
  value_range (-2.0, 2.0)




#else

#define GEGL_OP_META
#define GEGL_OP_NAME     commonadjustments
#define GEGL_OP_C_SOURCE commonadjustments.c

#include "gegl-op.h"




typedef struct
{
  GeglNode *input;
  GeglNode *sa; 
  GeglNode *nop; 
  GeglNode *bloom; 
  GeglNode *unsharpmask; 
  GeglNode *softglow; 
  GeglNode *grainmerge; 
  GeglNode *softlight; 
  GeglNode *hardlight; 
  GeglNode *hslcolor; 
  GeglNode *hsvhue; 
  GeglNode *antierase; 
  GeglNode *addition; 
  GeglNode *crop; 
  GeglNode *shadowhighlights; 
  GeglNode *lchcolor; 
  GeglNode *burn; 
  GeglNode *multiply; 
  GeglNode *linearlight; 
  GeglNode *overlay; 
  GeglNode *screen; 
  GeglNode *gegl1;
  GeglNode *color;
  GeglNode *lightchroma;
  GeglNode *saturation; 
  GeglNode *noisereduction;  
  GeglNode *bc;  
  GeglNode *channelmixer;  
  GeglNode *output;
}State;

static void
update_graph (GeglOperation *operation)
{
  GeglProperties *o = GEGL_PROPERTIES (operation);
  State *state = o->user_data;
  if (!state) return;

  GeglNode *usethis = state->antierase; /* the default */
  switch (o->blendmode) {
    case GEGL_BLEND_MODE_TYPE_GRAINMERGE: usethis = state->grainmerge; break;
    case GEGL_BLEND_MODE_TYPE_HSLCOLOR: usethis = state->hslcolor; break;
    case GEGL_BLEND_MODE_TYPE_SOFTLIGHT: usethis = state->softlight; break;
    case GEGL_BLEND_MODE_TYPE_OVERLAY: usethis = state->overlay; break;
    case GEGL_BLEND_MODE_TYPE_BURN: usethis = state->burn; break;
    case GEGL_BLEND_MODE_TYPE_LCHCOLOR: usethis = state->lchcolor; break;
    case GEGL_BLEND_MODE_TYPE_MULTIPLY: usethis = state->multiply; break;
    case GEGL_BLEND_MODE_TYPE_LINEARLIGHT: usethis = state->linearlight; break;
    case GEGL_BLEND_MODE_TYPE_HARDLIGHT: usethis = state->hardlight; break;
    case GEGL_BLEND_MODE_TYPE_ADDITION: usethis = state->addition; break;
    case GEGL_BLEND_MODE_TYPE_SCREEN: usethis = state->screen; break;
    case GEGL_BLEND_MODE_TYPE_HSVHUE: usethis = state->hsvhue; break;
    case GEGL_BLEND_MODE_TYPE_ANTIERASE: usethis = state->antierase; break;
  }

  gegl_node_link_many (state->input, state->sa, state->output, NULL);
  gegl_node_link_many (state->input, state->nop, state->unsharpmask, state->bc, state->lightchroma, state->saturation, state->shadowhighlights,  usethis, state->channelmixer,   NULL);
  gegl_node_connect_from (usethis, "aux", state->color, "output");
  gegl_node_connect_from (state->sa, "aux", state->channelmixer, "output");

}

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
GeglProperties *o = GEGL_PROPERTIES (operation);
  GeglNode *input, *sa, *output, *nop, *color, *unsharpmask, *bc, *screen, *antierase, *saturation, *bloom, *addition, *shadowhighlights, *linearlight, *hardlight, *hsvhue, *crop, *lightchroma, *burn, *multiply, *softglow, *hslcolor, *lchcolor, *overlay, *softlight, *channelmixer, *grainmerge;

  input    = gegl_node_get_input_proxy (gegl, "input");
  output   = gegl_node_get_output_proxy (gegl, "output");


  color    = gegl_node_new_child (gegl,
                                  "operation", "gegl:color",
                                  NULL);

  bc    = gegl_node_new_child (gegl,
                                  "operation", "gegl:brightness-contrast",
                                  NULL);

  sa    = gegl_node_new_child (gegl,
                                  "operation", "gegl:src-atop",
                                  NULL);


  crop    = gegl_node_new_child (gegl,
                                  "operation", "gegl:crop",
                                  NULL);


  nop    = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",
                                  NULL);

hslcolor = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 39, NULL);

grainmerge = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 47, NULL);

softlight = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 45, NULL);

addition = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 33, NULL);


hardlight = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 44, NULL);


hsvhue = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 37, NULL);


overlay = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 23, NULL);

burn = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 43,  "blend-space", 1, NULL);

lchcolor = gegl_node_new_child (gegl,
                                    "operation", "gimp:layer-mode", "layer-mode", 26,  "blend-space", 3, NULL);

multiply = gegl_node_new_child (gegl,
                                    "operation", "gimp:layer-mode", "layer-mode", 30,  "blend-space", 2, NULL);

linearlight = gegl_node_new_child (gegl,
                                    "operation", "gimp:layer-mode", "layer-mode", 50,  "blend-space", 2, NULL);

screen = gegl_node_new_child (gegl,
                                    "operation", "gimp:layer-mode", "layer-mode", 31,  "blend-space", 2, NULL);

antierase = gegl_node_new_child (gegl,
                                    "operation", "gimp:layer-mode", "layer-mode", 63,  "blend-space", 2, NULL);



  lightchroma    = gegl_node_new_child (gegl,
                                  "operation", "gegl:hue-chroma",
                                  NULL);

  saturation    = gegl_node_new_child (gegl,
                                  "operation", "gegl:saturation",
                                  NULL);



  unsharpmask    = gegl_node_new_child (gegl,
                                  "operation", "gegl:unsharp-mask",
                                  NULL);

  shadowhighlights    = gegl_node_new_child (gegl,
                                  "operation", "gegl:shadows-highlights",
                                  NULL);

  channelmixer    = gegl_node_new_child (gegl,
                                  "operation", "gegl:channel-mixer",
                                  NULL);








  gegl_operation_meta_redirect (operation, "sat", saturation, "scale");
  gegl_operation_meta_redirect (operation, "lightness", lightchroma, "lightness");
  gegl_operation_meta_redirect (operation, "color", color, "value");
  gegl_operation_meta_redirect (operation, "scale", unsharpmask, "scale");
     gegl_operation_meta_redirect (operation, "radius", shadowhighlights, "radius");
      gegl_operation_meta_redirect (operation, "shadows", shadowhighlights, "shadows");
      gegl_operation_meta_redirect (operation, "highlights", shadowhighlights, "highlights");
      gegl_operation_meta_redirect (operation, "whitepoint", shadowhighlights, "whitepoint");
      gegl_operation_meta_redirect (operation, "compress", shadowhighlights, "compress");
      gegl_operation_meta_redirect (operation, "shadows-ccorrect", shadowhighlights, "shadows-ccorrect");
      gegl_operation_meta_redirect (operation, "highlights-ccorrect", shadowhighlights, "highlights-ccorrect");
      gegl_operation_meta_redirect (operation, "brightness", bc, "brightness");
      gegl_operation_meta_redirect (operation, "contrast", bc, "contrast");
      gegl_operation_meta_redirect (operation, "red", channelmixer, "rr-gain");
      gegl_operation_meta_redirect (operation, "green", channelmixer, "gg-gain");
      gegl_operation_meta_redirect (operation, "blue", channelmixer, "bb-gain");













  /* now save references to the gegl nodes so we can use them
   * later, when update_graph() is called
   */
  State *state = g_malloc0 (sizeof (State));
  state->input = input;
  state->sa = sa;
  state->unsharpmask = unsharpmask;
  state->nop = nop;
  state->softlight = softlight;
  state->antierase = antierase;
  state->burn = burn;
  state->lchcolor = lchcolor;
  state->addition = addition;
  state->grainmerge = grainmerge;
  state->multiply = multiply;
  state->hardlight = hardlight;
  state->screen = screen;
  state->linearlight = linearlight;
  state->overlay = overlay;
  state->shadowhighlights = shadowhighlights;
  state->hslcolor = hslcolor;
  state->saturation = saturation;
  state->hsvhue = hsvhue;
  state->crop = crop;
  state->color = color;
  state->bc = bc;
  state->lightchroma = lightchroma;
  state->channelmixer = channelmixer;
  state->output = output;

  o->user_data = state;
}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;
GeglOperationMetaClass *operation_meta_class = GEGL_OPERATION_META_CLASS (klass);
  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;
  operation_meta_class->update = update_graph;

  gegl_operation_class_set_keys (operation_class,
    "name",        "gegl:colorlightingfusion",
    "title",       _("Color Lighting Fusion"),
    "categories",  "Artistic",
    "reference-hash", "ha3fs1fv0nyagsyefsfsgac",
    "description", _("GEGL does all common color and lighting adjustments in on place. Non specified resets are at 0. You can set the blend mode opacity slider from 99% to 0% by clicking on the colorbox and sliding the A slider to 0.0. This is mandatory for getting the most out of the filter."
                     ""),
    NULL);
}

#endif
