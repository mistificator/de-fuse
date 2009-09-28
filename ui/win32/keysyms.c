/* keysyms.c: UI keysym to Fuse input layer keysym mappings
   Copyright (c) 2000-2007 Philip Kendall, Matan Ziv-Av, Russell Marks
                           Fredrick Meunier, Catalin Mihaila, Stuart Brady

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

   Author contact information:

   E-mail: philip-fuse@shadowmagic.org.uk

*/

/* This file is autogenerated from keysyms.dat by keysyms.pl.
   Do not edit unless you know what you're doing! */

#include <config.h>

#define WINVER 0x0500

#include "input.h"
#include "keyboard.h"

#include <windows.h>

keysyms_map_t keysyms_map[] = {

  { VK_TAB,          INPUT_KEY_Tab         },
  { VK_RETURN,       INPUT_KEY_Return      },
  { VK_ESCAPE,       INPUT_KEY_Escape      },
  { VK_SPACE,        INPUT_KEY_space       },
  { VK_OEM_5,        INPUT_KEY_numbersign  },
  { VK_OEM_7,        INPUT_KEY_apostrophe  },
  { VK_OEM_COMMA,    INPUT_KEY_comma       },
  { VK_OEM_MINUS,    INPUT_KEY_minus       },
  { VK_OEM_PERIOD,   INPUT_KEY_period      },
  { VK_OEM_2,        INPUT_KEY_slash       },
  { '0',             INPUT_KEY_0           },
  { '1',             INPUT_KEY_1           },
  { '2',             INPUT_KEY_2           },
  { '3',             INPUT_KEY_3           },
  { '4',             INPUT_KEY_4           },
  { '5',             INPUT_KEY_5           },
  { '6',             INPUT_KEY_6           },
  { '7',             INPUT_KEY_7           },
  { '8',             INPUT_KEY_8           },
  { '9',             INPUT_KEY_9           },
  { VK_OEM_1,        INPUT_KEY_semicolon   },
  { VK_OEM_PLUS,     INPUT_KEY_equal       },
  { 'A',             INPUT_KEY_a           },
  { 'B',             INPUT_KEY_b           },
  { 'C',             INPUT_KEY_c           },
  { 'D',             INPUT_KEY_d           },
  { 'E',             INPUT_KEY_e           },
  { 'F',             INPUT_KEY_f           },
  { 'G',             INPUT_KEY_g           },
  { 'H',             INPUT_KEY_h           },
  { 'I',             INPUT_KEY_i           },
  { 'J',             INPUT_KEY_j           },
  { 'K',             INPUT_KEY_k           },
  { 'L',             INPUT_KEY_l           },
  { 'M',             INPUT_KEY_m           },
  { 'N',             INPUT_KEY_n           },
  { 'O',             INPUT_KEY_o           },
  { 'P',             INPUT_KEY_p           },
  { 'Q',             INPUT_KEY_q           },
  { 'R',             INPUT_KEY_r           },
  { 'S',             INPUT_KEY_s           },
  { 'T',             INPUT_KEY_t           },
  { 'U',             INPUT_KEY_u           },
  { 'V',             INPUT_KEY_v           },
  { 'W',             INPUT_KEY_w           },
  { 'X',             INPUT_KEY_x           },
  { 'Y',             INPUT_KEY_y           },
  { 'Z',             INPUT_KEY_z           },
  { VK_BACK,         INPUT_KEY_BackSpace   },
  { VK_UP,           INPUT_KEY_Up          },
  { VK_DOWN,         INPUT_KEY_Down        },
  { VK_LEFT,         INPUT_KEY_Left        },
  { VK_RIGHT,        INPUT_KEY_Right       },
  { VK_INSERT,       INPUT_KEY_Insert      },
  { VK_DELETE,       INPUT_KEY_Delete      },
  { VK_HOME,         INPUT_KEY_Home        },
  { VK_END,          INPUT_KEY_End         },
  { VK_PRIOR,        INPUT_KEY_Page_Up     },
  { VK_NEXT,         INPUT_KEY_Page_Down   },
  { VK_CAPITAL,      INPUT_KEY_Caps_Lock   },
  { VK_F1,           INPUT_KEY_F1          },
  { VK_F2,           INPUT_KEY_F2          },
  { VK_F3,           INPUT_KEY_F3          },
  { VK_F4,           INPUT_KEY_F4          },
  { VK_F5,           INPUT_KEY_F5          },
  { VK_F6,           INPUT_KEY_F6          },
  { VK_F7,           INPUT_KEY_F7          },
  { VK_F8,           INPUT_KEY_F8          },
  { VK_F9,           INPUT_KEY_F9          },
  { VK_F10,          INPUT_KEY_F10         },
  { VK_F11,          INPUT_KEY_F11         },
  { VK_F12,          INPUT_KEY_F12         },
  { VK_SHIFT,        INPUT_KEY_Shift_L     },
  { VK_CONTROL,      INPUT_KEY_Control_L   },
  { VK_MENU,         INPUT_KEY_Alt_L       },
  { VK_LWIN,         INPUT_KEY_Meta_L      },
  { VK_APPS,         INPUT_KEY_Mode_switch },

  { 0, 0 }			/* End marker: DO NOT MOVE! */

};

