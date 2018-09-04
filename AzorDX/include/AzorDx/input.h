#ifndef AZORDX_INPUT_H
#define AZORDX_INPUT_H

#define AZOR_ESCAPE 0x01
#define AZOR_1 0x02
#define AZOR_2 0x03
#define AZOR_3 0x04
#define AZOR_4 0x05
#define AZOR_5 0x06
#define AZOR_6 0x07
#define AZOR_7 0x08
#define AZOR_8 0x09
#define AZOR_9 0x0A
#define AZOR_0 0x0B
#define AZOR_MINUS 0x0C /* - on main keyboards */
#define AZOR_EQUALS 0x0D
#define AZOR_BACK 0x0E /* backspace */
#define AZOR_TAB 0x0F
#define AZOR_Q 0x10
#define AZOR_W 0x11
#define AZOR_E 0x12
#define AZOR_R 0x13
#define AZOR_T 0x14
#define AZOR_Y 0x15
#define AZOR_U 0x16
#define AZOR_I 0x17
#define AZOR_O 0x18
#define AZOR_P 0x19
#define AZOR_LBRACKET 0x1A
#define AZOR_RBRACKET 0x1B
#define AZOR_RETURN 0x1C /* Enter on main keyboards */
#define AZOR_LCONTROL 0x1D
#define AZOR_A 0x1E
#define AZOR_S 0x1F
#define AZOR_D 0x20
#define AZOR_F 0x21
#define AZOR_G 0x22
#define AZOR_H 0x23
#define AZOR_J 0x24
#define AZOR_K 0x25
#define AZOR_L 0x26
#define AZOR_SEMICOLON 0x27
#define AZOR_APOSTROPHE 0x28
#define AZOR_GRAVE 0x29 /* accent grave */
#define AZOR_LSHIFT 0x2A
#define AZOR_BACKSLASH 0x2B
#define AZOR_Z 0x2C
#define AZOR_X 0x2D
#define AZOR_C 0x2E
#define AZOR_V 0x2F
#define AZOR_B 0x30
#define AZOR_N 0x31
#define AZOR_M 0x32
#define AZOR_COMMA 0x33
#define AZOR_PERIOD 0x34 /* . on main keypad */
#define AZOR_SLASH 0x35  /* / on main keypad */
#define AZOR_RSHIFT 0x36
#define AZOR_MULTIPLY 0x37 /* * on numeric keypad */
#define AZOR_LMENU 0x38    /* left Alt */
#define AZOR_SPACE 0x39
#define AZOR_CAPITAL 0x3A
#define AZOR_F1 0x3B
#define AZOR_F2 0x3C
#define AZOR_F3 0x3D
#define AZOR_F4 0x3E
#define AZOR_F5 0x3F
#define AZOR_F6 0x40
#define AZOR_F7 0x41
#define AZOR_F8 0x42
#define AZOR_F9 0x43
#define AZOR_F10 0x44
#define AZOR_NUMLOCK 0x45
#define AZOR_SCROLL 0x46 /* Scroll Lock */
#define AZOR_NUMPAD7 0x47
#define AZOR_NUMPAD8 0x48
#define AZOR_NUMPAD9 0x49
#define AZOR_SUBTRACT 0x4A /* - on numeric keypad */
#define AZOR_NUMPAD4 0x4B
#define AZOR_NUMPAD5 0x4C
#define AZOR_NUMPAD6 0x4D
#define AZOR_ADD 0x4E /* + on numeric keypad */
#define AZOR_NUMPAD1 0x4F
#define AZOR_NUMPAD2 0x50
#define AZOR_NUMPAD3 0x51
#define AZOR_NUMPAD0 0x52
#define AZOR_DECIMAL 0x53 /* . on numeric keypad */
#define AZOR_OEM_102 0x56 /* < > | on UK/Germany keyboards */
#define AZOR_F11 0x57
#define AZOR_F12 0x58
#define AZOR_F13 0x64          /*                     (NEC PC98) */
#define AZOR_F14 0x65          /*                     (NEC PC98) */
#define AZOR_F15 0x66          /*                     (NEC PC98) */
#define AZOR_KANA 0x70         /* (Japanese keyboards)            */
#define AZOR_ABNT_C1 0x73      /* / ? on Portugese (Brazilian) keyboards */
#define AZOR_CONVERT 0x79      /* (Japanese keyboards)            */
#define AZOR_NOCONVERT 0x7B    /* (Japanese keyboards)            */
#define AZOR_YEN 0x7D          /* (Japanese keyboards)            */
#define AZOR_ABNT_C2 0x7E      /* Numpad . on Portugese (Brazilian) keyboards */
#define AZOR_NUMPADEQUALS 0x8D /* = on numeric keypad (NEC PC98) */
#define AZOR_CIRCUMFLEX 0x90   /* (Japanese keyboards)            */
#define AZOR_AT 0x91           /*                     (NEC PC98) */
#define AZOR_COLON 0x92        /*                     (NEC PC98) */
#define AZOR_UNDERLINE 0x93    /*                     (NEC PC98) */
#define AZOR_KANJI 0x94        /* (Japanese keyboards)            */
#define AZOR_STOP 0x95         /*                     (NEC PC98) */
#define AZOR_AX 0x96           /*                     (Japan AX) */
#define AZOR_UNLABELED 0x97    /*                        (J3100) */
#define AZOR_NEXTTRACK 0x99    /* Next Track */
#define AZOR_NUMPADENTER 0x9C  /* Enter on numeric keypad */
#define AZOR_RCONTROL 0x9D
#define AZOR_MUTE 0xA0        /* Mute */
#define AZOR_CALCULATOR 0xA1  /* Calculator */
#define AZOR_PLAYPAUSE 0xA2   /* Play / Pause */
#define AZOR_MEDIASTOP 0xA4   /* Media Stop */
#define AZOR_VOLUMEDOWN 0xAE  /* Volume - */
#define AZOR_VOLUMEUP 0xB0    /* Volume + */
#define AZOR_WEBHOME 0xB2     /* Web home */
#define AZOR_NUMPADCOMMA 0xB3 /* , on numeric keypad (NEC PC98) */
#define AZOR_DIVIDE 0xB5      /* / on numeric keypad */
#define AZOR_SYSRQ 0xB7
#define AZOR_RMENU 0xB8  /* right Alt */
#define AZOR_PAUSE 0xC5  /* Pause */
#define AZOR_HOME 0xC7   /* Home on arrow keypad */
#define AZOR_UP 0xC8     /* UpArrow on arrow keypad */
#define AZOR_PRIOR 0xC9  /* PgUp on arrow keypad */
#define AZOR_LEFT 0xCB   /* LeftArrow on arrow keypad */
#define AZOR_RIGHT 0xCD  /* RightArrow on arrow keypad */
#define AZOR_END 0xCF    /* End on arrow keypad */
#define AZOR_DOWN 0xD0   /* DownArrow on arrow keypad */
#define AZOR_NEXT 0xD1   /* PgDn on arrow keypad */
#define AZOR_INSERT 0xD2 /* Insert on arrow keypad */
#define AZOR_DELETE 0xD3 /* Delete on arrow keypad */
#define AZOR_LWIN 0xDB   /* Left Windows key */
#define AZOR_RWIN 0xDC   /* Right Windows key */
#define AZOR_APPS 0xDD   /* AppMenu key */
#define AZOR_POWER 0xDE
#define AZOR_SLEEP 0xDF
#define AZOR_WAKE 0xE3         /* System Wake */
#define AZOR_WEBSEARCH 0xE5    /* Web Search */
#define AZOR_WEBFAVORITES 0xE6 /* Web Favorites */
#define AZOR_WEBREFRESH 0xE7   /* Web Refresh */
#define AZOR_WEBSTOP 0xE8      /* Web Stop */
#define AZOR_WEBFORWARD 0xE9   /* Web Forward */
#define AZOR_WEBBACK 0xEA      /* Web Back */
#define AZOR_MYCOMPUTER 0xEB   /* My Computer */
#define AZOR_MAIL 0xEC         /* Mail */
#define AZOR_MEDIASELECT 0xED  /* Media Select */

