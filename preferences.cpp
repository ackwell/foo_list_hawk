#include "stdafx.h"
#include "resource.h"

// {74C09DBD-7D06-40FE-B167-B1286740D26A}
static const GUID guid_cfg_ratio_cutoff = { 0x74c09dbd, 0x7d06, 0x40fe, { 0xb1, 0x67, 0xb1, 0x28, 0x67, 0x40, 0xd2, 0x6a } };

enum {
	default_cfg_ratio_cutoff = 100
};

static cfg_uint cfg_radio_cutoff(guid_cfg_ratio_cutoff, default_cfg_ratio_cutoff);

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
	END_MSG_MAP()

private:
	const preferences_page_callback::ptr m_callback;
};

t_uint32 HawkPreferences::get_state() {
	return 0;
}

void HawkPreferences::apply() {
}

void HawkPreferences::reset() {
}

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