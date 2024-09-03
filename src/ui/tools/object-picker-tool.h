// SPDX-License-Identifier: GPL-2.0-or-later
#ifndef SEEN_OBJECT_PICKER_TOOL_H
#define SEEN_OBJECT_PICKER_TOOL_H

#include <sigc++/signal.h>
#include "display/control/canvas-item-ptr.h"
#include "display/control/canvas-item-rect.h"
#include "display/control/canvas-item-text.h"
#include "helper/auto-connection.h"
#include "object/sp-object.h"
#include "ui/tools/tool-base.h"

namespace Inkscape::UI::Tools {

class ObjectPickerTool : public ToolBase {
public:
    ObjectPickerTool(SPDesktop* desktop);
    ~ObjectPickerTool() override;

    sigc::signal<bool (SPObject*)> signal_object_picked;

private:
    bool root_handler(const CanvasEvent& event) override;
    void show_text(const Geom::Point& cursor, const char* text);
    CanvasItemPtr<CanvasItemText> _label;
    CanvasItemPtr<CanvasItemRect> _frame;
    auto_connection _zoom;
};

} // namespaces

#endif
