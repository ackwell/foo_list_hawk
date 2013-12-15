#include "stdafx.h"

// Called when a new playlist is created
void HawkPlaylistCallback::on_playlist_created(t_size p_index, const char *p_name, t_size p_name_len) {
	in_main_thread([=](){
		// Get a reference to the playlist manager
		static_api_ptr_t<playlist_manager> pm;

		// Loop over the current playlists
		for (t_size i = 0; i < pm->get_playlist_count(); i++) {
			bool is_duplicate = check_duplicate(i, p_index);

			if (is_duplicate) {
				popup_message::g_show("Duplicate found", "\/");
			}
		}
	});
}

bool HawkPlaylistCallback::check_duplicate(t_size p_index_1, t_size p_index_2) {
	if (p_index_1 == p_index_2) { return false; }

	static_api_ptr_t<playlist_manager> pm;

	pfc::string8 blah;
	pm->playlist_get_name(p_index_1, blah);

	popup_message::g_show(blah, "lol");

	return false;
}
