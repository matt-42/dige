// Copyright (C) 2010 Matthieu Garrigues
//
// This file is part of dige.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
/*!
**\file   keycode.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sun Nov  7 16:02:08 2010
**
**\brief  keycode header.
**
**
*/

#ifndef DIGE_KEYCODE_H_
# define DIGE_KEYCODE_H_

namespace dg
{
  enum keycode
  {
    key_escape,
    key_tab,
    key_backtab,
    key_backspace,
    key_return,
    key_enter,
    key_insert,
    key_delete,
    key_pause,
    key_print,
    key_sysreq,
    key_clear,
    key_home,
    key_end,
    key_left,
    key_up,
    key_right,
    key_down,
    key_pageup,
    key_pagedown,
    key_shift,
    key_control,
    key_meta,
    key_alt,
    key_altgr,
    key_capslock,
    key_numlock,
    key_scrolllock,
    key_f1,
    key_f2,
    key_f3,
    key_f4,
    key_f5,
    key_f6,
    key_f7,
    key_f8,
    key_f9,
    key_f10,
    key_f11,
    key_f12,
    key_f13,
    key_f14,
    key_f15,
    key_f16,
    key_f17,
    key_f18,
    key_f19,
    key_f20,
    key_f21,
    key_f22,
    key_f23,
    key_f24,
    key_f25,
    key_f26,
    key_f27,
    key_f28,
    key_f29,
    key_f30,
    key_f31,
    key_f32,
    key_f33,
    key_f34,
    key_f35,
    key_super_l,
    key_super_r,
    key_menu,
    key_hyper_l,
    key_hyper_r,
    key_help,
    key_direction_l,
    key_direction_r,
    key_space,
    key_any,
    key_exclam,
    key_quotedbl,
    key_numbersign,
    key_dollar,
    key_percent,
    key_ampersand,
    key_apostrophe,
    key_parenleft,
    key_parenright,
    key_asterisk,
    key_plus,
    key_comma,
    key_minus,
    key_period,
    key_slash,
    key_0,
    key_1,
    key_2,
    key_3,
    key_4,
    key_5,
    key_6,
    key_7,
    key_8,
    key_9,
    key_colon,
    key_semicolon,
    key_less,
    key_equal,
    key_greater,
    key_question,
    key_at,
    key_a,
    key_b,
    key_c,
    key_d,
    key_e,
    key_f,
    key_g,
    key_h,
    key_i,
    key_j,
    key_k,
    key_l,
    key_m,
    key_n,
    key_o,
    key_p,
    key_q,
    key_r,
    key_s,
    key_t,
    key_u,
    key_v,
    key_w,
    key_x,
    key_y,
    key_z,
    key_bracketleft,
    key_backslash,
    key_bracketright,
    key_asciicircum,
    key_underscore,
    key_quoteleft,
    key_braceleft,
    key_bar,
    key_braceright,
    key_asciitilde,
    key_nobreakspace,
    key_exclamdown,
    key_cent,
    key_sterling,
    key_currency,
    key_yen,
    key_brokenbar,
    key_section,
    key_diaeresis,
    key_copyright,
    key_ordfeminine,
    key_guillemotleft,
    key_notsign,
    key_hyphen,
    key_registered,
    key_macron,
    key_degree,
    key_plusminus,
    key_twosuperior,
    key_threesuperior,
    key_acute,
    key_mu,
    key_paragraph,
    key_periodcentered,
    key_cedilla,
    key_onesuperior,
    key_masculine,
    key_guillemotright,
    key_onequarter,
    key_onehalf,
    key_threequarters,
    key_questiondown,
    key_agrave,
    key_aacute,
    key_acircumflex,
    key_atilde,
    key_adiaeresis,
    key_aring,
    key_ae,
    key_ccedilla,
    key_egrave,
    key_eacute,
    key_ecircumflex,
    key_ediaeresis,
    key_igrave,
    key_iacute,
    key_icircumflex,
    key_idiaeresis,
    key_eth,
    key_ntilde,
    key_ograve,
    key_oacute,
    key_ocircumflex,
    key_otilde,
    key_odiaeresis,
    key_multiply,
    key_ooblique,
    key_ugrave,
    key_uacute,
    key_ucircumflex,
    key_udiaeresis,
    key_yacute,
    key_thorn,
    key_ssharp,
    key_division,
    key_ydiaeresis,
    key_multi_key,
    key_codeinput,
    key_singlecandidate,
    key_multiplecandidate,
    key_previouscandidate,
    key_mode_switch,
    key_kanji,
    key_muhenkan,
    key_henkan,
    key_romaji,
    key_hiragana,
    key_katakana,
    key_hiragana_katakana,
    key_zenkaku,
    key_hankaku,
    key_zenkaku_hankaku,
    key_touroku,
    key_massyo,
    key_kana_lock,
    key_kana_shift,
    key_eisu_shift,
    key_eisu_toggle,
    key_hangul,
    key_hangul_start,
    key_hangul_end,
    key_hangul_hanja,
    key_hangul_jamo,
    key_hangul_romaja,
    key_hangul_jeonja,
    key_hangul_banja,
    key_hangul_prehanja,
    key_hangul_posthanja,
    key_hangul_special,
    key_dead_grave,
    key_dead_acute,
    key_dead_circumflex,
    key_dead_tilde,
    key_dead_macron,
    key_dead_breve,
    key_dead_abovedot,
    key_dead_diaeresis,
    key_dead_abovering,
    key_dead_doubleacute,
    key_dead_caron,
    key_dead_cedilla,
    key_dead_ogonek,
    key_dead_iota,
    key_dead_voiced_sound,
    key_dead_semivoiced_sound,
    key_dead_belowdot,
    key_dead_hook,
    key_dead_horn,
    key_back,
    key_forward,
    key_stop,
    key_refresh,
    key_volumedown,
    key_volumemute,
    key_volumeup,
    key_bassboost,
    key_bassup,
    key_bassdown,
    key_trebleup,
    key_trebledown,
    key_mediaplay,
    key_mediastop,
    key_mediaprevious,
    key_medianext,
    key_mediarecord,
    key_mediapause,
    key_mediatoggleplaypause,
    key_homepage,
    key_favorites,
    key_search,
    key_standby,
    key_openurl,
    key_launchmail,
    key_launchmedia,
    key_launch0,
    key_launch1,
    key_launch2,
    key_launch3,
    key_launch4,
    key_launch5,
    key_launch6,
    key_launch7,
    key_launch8,
    key_launch9,
    key_launcha,
    key_launchb,
    key_launchc,
    key_launchd,
    key_launche,
    key_launchf,
    key_launchg,
    key_launchh,
    key_monbrightnessup,
    key_monbrightnessdown,
    key_keyboardlightonoff,
    key_keyboardbrightnessup,
    key_keyboardbrightnessdown,
    key_poweroff,
    key_wakeup,
    key_eject,
    key_screensaver,
    key_www,
    key_memo,
    key_lightbulb,
    key_shop,
    key_history,
    key_addfavorite,
    key_hotlinks,
    key_brightnessadjust,
    key_finance,
    key_community,
    key_audiorewind,
    key_backforward,
    key_applicationleft,
    key_applicationright,
    key_book,
    key_cd,
    key_calculator,
    key_todolist,
    key_cleargrab,
    key_close,
    key_copy,
    key_cut,
    key_display,
    key_dos,
    key_documents,
    key_excel,
    key_explorer,
    key_game,
    key_go,
    key_itouch,
    key_logoff,
    key_market,
    key_meeting,
    key_menukb,
    key_menupb,
    key_mysites,
    key_news,
    key_officehome,
    key_option,
    key_paste,
    key_phone,
    key_calendar,
    key_reply,
    key_reload,
    key_rotatewindows,
    key_rotationpb,
    key_rotationkb,
    key_save,
    key_send,
    key_spell,
    key_splitscreen,
    key_support,
    key_taskpane,
    key_terminal,
    key_tools,
    key_travel,
    key_video,
    key_word,
    key_xfer,
    key_zoomin,
    key_zoomout,
    key_away,
    key_messenger,
    key_webcam,
    key_mailforward,
    key_pictures,
    key_music,
    key_battery,
    key_bluetooth,
    key_wlan,
    key_uwb,
    key_audioforward,
    key_audiorepeat,
    key_audiorandomplay,
    key_subtitle,
    key_audiocycletrack,
    key_time,
    key_hibernate,
    key_view,
    key_topmenu,
    key_powerdown,
    key_suspend,
    key_contrastadjust,
    key_medialast,
    key_unknown,
    key_call,
    key_camera,
    key_camerafocus,
    key_context1,
    key_context2,
    key_context3,
    key_context4,
    key_flip,
    key_hangup,
    key_no,
    key_select,
    key_yes,
    key_togglecallhangup,
    key_voicedial,
    key_lastnumberredial,
    key_execute,
    key_printer,
    key_play,
    key_sleep,
    key_zoom,
    key_cancel
  };

  keycode qt_key_to_dige_key(int);

} // end of namespace dg.

#endif
