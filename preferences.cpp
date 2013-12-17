#include "stdafx.h"
#include "preferences.h"

enum {
	default_cfg_ratio_cutoff = 100,
	default_cfg_max_playlists = 2
};

// {74C09DBD-7D06-40FE-B167-B1286740D26A}
static const GUID guid_cfg_ratio_cutoff = { 0x74c09dbd, 0x7d06, 0x40fe, { 0xb1, 0x67, 0xb1, 0x28, 0x67, 0x40, 0xd2, 0x6a } };
cfg_uint cfg_ratio_cutoff(guid_cfg_ratio_cutoff, default_cfg_ratio_cutoff);

// {F9B4F7C1-B6EE-4E59-9087-905902655050}
static const GUID guid_cfg_max_playlists = { 0xf9b4f7c1, 0xb6ee, 0x4e59, { 0x90, 0x87, 0x90, 0x59, 0x2, 0x65, 0x50, 0x50 } };
cfg_uint cfg_max_playlists(guid_cfg_max_playlists, default_cfg_max_playlists);


t_uint32 HawkPreferences::get_state() {
	t_uint32 state = preferences_state::resettable;
	if (has_changed()) state |= preferences_state::changed;
	return state;
}

void HawkPreferences::apply() {
	cfg_ratio_cutoff = GetDlgItemInt(IDC_RATIO_CUTOFF, NULL, FALSE);
	cfg_max_playlists = GetDlgItemInt(IDC_MAX_PLAYLISTS, NULL, FALSE);

	// Limit cutoff to 0 - 100
	cfg_ratio_cutoff = min(100, max(0, cfg_ratio_cutoff));
	SetDlgItemInt(IDC_RATIO_CUTOFF, cfg_ratio_cutoff, FALSE);

	// Limit max playlists to > 2
	cfg_max_playlists = max(2, cfg_max_playlists);
	SetDlgItemInt(IDC_MAX_PLAYLISTS, cfg_max_playlists, FALSE);

	on_changed();
}

void HawkPreferences::reset() {
	SetDlgItemInt(IDC_RATIO_CUTOFF, default_cfg_ratio_cutoff, FALSE);
	SetDlgItemInt(IDC_MAX_PLAYLISTS, default_cfg_max_playlists, FALSE);
}

BOOL HawkPreferences::on_dialog_init(CWindow, LPARAM) {
	SetDlgItemInt(IDC_RATIO_CUTOFF, cfg_ratio_cutoff, FALSE);
	SetDlgItemInt(IDC_MAX_PLAYLISTS, cfg_max_playlists, FALSE);
	return FALSE;
}

void HawkPreferences::on_edit_change(UINT, int, CWindow) {
	on_changed();
}

bool HawkPreferences::has_changed() {
	return GetDlgItemInt(IDC_RATIO_CUTOFF, NULL, FALSE) != cfg_ratio_cutoff
		|| GetDlgItemInt(IDC_MAX_PLAYLISTS,NULL, FALSE) != cfg_max_playlists
		;
}

void HawkPreferences::on_changed() {
	m_callback->on_state_changed();
}
