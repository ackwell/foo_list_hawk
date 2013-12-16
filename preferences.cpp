#include "stdafx.h"
#include "preferences.h"

// {74C09DBD-7D06-40FE-B167-B1286740D26A}
static const GUID guid_cfg_ratio_cutoff = { 0x74c09dbd, 0x7d06, 0x40fe, { 0xb1, 0x67, 0xb1, 0x28, 0x67, 0x40, 0xd2, 0x6a } };

enum {
	default_cfg_ratio_cutoff = 100
};

cfg_uint cfg_ratio_cutoff(guid_cfg_ratio_cutoff, default_cfg_ratio_cutoff);

t_uint32 HawkPreferences::get_state() {
	t_uint32 state = preferences_state::resettable;
	if (has_changed()) state |= preferences_state::changed;
	return state;
}

void HawkPreferences::apply() {
	cfg_ratio_cutoff = GetDlgItemInt(IDC_RATIO_CUTOFF, NULL, FALSE);
	// Limit 0 - 100
	cfg_ratio_cutoff = min(100, max(0, cfg_ratio_cutoff));
	SetDlgItemInt(IDC_RATIO_CUTOFF, cfg_ratio_cutoff, FALSE);
	on_changed();
}

void HawkPreferences::reset() {
	SetDlgItemInt(IDC_RATIO_CUTOFF, default_cfg_ratio_cutoff, FALSE);
}

BOOL HawkPreferences::on_dialog_init(CWindow, LPARAM) {
	SetDlgItemInt(IDC_RATIO_CUTOFF, cfg_ratio_cutoff, FALSE);
	return FALSE;
}

void HawkPreferences::on_edit_change(UINT, int, CWindow) {
	on_changed();
}

bool HawkPreferences::has_changed() {
	return GetDlgItemInt(IDC_RATIO_CUTOFF, NULL, FALSE) != cfg_ratio_cutoff;
}

void HawkPreferences::on_changed() {
	m_callback->on_state_changed();
}
