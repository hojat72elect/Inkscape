// SPDX-License-Identifier: GPL-2.0-or-later
/** @file
 *  Processing instruction node implementation
 *//*
 * Authors: see git history
 *
 * Copyright (C) 2018 Authors
 * Copyright 2004-2005 MenTaLguY <mental@rydia.net>
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */

#ifndef SEEN_INKSCAPE_XML_PI_NODE_H
#define SEEN_INKSCAPE_XML_PI_NODE_H

#include "xml/simple-node.h"

namespace Inkscape {

namespace XML {

/**
 * @brief Processing instruction node, e.g. &lt;?xml version="1.0" encoding="utf-8" standalone="no"?&gt;
 */
struct PINode : public SimpleNode {
    PINode(GQuark target, Util::ptr_shared content, Document *doc)
    : SimpleNode(target, doc)
    {
        setContent(content);
    }
    PINode(PINode const &other, Document *doc)
    : SimpleNode(other, doc) {}

    Inkscape::XML::NodeType type() const override { return Inkscape::XML::NodeType::PI_NODE; }

protected:
    SimpleNode *_duplicate(Document* doc) const override { return new PINode(*this, doc); }
};

}

}

#endif
/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :
