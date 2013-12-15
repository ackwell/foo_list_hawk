#include "stdafx.h"

// Called when a new playlist is created
void HawkPlaylistCallback::on_playlist_created(t_size p_index, const char *p_name, t_size p_name_len) {
	// Get string8 copy for comparisons
	pfc::string8 new_name = p_name;

	in_main_thread([=](){
		// Get a reference to the playlist manager
		static_api_ptr_t<playlist_manager> pm;

		// Loop over the current playlists, get it's name
		for (t_size i = 0; i < pm->get_playlist_count(); i++) {
			pfc::string8 name;
			pm->playlist_get_name(i, name);
			
			if (name == new_name) {
				// Loop will include the one just created. If we hit it, ignore.
				if (i == p_index) { continue; }

				popup_message::g_show(name, "Playlist dupe:");
			}
		}
	});
}