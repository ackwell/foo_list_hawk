#include "stdafx.h"

// Called when a new playlist is created
void HawkPlaylistCallback::on_playlist_created(t_size p_index, const char *p_name, t_size p_name_len) {
	in_main_thread([=](){
		static_api_ptr_t<playlist_manager> pm;
		t_size new_index = p_index;

		unsigned int playlist_count = pm->get_playlist_count();
		int num_over_limit = playlist_count - cfg_max_playlists;

		// Loop over the current playlists, get dupes to delete
		pfc::bit_array_var_impl to_remove;
		for (t_size old_index = 0; old_index < playlist_count; old_index++) {
			bool is_playing = old_index == pm->get_playing_playlist();
			bool is_duplicate = check_duplicate(old_index, new_index);

			// If the playlist isn't playing, and we are over the limit, chukkit.
			if (!is_playing && num_over_limit > 0) {
				to_remove.set(old_index, true);
				num_over_limit--;
				continue;
			}

			if (is_duplicate) {
				// Old playlist is playing, not safe to toss.
				// Instead, toss the new one, and switch active to the old.
				if (is_playing) {
					to_remove.set(new_index, true);
					new_index = old_index;
					pm->set_active_playlist(new_index);
				}

				// Otherwise, safe to toss old one
				else {
					to_remove.set(old_index, true);
				}
			}
		}

		// Remove the ones we have marked for deletion
		pm->remove_playlists(to_remove);
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
	int length = items_1.get_size();
	for (int i = 0; i < length; i++) {
		if (in_item_array(items_1[i], items_2)) { matches++; }
	}

	// Are we classifying this as a dupe?
	double ratio = matches / (items_1.get_size() + items_2.get_size() - matches);
	double target = cfg_ratio_cutoff / 100.f;
	if (ratio >= target) { return true; }
	return false;
}

bool HawkPlaylistCallback::in_item_array(metadb_handle_ptr needle, metadb_handle_list haystack) {
	int length = haystack.get_size();
	for (int i = 0; i < length; i++) {
		if (haystack[i] == needle) {
			return true;
		}
	}
	return false;
}