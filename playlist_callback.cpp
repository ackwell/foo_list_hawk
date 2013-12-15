#include "stdafx.h"

// Called when a new playlist is created
void HawkPlaylistCallback::on_playlist_created(t_size p_index, const char *p_name, t_size p_name_len) {
	in_main_thread([&](){
		// Get a reference to the playlist manager
		static_api_ptr_t<playlist_manager> pm;

		pm->playlist_rename(p_index, "nope", 4);
	});
}