/*See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 1;        /* gaps between windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Mononoki Nerd Font:size=12:alias=true:autohint=true"};
static const char dmenufont[]       = "Mononoki Nerd Font:size=10";


static const char col_1[]  = "#0A0E14"; /* background color of bar */
static const char col_2[]  = "#686868"; /* border color unfocused windows */
static const char col_3[]  = "#B3B1AD";
static const char col_4[]  = "#924441"; /* border color focused windows and tags */
/* bar opacity 
 * 0xff is no transparency.
 * 0xee adds wee bit of transparency.
 * 0xdd adds adds a bit more transparency.
 * Play with the value to get desired transparency.
 */
static const unsigned int baralpha    = 0xcc; 
static const unsigned int borderalpha = 0xff;
static const char *colors[][3]        = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_3, col_1, col_2 },
	[SchemeSel]  = { col_3, col_4, col_4 },
};
static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
//static const char *tags[] = { "", "", "", "", "", "", "", "", "" }; 
static const char *tags[] = { "dev", "www", "sys", "doc", "vbox", "chat", "mus", "vid", "gfx" };


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                        instance    title       tags mask      isfloating   monitor */
    { "Gimp",                       NULL,       NULL,       0,            1,           -1 },
    { "Chromium",                      NULL,       NULL,    1 << 1,       0,           -1 },
    { "discord",                    NULL,       NULL,       1 << 5,       0,           -1 },
    { "Code",                       NULL,       NULL,       1 << 0,       0,           -1 },
};


// constants
static const char *upvol[]   = { "/usr/bin/amixer", "set", "Master", "5%+", NULL };
static const char *downvol[] = { "/usr/bin/amixer", "set", "Master", "5%-", NULL };
static const char *mutevol[] = { "/usr/bin/amixer", "set", "Master", "toggle", NULL };

// Incremental VolumeControl
static const char *upincvol[]   = { "/usr/bin/amixer", "set", "Master", "1%+", NULL };
static const char *downincvol[] = { "/usr/bin/amixer", "set", "Master", "1%-", NULL };

static const char *cmus_play[] = { "cmus_control.sh", "play"};
static const char *cmus_next[] = { "cmus_control.sh", "next"};
static const char *cmus_prev[] = { "cmus_control.sh", "prev"};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=" ,  tile     },    /* first entry is default */
	{ "><>" ,  NULL     },    /* no layout function means floating behavior */
	{ "[M]" ,  monocle  },
    { "[@]" ,  spiral   },
    { "[\\]",  dwindle  },
	{ "HHH" ,  grid     },
    { NULL  ,  NULL     }
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* If you are using the standard dmenu program, use the following. */
static const char *dmenucmd[]    = { "dmenu_run", "-p", "Run: ", NULL };

/* the st terminal with tabbed */
static const char *termcmd[]     = { "st", NULL };
// Custom spawn commands for the browser, network and audio
static const char *browser[]     =   { "chromium",             NULL };
static const char *network[]     =   { "nm-connection-editor", NULL };
static const char *pulseaudio[]  =   { "pavucontrol",          NULL };
/* commands */
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,	                    XK_p,      spawn,          {.v = dmenucmd   } },
	{ MODKEY|ShiftMask,	            XK_Return, spawn,          {.v = termcmd    } },
    { MODKEY|ShiftMask,             XK_b,      spawn,          {.v = browser    } },
    { MODKEY|ShiftMask,             XK_n,      spawn,          {.v = network    } },
    { MODKEY|ShiftMask,             XK_a,      spawn,          {.v = pulseaudio } },
	{ MODKEY|ControlMask,           XK_t,      togglebar,      {0} },
    { MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
    { MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[5]} },
    { MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
    { MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,			            XK_b,	   shiftview,      {.i = -1 } },
	{ MODKEY,			            XK_n,	   shiftview,      {.i = +1 } },
	{ 0,   	                        XF86XK_AudioLowerVolume,    spawn,          { .v = downvol } },
	{ 0,       	                    XF86XK_AudioMute,           spawn,          { .v = mutevol } },
	{ 0,           	                XF86XK_AudioRaiseVolume,    spawn,          { .v = upvol   } },
    { 0,                            XF86XK_AudioPlay,           spawn,          { .v = cmus_play } }, 
    { 0,                            XF86XK_AudioNext,           spawn,          { .v = cmus_next } },
    { 0,                            XF86XK_AudioPrev,           spawn,          { .v = cmus_prev } },
    { MODKEY|ShiftMask,             XF86XK_AudioRaiseVolume,    spawn,          { .v = upincvol   } },
    { MODKEY|ShiftMask,             XF86XK_AudioLowerVolume,    spawn,          { .v = downincvol } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

