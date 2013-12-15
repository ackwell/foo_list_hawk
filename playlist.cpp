#include "stdafx.h"

// Called when a new playlist is created
void HawkPlaylistCallback::on_playlist_created(t_size p_index, const char *p_name, t_size p_name_len) {
	in_main_thread([=](){
		static_api_ptr_t<playlist_manager> pm;

		// Loop over the current playlists, check if dupe
		for (t_size i = 0; i < pm->get_playlist_count(); i++) {
			bool is_duplicate = check_duplicate(i, p_index);

			if (is_duplicate) {
				popup_message::g_show("Duplicate found", "");
			}
		}
	});
}

bool HawkPlaylistCallback::check_duplicate(t_size p_index_1, t_size p_index_2) {
	// Same entry, no further processing required.
	if (p_index_1 == p_index_2) { return false; }

	static_api_ptr_t<playlist_manager> pm;
	
	// Get the two lists, and sort them both in the same way (so comparison is bettererer)
	metadb_handle_list items_1, items_2;
	pm->playlist_get_all_items(p_index_1, items_1);
	pm->playlist_get_all_items(p_index_2, items_2);
	items_1.sort();
	items_2.sort();

	// Loop list 1
	items_1.for_each([=](metadb_handle_ptr item){
		popup_message::g_show(item->get_path(), "stuff");
	});

	return false;
}
