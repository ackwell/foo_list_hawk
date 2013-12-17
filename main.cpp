#include "stdafx.h"

// Set up foobar shit
DECLARE_COMPONENT_VERSION("Playlist Hawk", "1.2.0", "Watches playlists to prevent duplicates.");
VALIDATE_COMPONENT_FILENAME("foo_list_hawk.dll");

// An initquit to handle setting everything else up
class HawkInitQuit : public initquit {
public:
	HawkPlaylistCallback* playlist_callback;

	// Initiate the callback
	void on_init() {
		playlist_callback = new HawkPlaylistCallback();
	}

	//  Application is closing, chuck out the callback to clear space
	void on_quit() {
		delete playlist_callback;
	}
};

// Register the initquit
static initquit_factory_t<HawkInitQuit> g_hawkinitquit_factory;
