
class HawkPlaylistCallback : public playlist_callback_impl_base {
public:
	void on_playlist_created(t_size p_index, const char *p_name, t_size p_name_len);

private:
	bool check_duplicate(t_size p_index_1, t_size p_index_2);
	bool in_item_array(metadb_handle_ptr needle, metadb_handle_list &haystack);
};
