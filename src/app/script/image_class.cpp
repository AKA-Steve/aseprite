// Aseprite
// Copyright (C) 2015-2017  David Capello
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "doc/image.h"
#include "script/engine.h"

namespace app {

namespace {

const char* kTag = "Image";

void Image_new(script::ContextHandle handle)
{
  script::Context ctx(handle);
  ctx.pushNull();          // TODO
}

void Image_putPixel(script::ContextHandle handle)
{
  script::Context ctx(handle);
  auto image = (doc::Image*)ctx.toUserData(0, kTag);
  int x = ctx.requireInt(1);
  int y = ctx.requireInt(2);
  doc::color_t color = ctx.requireUInt(3);

  if (image) {
    image->putPixel(x, y, color);
  }

  ctx.pushUndefined();
}

void Image_getPixel(script::ContextHandle handle)
{
  script::Context ctx(handle);
  auto image = (doc::Image*)ctx.toUserData(0, kTag);
  int x = ctx.requireInt(1);
  int y = ctx.requireInt(2);

  if (image) {
    doc::color_t color = image->getPixel(x, y);
    ctx.pushUInt(color);
  }
  else
    ctx.pushUndefined();
}

void Image_get_width(script::ContextHandle handle)
{
  script::Context ctx(handle);
  auto image = (doc::Image*)ctx.toUserData(0, kTag);
  if (image)
    ctx.pushInt(image->width());
  else
    ctx.pushUndefined();
}

void Image_get_height(script::ContextHandle handle)
{
  script::Context ctx(handle);
  auto image = (doc::Image*)ctx.toUserData(0, kTag);
  if (image)
    ctx.pushInt(image->height());
  else
    ctx.pushUndefined();
}

const script::FunctionEntry Image_methods[] = {
  { "getPixel", Image_getPixel, 2 },
  { "putPixel", Image_putPixel, 3 },
  { nullptr, nullptr, 0 }
};

const script::PropertyEntry Image_props[] = {
  { "width", Image_get_width, nullptr },
  { "height", Image_get_height, nullptr },
  { nullptr, nullptr, 0 }
};

} // anonymous namespace

void register_image_class(script::index_t idx, script::Context& ctx)
{
  ctx.registerClass(idx, kTag,
                    Image_new, 0,
                    Image_methods, Image_props);
}

void push_image(script::Context& ctx, doc::Image* image)
{
  ctx.newObject(kTag, image, nullptr);
}

} // namespace app
