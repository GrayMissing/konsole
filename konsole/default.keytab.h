  /* generated by '../tests/quote ../other/default.Keytab' */

  "# [default.Keytab] Buildin Keyboard Table\n"
  "\n"
  "# --------------------------------------------------------------\n"
  "#\n"
  "# This file is used to create the buildin keyboard table.\n"
  "# It is included for reference purpose with the *.keytab\n"
  "# files that are loaded dynamically.\n"
  "#\n"
  "# Modifying it does not have any effect (unless you\n"
  "# derive the default.keytab.h and recompile konsole).\n"
  "#\n"
  "# To customize your keyboard, copy this file to something\n"
  "# ending with .keytab and change it to meet you needs.\n"
  "# Please read the README.KeyTab and the README.keyboard\n"
  "# in this case.\n"
  "#\n"
  "# --------------------------------------------------------------\n"
  "\n"
  "keyboard \"XTerm (XFree 4.x.x)\"\n"
  "\n"
  "# --------------------------------------------------------------\n"
  "#\n"
  "# Note that this particular table is a \"risc\" version made to\n"
  "# ease customization without bothering with obsolete details.\n"
  "# See VT100.keytab for the more hairy stuff.\n"
  "#\n"
  "# --------------------------------------------------------------\n"
  "\n"
  "# common keys\n"
  "\n"
  "key Escape             : \"\\E\"\n"
  "\n"
  "key Tab   -Shift       : \"\\t\"\n"
  "key Tab   +Shift+Ansi  : \"\\E[Z\"\n"
  "key Tab   +Shift-Ansi  : \"\\t\"\n"
  "\n"
  "key Return-Shift-NewLine : \"\\r\"\n"
  "key Return-Shift+NewLine : \"\\r\\n\"\n"
  "\n"
  "key Return+Shift         : \"\\EOM\"\n"
  "\n"
  "# Backspace and Delete codes are preserving CTRL-H.\n"
  "\n"
  "key Backspace      : \"\\x7f\"\n"
  "\n"
  "# Arrow keys in VT52 mode\n"
  "\n"
  "key Up   -Shift-Ansi : \"\\EA\"\n"
  "key Down -Shift-Ansi : \"\\EB\"\n"
  "key Right-Shift-Ansi : \"\\EC\"\n"
  "key Left -Shift-Ansi : \"\\ED\"\n"
  "\n"
  "# Arrow keys in ANSI mode with Application - and Normal Cursor Mode)\n"
  "\n"
  "key Up   -Shift+Ansi+AppCuKeys : \"\\EOA\"\n"
  "key Down -Shift+Ansi+AppCuKeys : \"\\EOB\"\n"
  "key Right-Shift+Ansi+AppCuKeys : \"\\EOC\"\n"
  "key Left -Shift+Ansi+AppCuKeys : \"\\EOD\"\n"
  "\n"
  "key Up   -Shift+Ansi-AppCuKeys : \"\\E[A\"\n"
  "key Down -Shift+Ansi-AppCuKeys : \"\\E[B\"\n"
  "key Right-Shift+Ansi-AppCuKeys : \"\\E[C\"\n"
  "key Left -Shift+Ansi-AppCuKeys : \"\\E[D\"\n"
  "\n"
  "# other grey PC keys\n"
  "\n"
  "key Enter+NewLine : \"\\r\\n\"\n"
  "key Enter-NewLine : \"\\r\"\n"
  "\n"
  "key Home  -Shift-AppCuKeys : \"\\E[H\"  \n"
  "key End   -Shift-AppCuKeys : \"\\E[F\"  \n"
  "key Home  +Shift-AppCuKeys : \"\\E[2H\"  \n"
  "key End   +Shift-AppCuKeys : \"\\E[2F\"  \n"
  "\n"
  "key Home  -Shift+AppCuKeys : \"\\EOH\"  \n"
  "key End   -Shift+AppCuKeys : \"\\EOF\"  \n"
  "key Home  +Shift+AppCuKeys : \"\\EO2H\"  \n"
  "key End   +Shift+AppCuKeys : \"\\EO2F\"  \n"
  "\n"
  "key Insert-Shift : \"\\E[2~\"  \n"
  "key Delete-Shift : \"\\E[3~\"  \n"
  "key Prior -Shift : \"\\E[5~\"  \n"
  "key Next  -Shift : \"\\E[6~\"  \n"
  "\n"
  "key Delete+Shift : \"\\E[3;2~\"  \n"
  "\n"
  "# Function keys w/o Shift modifier\n"
  "\n"
  "key F1    -Shift   : \"\\EOP\"\n"
  "key F2    -Shift   : \"\\EOQ\"\n"
  "key F3    -Shift   : \"\\EOR\"\n"
  "key F4    -Shift   : \"\\EOS\"\n"
  "key F5    -Shift   : \"\\E[15~\"\n"
  "key F6    -Shift   : \"\\E[17~\"\n"
  "key F7    -Shift   : \"\\E[18~\"\n"
  "key F8    -Shift   : \"\\E[19~\"\n"
  "key F9    -Shift   : \"\\E[20~\"\n"
  "key F10   -Shift   : \"\\E[21~\"\n"
  "key F11   -Shift   : \"\\E[23~\"\n"
  "key F12   -Shift   : \"\\E[24~\"\n"
  "\n"
  "key F1 +Shift    : \"\\EO2P\"  \n"
  "key F2 +Shift    : \"\\EO2Q\"\n"
  "key F3 +Shift    : \"\\EO2R\"\n"
  "key F4 +Shift    : \"\\EO2S\"\n"
  "key F5 +Shift    : \"\\E[15;2~\"\n"
  "key F6 +Shift    : \"\\E[17;2~\" \n"
  "key F7 +Shift    : \"\\E[18;2~\" \n"
  "key F8 +Shift    : \"\\E[19;2~\" \n"
  "key F9 +Shift    : \"\\E[20;2~\" \n"
  "key F10+Shift    : \"\\E[21;2~\" \n"
  "key F11+Shift    : \"\\E[23;2~\" \n"
  "key F12+Shift    : \"\\E[24;2~\" \n"
  "\n"
  "# Work around dead keys\n"
  "\n"
  "key Space +Control : \"\\x00\"\n"
  "\n"
  "# Some keys are used by konsole to cause operations.\n"
  "# The scroll* operations refer to the history buffer.\n"
  "\n"
  "key Up    +Shift   : scrollLineUp\n"
  "key Prior +Shift   : scrollPageUp\n"
  "key Down  +Shift   : scrollLineDown\n"
  "key Next  +Shift   : scrollPageDown\n"
  "key Insert+Shift -Control  : emitClipboard\n"
  "key Insert+Shift +Control  : emitSelection\n"
  "\n"
  "key ScrollLock     : scrollLock\n"
  "\n"
  "# keypad characters are not offered differently by Qt.\n"
  ""
