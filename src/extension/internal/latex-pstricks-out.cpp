// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Authors:
 *   Michael Forbes <miforbes@mbhs.edu>
 *   Jon A. Cruz <jon@joncruz.org>
 *   Abhishek Sharma
 *
 * Copyright (C) 2004 Authors
 *
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */

#include "latex-pstricks-out.h"
#include <print.h>
#include "extension/system.h"
#include "extension/print.h"
#include "extension/db.h"
#include "display/drawing.h"
#include "object/sp-root.h"


#include "document.h"


namespace Inkscape {
namespace Extension {
namespace Internal {

LatexOutput::LatexOutput () // The null constructor
{
    return;
}

LatexOutput::~LatexOutput () //The destructor
{
    return;
}

bool LatexOutput::check(Inkscape::Extension::Extension * /*module*/)
{
    bool result = Inkscape::Extension::db.get("org.inkscape.print.latex") != nullptr;
    return result;
}


void LatexOutput::save(Inkscape::Extension::Output * /*mod2*/, SPDocument *doc, gchar const *filename)
{
    SPPrintContext context;
    doc->ensureUpToDate();

    Inkscape::Extension::Print *mod = Inkscape::Extension::get_print(SP_MODULE_KEY_PRINT_LATEX);
    const gchar * oldconst = mod->get_param_string("destination");
    gchar * oldoutput = g_strdup(oldconst);
    mod->set_param_string("destination", filename);

    // Start
    context.module = mod;
    // fixme: This has to go into module constructor somehow
    mod->base = doc->getRoot();
    Inkscape::Drawing drawing;
    mod->dkey = SPItem::display_key_new(1);
    mod->root = (mod->base)->invoke_show(drawing, mod->dkey, SP_ITEM_SHOW_DISPLAY);
    drawing.setRoot(mod->root);
    // Print document
    mod->begin(doc);
    (mod->base)->invoke_print(&context);
    mod->finish();
    // Release things
    (mod->base)->invoke_hide(mod->dkey);
    mod->base = nullptr;
    mod->root = nullptr; // should have been deleted by invoke_hide
    // end

    mod->set_param_string("destination", oldoutput);
    g_free(oldoutput);
}

#include "clear-n_.h"

/**
    \brief   A function allocate a copy of this function.

    This is the definition of postscript out.  This function just
    calls the extension system with the memory allocated XML that
    describes the data.
*/
void
LatexOutput::init ()
{
    // clang-format off
    Inkscape::Extension::build_from_mem(
        "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
            "<name>" N_("LaTeX Output") "</name>\n"
            "<id>org.inkscape.output.latex</id>\n"
            "<output>\n"
                "<extension>.tex</extension>\n"
                "<mimetype>text/x-tex</mimetype>\n"
                "<filetypename>" N_("LaTeX With PSTricks macros (*.tex)") "</filetypename>\n"
                "<filetypetooltip>" N_("LaTeX PSTricks File") "</filetypetooltip>\n"
            "</output>\n"
        "</inkscape-extension>", std::make_unique<LatexOutput>());
    // clang-format on

    return;
}

} } }  /* namespace Inkscape, Extension, Implementation */

/*
  Local Variables:
  mode:cpp
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :
