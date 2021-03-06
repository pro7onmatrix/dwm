/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
  "FiraCode Nerd Font:size=12:antialias=true:autohint=true",
};
static const char dmenufont[]       = "FiraCode Nerd Font:size=12:antialias=true:autohint=true";
static const char col_gray1[]       = "#2e3440";
static const char col_gray2[]       = "#434c5e";
static const char col_gray3[]       = "#d8dee9";
static const char col_gray4[]       = "#e5e9f0";
static const char col_cyan[]        = "#8fbcbb";
static const char col_orange[]      = "#d08770";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#bf616a";
static const char col_yellow[]      = "#ebcb8b";
static const char col_white[]       = "#eceff4";

static const char *colors[][3]      = {
/*                   fg         bg          border   */
  [SchemeNorm]  =  { col_gray3, col_gray1,  col_gray1 },
  [SchemeInv]   =  { col_gray1, col_gray3,  col_gray1 },
  [SchemeSel]   =  { col_gray1, col_cyan,   col_cyan  },
  [SchemeOcc]   =  { col_gray3, col_gray2,  col_gray1 },
  [SchemeUrgent]=  { col_white, col_red,    col_red   },
  [SchemeWarn]  =  { col_black, col_yellow, col_red   },
};

/* tagging */
static const char *tags[] = { " ₁", " ₂", " ₃", " ₄", " ₅", " ₆", " ₇", " ₈", " ₉" };

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor      scratch key */
  { "Gimp",     NULL,       NULL,       0,            1,           -1,          0 },
  { "Avogadro", NULL,       NULL,       0,            1,           -1,          0 },
  { "Firefox",  NULL,       NULL,       1 << 2,       0,           -1,          0 },
  { "Thunderbird", NULL,    NULL,       1 << 3,       0,           -1,          0 },
  { "Slack",    NULL,       NULL,       1 << 6,       0,           -1,          0 },
  { "discord",  NULL,       NULL,       1 << 6,       0,           -1,          0 },
  { "zoom",     NULL,       NULL,       1 << 7,       1,           -1,          0 },
  { NULL,       NULL,       "scratchpad", 0,          1,           -1,          's' },
};

/* layout(s) */
static const float mfact     = 0.5;  /* fa1tor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "﬿",      tile },    /* first entry is default */
  { "",      NULL },    /* no layout function means floating behavior */
  { "",      monocle },
  { "恵",     centeredmaster },
  { "﵁",      centeredfloatingmaster },
};

static const char *monoclelabels[] = { "", "", "", "", "", "", "", "", "", "" };

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]    = { "st", NULL };
static const char *logoutcmd[]  = { "dmenu-poweroff", NULL };
static const char *lockcmd[]    = { "slock", NULL };

static const char *screenshotcmd[] = { "screenshot", NULL };

/* Some playback options */
static const char *prevtrack[]  = { "playerctl", "previous", NULL };
static const char *nexttrack[]  = { "playerctl", "next", NULL };
static const char *toggleplayback[] = { "playerctl", "play-pause", NULL };
static const char *stopplayback[] = { "playerctl", "stop", NULL };

static const char *bitwarden[] = { "bitwarden-dmenu", NULL };

static const char *brightnessup[]   = { "xbacklight", "-inc", "5", NULL };
static const char *brightnessdown[] = { "xbacklight", "-dec", "5", NULL };

/* First arg only serves to match against key in rules */
static const char *scratchpadcmd[] = { "s", "st", "-t", "scratchpad", NULL };

