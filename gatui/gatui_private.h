#ifndef GATUI_PRIVATE_H
#define GATUI_PRIVATE_H

#include <glib-object.h>

#include "atomtree.h"
#include "atui.h"
#include "gatui.h"

void
atui_leaves_to_gliststore( // for GATUILeaves generation
		GListStore* list,
		atui_leaf* leaves,
		uint16_t num_leaves
		);

#endif