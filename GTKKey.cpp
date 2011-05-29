#include "Globals.h"
#include "GTK++.h"

uint32_t GTKKey::GetDefaultModifiersMask()
{
	return gtk_accelerator_get_default_mod_mask();
}

uint32_t GTKKey::ToUpper(uint32_t Key)
{
	return gdk_keyval_to_upper(Key);
}