#include "movestack.c"
static Key keys[] = {
  /* modifier                     key         function        argument */
  { MODKEY,                       XK_p,       spawn,          {.v = dmenucmd} },
  { MODKEY,                       XK_Return,  spawn,          {.v = termcmd} },
  { MODKEY,                       XK_grave,   togglescratch,  {.v = scratchpadcmd} },
  { MODKEY,                       XK_b,       togglebar,      {0} },
  { MODKEY,                       XK_j,       focusstack,     {.i = +1} },
  { MODKEY,                       XK_k,       focusstack,     {.i = -1} },
  { MODKEY|ControlMask,           XK_space,   focusmaster,    {0} },
  { MODKEY,                       XK_i,       incnmaster,     {.i = +1} },
  { MODKEY,                       XK_d,       incnmaster,     {.i = -1} },
  { MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
  { MODKEY|ShiftMask,             XK_j,       movestack,      {.i = +1} },
  { MODKEY|ShiftMask,             XK_k,       movestack,      {.i = -1} },
  { MODKEY|ShiftMask,             XK_Return,  zoom,           {0} },
  { MODKEY,                       XK_Tab,     view,           {0} },
  { MODKEY|ShiftMask,             XK_c,       killclient,     {0} },
  { MODKEY,                       XK_t,       setlayout,      {.v = &layouts[0]} },
  { MODKEY,                       XK_f,       setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_m,       setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_u,       setlayout,      {.v = &layouts[3]} },
  { MODKEY,                       XK_o,       setlayout,      {.v = &layouts[4]} },
  { MODKEY,                       XK_F11,     fullscreen,     {0} },
  { MODKEY,                       XK_space,   setlayout,      {0} },
  { MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },
  { MODKEY,                       XK_0,       view,           {.ui = ~0} },
  { MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0} },
  { MODKEY,                       XK_comma,   focusmon,       {.i = -1} },
  { MODKEY,                       XK_period,  focusmon,       {.i = +1} },
  { MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1} },
  { MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1} },
  { MODKEY,                       XK_minus,   setgaps,        {.i = -1} },
  { MODKEY,                       XK_plus,    setgaps,        {.i = +1} },
  TAGKEYS(                        XK_1,                       0)
  TAGKEYS(                        XK_2,                       1)
  TAGKEYS(                        XK_3,                       2)
  TAGKEYS(                        XK_4,                       3)
  TAGKEYS(                        XK_5,                       4)
  TAGKEYS(                        XK_6,                       5)
  TAGKEYS(                        XK_7,                       6)
  TAGKEYS(                        XK_8,                       7)
  TAGKEYS(                        XK_9,                       8)
  { MODKEY|ShiftMask,             XK_q,       quit,           {0} },
  { MODKEY|ShiftMask,             XK_s,       spawn,          {.v = logoutcmd} },
  { MODKEY|ShiftMask,             XK_l,       spawn,          {.v = lockcmd} },

  { MODKEY|ShiftMask,             XK_f,       spawn,          SHCMD("$BROWSER") },
  { MODKEY|ShiftMask,             XK_p,       spawn,          {.v = bitwarden} },

  // audio controls
  { 0, XF86XK_AudioMute,                      spawn,          SHCMD("pamixer -t && pkill -RTMIN+12 dwmblocks") },
  { 0, XF86XK_AudioRaiseVolume,               spawn,          SHCMD("pamixer -i 5 && pkill -RTMIN+12 dwmblocks") },
  { 0, XF86XK_AudioLowerVolume,               spawn,          SHCMD("pamixer -d 5 && pkill -RTMIN+12 dwmblocks") },
  { 0, XF86XK_AudioPrev,                      spawn,          {.v = prevtrack} },
  { 0, XF86XK_AudioNext,                      spawn,          {.v = nexttrack} },
  { 0, XF86XK_AudioPlay,                      spawn,          {.v = toggleplayback} },
  { 0, XF86XK_AudioStop,                      spawn,          {.v = stopplayback} },

  // brightness controls
  { 0, XF86XK_MonBrightnessUp,                spawn,          {.v = brightnessup} },
  { 0, XF86XK_MonBrightnessDown,              spawn,          {.v = brightnessdown} },

  // screenshots
  { 0,                            XK_Print,   spawn,          {.v = screenshotcmd} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
  { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
  { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

