#include "stdafx.h"

// Called when a new playlist is created
void HawkPlaylistCallback::on_playlist_created(t_size p_index, const char *p_name, t_size p_name_len) {
	in_main_thread([=](){
		static_api_ptr_t<playlist_manager> pm;

		// Loop over the current playlists, check if dupe
		for (t_size i = 0; i < pm->get_playlist_count(); i++) {
			bool is_duplicate = check_duplicate(i, p_index);

			if (is_duplicate) {
				// Duplicate, delete the old copy.
				pm->remove_playlist(i);
			}
		}
	});
}

bool HawkPlaylistCallback::check_duplicate(t_size p_index_1, t_size p_index_2) {
	// Same entry, no further processing required.
	if (p_index_1 == p_index_2) { return false; }

	static_api_ptr_t<playlist_manager> pm;
	
	// Get the two lists
	metadb_handle_list items_1, items_2;
	pm->playlist_get_all_items(p_index_1, items_1);
	pm->playlist_get_all_items(p_index_2, items_2);

	float matches = 0;
	items_1.for_each([&](metadb_handle_ptr item_1){
		bool dupe = in_item_array(item_1, items_2);
		if (dupe) { matches++; }
	});

	double ratio = matches / (items_1.get_size() + items_2.get_size() - matches);
	double target = cfg_ratio_cutoff / 100.f;
	if (ratio >= target) { return true; }
	return false;
}

bool HawkPlaylistCallback::in_item_array(metadb_handle_ptr needle, metadb_handle_list &haystack) {
	bool out = false;

	// I should probably do something a bit better than a linear search but fukkit I'm lazy.
	haystack.for_each([&](metadb_handle_ptr item){
		if (item == needle) {
			out = true;
			return;
		}
	});

	return out;
}