#define AZOR_BACKSPACE AZOR_BACK       /* backspace */
#define AZOR_NUMPADSTAR AZOR_MULTIPLY  /* * on numeric keypad */
#define AZOR_LALT AZOR_LMENU           /* left Alt */
#define AZOR_CAPSLOCK AZOR_CAPITAL     /* CapsLock */
#define AZOR_NUMPADMINUS AZOR_SUBTRACT /* - on numeric keypad */
#define AZOR_NUMPADPLUS AZOR_ADD       /* + on numeric keypad */
#define AZOR_NUMPADPERIOD AZOR_DECIMAL /* . on numeric keypad */
#define AZOR_NUMPADSLASH AZOR_DIVIDE   /* / on numeric keypad */
#define AZOR_RALT AZOR_RMENU           /* right Alt */
#define AZOR_UPARROW AZOR_UP           /* UpArrow on arrow keypad */
#define AZOR_PGUP AZOR_PRIOR           /* PgUp on arrow keypad */
#define AZOR_LEFTARROW AZOR_LEFT       /* LeftArrow on arrow keypad */
#define AZOR_RIGHTARROW AZOR_RIGHT     /* RightArrow on arrow keypad */
#define AZOR_DOWNARROW AZOR_DOWN       /* DownArrow on arrow keypad */
#define AZOR_PGDN AZOR_NEXT            /* PgDn on arrow keypad */
#define AZOR_MOUSE_BT_LEFT 0
#define AZOR_MOUSE_BT_RIGHT 1

#include <d3dx9math.h>

namespace azordx {

class Input {
 private:
  /* data */
 public:
  Input() = delete;
  ~Input() = delete;

 public:
  static void initialize();
  static void clean_up();
  static bool is_key_pressed(int keycode);
  static bool is_mouse_bt_pressed(int btn_code);
  static D3DXVECTOR2 mouse_pos();
  static float mouse_x();
  static float mouse_y();
  static float mouse_z();
};
}  // namespace azordx

#endif  // AZORDX_INPUT_H