#include "stdafx.h"

// {74C09DBD-7D06-40FE-B167-B1286740D26A}
static const GUID guid_cfg_ratio_cutoff = { 0x74c09dbd, 0x7d06, 0x40fe, { 0xb1, 0x67, 0xb1, 0x28, 0x67, 0x40, 0xd2, 0x6a } };

enum {
	default_cfg_ratio_cutoff = 100
};

static cfg_uint cfg_radio_cutoff(guid_cfg_ratio_cutoff, default_cfg_ratio_cutoff);

class HawkPreferences : public CDialogImpl<HawkPreferences>, public preferences_page_instance {

};
