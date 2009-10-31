#include "Globals.h"
#include "GTK++.h"

UINT GTKKey::GetDefaultModifiersMask()
{
	return gtk_accelerator_get_default_mod_mask();
}

UINT GTKKey::ToUpper(UINT Key)
{
	return gdk_keyval_to_upper(Key);
}