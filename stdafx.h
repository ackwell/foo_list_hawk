
#pragma once

#include "../SDK/foobar2000.h"

#include "helpers.h"

// I'm including everything in here because a) I'm lazy and b) I'm lazy
class HawkPlaylistCallback : public playlist_callback_impl_base {
public:
	void on_playlist_created(t_size p_index, const char *p_name, t_size p_name_len);
};

