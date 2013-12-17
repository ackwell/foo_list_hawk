#include "resource.h"

class HawkPreferences : public CDialogImpl<HawkPreferences>, public preferences_page_instance {
public:
	// Constructor
	HawkPreferences(preferences_page_callback::ptr callback) : m_callback(callback) {}

	// Resource ID
	enum {IDD = IDD_HAWKPREFERENCES};

	// Required methods
	t_uint32 get_state();
	void apply();
	void reset();

	// WTL message map
	BEGIN_MSG_MAP(HawkPreferences)
		MSG_WM_INITDIALOG(on_dialog_init)
		COMMAND_HANDLER_EX(IDC_RATIO_CUTOFF, EN_CHANGE, on_edit_change)
		COMMAND_HANDLER_EX(IDC_MAX_PLAYLISTS, EN_CHANGE, on_edit_change)
	END_MSG_MAP()

private:
	// Handlers
	BOOL on_dialog_init(CWindow, LPARAM);
	void on_edit_change(UINT, int, CWindow);

	// Helpers
	bool has_changed();
	void on_changed();

	// Callback thingo
	const preferences_page_callback::ptr m_callback;
};


// Handle instanciation of the preferences page
class hawk_preferences_page : public preferences_page_impl<HawkPreferences> {
public:
	const char * get_name() { return "List Hawk"; }
	GUID get_guid() {
		// {F24A7143-AC9B-4394-AC01-38BD023EFC55}
		static const GUID guid = { 0xf24a7143, 0xac9b, 0x4394, { 0xac, 0x1, 0x38, 0xbd, 0x2, 0x3e, 0xfc, 0x55 } };
		return guid;
	}
	GUID get_parent_guid() { return guid_media_library; }
};
static preferences_page_factory_t<hawk_preferences_page> g_hawk_preferences_page_factory;